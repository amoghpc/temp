/* Definitions for thread-local data handling.  Hurd/i386 version.
   Copyright (C) 2003-2014 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#ifndef _I386_TLS_H
#define _I386_TLS_H


/* Some things really need not be machine-dependent.  */
#include <sysdeps/mach/hurd/tls.h>

/* The TCB can have any size and the memory following the address the
   thread pointer points to is unspecified.  Allocate the TCB there.  */
#define TLS_TCB_AT_TP	1

#ifndef __ASSEMBLER__

/* Use i386-specific RPCs to arrange that %gs segment register prefix
   addresses the TCB in each thread.  */
# include <mach/i386/mach_i386.h>

# ifndef HAVE_I386_SET_GDT
#  define __i386_set_gdt(thr, sel, desc) ((void) (thr), (void) (sel), (void) (desc), MIG_BAD_ID)
# endif

# include <errno.h>
# include <assert.h>

# define HURD_TLS_DESC_DECL(desc, tcb)					      \
  struct descriptor desc =						      \
    {				/* low word: */				      \
      0xffff			/* limit 0..15 */			      \
      | (((unsigned int) (tcb)) << 16) /* base 0..15 */			      \
      ,				/* high word: */			      \
      ((((unsigned int) (tcb)) >> 16) & 0xff) /* base 16..23 */		      \
      | ((0x12 | 0x60 | 0x80) << 8) /* access = ACC_DATA_W|ACC_PL_U|ACC_P */  \
      | (0xf << 16)		/* limit 16..19 */			      \
      | ((4 | 8) << 20)		/* granularity = SZ_32|SZ_G */		      \
      | (((unsigned int) (tcb)) & 0xff000000) /* base 24..31 */		      \
    }

# define HURD_DESC_TLS(desc)						      \
  ({									      \
   (tcbhead_t *) (   (desc->low_word >> 16)				      \
                  | ((desc->high_word & 0xff) << 16)			      \
                  |  (desc->high_word & 0xff000000)			      \
     );})

#define __LIBC_NO_TLS()							      \
  ({ unsigned short ds, gs;						      \
     asm ("movw %%ds,%w0; movw %%gs,%w1" : "=q" (ds), "=q" (gs));	      \
     ds == gs; })

static inline const char * __attribute__ ((unused))
_hurd_tls_init (tcbhead_t *tcb, int secondcall)
{
  HURD_TLS_DESC_DECL (desc, tcb);
  thread_t self = __mach_thread_self ();
  const char *msg = NULL;

  if (!secondcall)
    {
      /* This field is used by TLS accesses to get our "thread pointer"
	 from the TLS point of view.  */
      tcb->tcb = tcb;

      /* Get the first available selector.  */
      int sel = -1;
      kern_return_t err = __i386_set_gdt (self, &sel, desc);
      if (err == MIG_BAD_ID)
	{
	  /* Old kernel, use a per-thread LDT.  */
	  sel = 0x27;
	  err = __i386_set_ldt (self, sel, &desc, 1);
	  assert_perror (err);
	  if (err)
	    {
	      msg = "i386_set_ldt failed";
	      goto out;
	    }
	}
      else if (err)
	{
	  assert_perror (err); /* Separate from above with different line #. */
	  msg = "i386_set_gdt failed";
	  goto out;
	}

      /* Now install the new selector.  */
      asm volatile ("mov %w0, %%gs" :: "q" (sel));
    }
  else
    {
      /* Fetch the selector set by the first call.  */
      int sel;
      asm ("mov %%gs, %w0" : "=q" (sel) : "0" (0));
      if (__builtin_expect (sel, 0x48) & 4) /* LDT selector */
	{
	  kern_return_t err = __i386_set_ldt (self, sel, &desc, 1);
	  assert_perror (err);
	  if (err)
	    {
	      msg = "i386_set_ldt failed";
	      goto out;
	    }
	}
      else
	{
	  kern_return_t err = __i386_set_gdt (self, &sel, desc);
	  assert_perror (err);
	  if (err)
	    {
	      msg = "i386_set_gdt failed";
	      goto out;
	    }
	}
    }

out:
  __mach_port_deallocate (__mach_task_self (), self);
  return msg;
}

/* Code to initially initialize the thread pointer.  This might need
   special attention since 'errno' is not yet available and if the
   operation can cause a failure 'errno' must not be touched.  */
# define TLS_INIT_TP(descr, secondcall) \
    _hurd_tls_init ((tcbhead_t *) (descr), (secondcall))

/* Return the TCB address of the current thread.  */
# define THREAD_SELF							      \
  ({ tcbhead_t *__tcb;							      \
     __asm__ ("movl %%gs:%c1,%0" : "=r" (__tcb)				      \
	      : "i" (offsetof (tcbhead_t, tcb)));			      \
     __tcb;})

/* Return the TCB address of a thread given its state.  */
# define THREAD_TCB(thread, thread_state)				      \
  ({ int __sel = (thread_state)->basic.gs;				      \
     tcbhead_t *__tcb;							      \
     struct descriptor __desc, *___desc = &__desc;			      \
     unsigned int __count = 1;						      \
     kern_return_t __err;						      \
     if (__builtin_expect (__sel, 0x48) & 4) /* LDT selector */		      \
       __err = __i386_get_ldt ((thread), __sel, 1, &___desc, &__count);	      \
     else								      \
       __err = __i386_get_gdt ((thread), __sel, &__desc);		      \
     assert_perror (__err);						      \
     assert (__count == 1);						      \
     HURD_DESC_TLS(___desc);})

/* Install new dtv for current thread.  */
# define INSTALL_NEW_DTV(dtvp)						      \
  ({ asm volatile ("movl %0,%%gs:%P1"					      \
		   : : "ir" (dtvp), "i" (offsetof (tcbhead_t, dtv))); })

/* Return the address of the dtv for the current thread.  */
# define THREAD_DTV()							      \
  ({ dtv_t *_dtv;							      \
     asm ("movl %%gs:%P1,%0" : "=q" (_dtv) : "i" (offsetof (tcbhead_t, dtv)));\
     _dtv; })

# include <mach/machine/thread_status.h>

/* Set up TLS in the new thread of a fork child, copying from the original.  */
static inline kern_return_t __attribute__ ((unused))
_hurd_tls_fork (thread_t child, thread_t orig, struct i386_thread_state *state)
{
  /* Fetch the selector set by _hurd_tls_init.  */
  int sel;
  asm ("mov %%gs, %w0" : "=q" (sel) : "0" (0));
  if (sel == state->ds)		/* _hurd_tls_init was never called.  */
    return 0;

  struct descriptor desc, *_desc = &desc;
  int err;
  unsigned int count = 1;

  if (__builtin_expect (sel, 0x48) & 4) /* LDT selector */
    err = __i386_get_ldt (orig, sel, 1, &_desc, &count);
  else
    err = __i386_get_gdt (orig, sel, &desc);

  assert_perror (err);
  if (err)
    return err;

  if (__builtin_expect (sel, 0x48) & 4) /* LDT selector */
    err = __i386_set_ldt (child, sel, &desc, 1);
  else
    err = __i386_set_gdt (child, &sel, desc);

  state->gs = sel;
  return err;
}

static inline kern_return_t __attribute__ ((unused))
_hurd_tls_new (thread_t child, struct i386_thread_state *state, tcbhead_t *tcb)
{
  /* Fetch the selector set by _hurd_tls_init.  */
  int sel;
  asm ("mov %%gs, %w0" : "=q" (sel) : "0" (0));
  if (sel == state->ds)		/* _hurd_tls_init was never called.  */
    return 0;

  HURD_TLS_DESC_DECL (desc, tcb);
  kern_return_t err;

  tcb->tcb = tcb;
  tcb->self = child;

  if (__builtin_expect (sel, 0x48) & 4) /* LDT selector */
    err = __i386_set_ldt (child, sel, &desc, 1);
  else
    err = __i386_set_gdt (child, &sel, desc);

  state->gs = sel;
  return err;
}

#endif	/* !__ASSEMBLER__ */

#endif	/* i386/tls.h */
