/*
 * Licensed to the OpenAirInterface (OAI) Software Alliance under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The OpenAirInterface Software Alliance licenses this file to You under 
 * the Apache License, Version 2.0  (the "License"); you may not use this file
 * except in compliance with the License.  
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *-------------------------------------------------------------------------------
 * For more information about the OpenAirInterface (OAI) Software Alliance:
 *      contact@openairinterface.org
 */


#if MME_CLIENT_TEST == 0
# include "intertask_interface.h"
#endif

#include "mme_config.h"

#ifndef S1AP_MME_H_
#define S1AP_MME_H_

// Forward declarations
struct eNB_description_s;

enum s1_eNB_state_s {
  S1AP_RESETING,      ///< After a reset request (eNB or MME initiated)
  S1AP_READY          ///< MME and eNB are S1 associated, UE contexts can be added
};

enum s1_ue_state_s {
  S1AP_UE_WAITING_CSR,    ///< Waiting for Initial Context Setup Response
  S1AP_UE_HANDOVER,       ///< Handover procedure triggered
  S1AP_UE_CONNECTED,      ///< UE context ready
};

/** Main structure representing UE association over s1ap
 *  Generated every time a new InitialUEMessage is received
 **/
typedef struct ue_description_s {
  STAILQ_ENTRY(ue_description_s) ue_entries;

  struct eNB_description_s *eNB;           ///< Which eNB this UE is attached to

  enum s1_ue_state_s        s1_ue_state;       ///< S1AP UE state

  unsigned eNB_ue_s1ap_id:24;    ///< Unique UE id over eNB (24 bits wide)
  uint32_t mme_ue_s1ap_id;    ///< Unique UE id over MME (32 bits wide)

  /** SCTP stream on which S1 message will be sent/received.
   *  During an UE S1 connection, a pair of streams is
   *  allocated and is used during all the connection.
   *  Stream 0 is reserved for non UE signalling.
   *  @name sctp stream identifier
   **/
  /*@{*/
  uint16_t sctp_stream_recv; ///< eNB -> MME stream
  uint16_t sctp_stream_send; ///< MME -> eNB stream
  /*@}*/

  uint32_t s11_sgw_teid;

  /* Timer for procedure outcome issued by MME that should be answered */
  long outcome_response_timer_id;
} ue_description_t;

/* Main structure representing eNB association over s1ap
 * Generated (or updated) every time a new S1SetupRequest is received.
 */
typedef struct eNB_description_s {
  STAILQ_ENTRY(eNB_description_s) eNB_entries;

  enum s1_eNB_state_s s1_state;         ///< State of the eNB S1AP association over MME

  /** eNB related parameters **/
  /*@{*/
  char     eNB_name[150];      ///< Printable eNB Name
  uint32_t eNB_id;             ///< Unique eNB ID
  uint8_t  default_paging_drx; ///< Default paging DRX interval for eNB
  /*@}*/

  /** UE list for this eNB **/
  /*@{*/
  uint32_t nb_ue_associated; ///< Number of NAS associated UE on this eNB
  STAILQ_HEAD(ue_list_s, ue_description_s) ue_list_head;
  /*@}*/

  /** SCTP stuff **/
  /*@{*/
  uint32_t sctp_assoc_id;    ///< SCTP association id on this machine
  uint16_t next_sctp_stream; ///< Next SCTP stream
  uint16_t instreams;        ///< Number of streams avalaible on eNB -> MME
  uint16_t outstreams;       ///< Number of streams avalaible on MME -> eNB
  /*@}*/
} eNB_description_t;

extern int              hss_associated;
extern uint32_t         nb_eNB_associated;
extern mme_config_t    *global_mme_config_p;

/** \brief S1AP layer top init
 * @returns -1 in case of failure
 **/
int s1ap_mme_init(const mme_config_t *mme_config);

/** \brief Look for given eNB id in the list
 * \param eNB_id The unique eNB id to search in list
 * @returns NULL if no eNB matchs the eNB id, or reference to the eNB element in list if matches
 **/
eNB_description_t* s1ap_is_eNB_id_in_list(const uint32_t eNB_id);

/** \brief Look for given eNB SCTP assoc id in the list
 * \param eNB_id The unique sctp assoc id to search in list
 * @returns NULL if no eNB matchs the sctp assoc id, or reference to the eNB element in list if matches
 **/
eNB_description_t* s1ap_is_eNB_assoc_id_in_list(const uint32_t sctp_assoc_id);

/** \brief Look for given ue eNB id in the list
 * \param eNB_id The unique ue_eNB_id to search in list
 * @returns NULL if no UE matchs the ue_eNB_id, or reference to the ue element in list if matches
 **/
ue_description_t* s1ap_is_ue_eNB_id_in_list(eNB_description_t *eNB_ref,
    const uint32_t eNB_ue_s1ap_id);

/** \brief Look for given ue mme id in the list
 * \param eNB_id The unique ue_mme_id to search in list
 * @returns NULL if no UE matchs the ue_mme_id, or reference to the ue element in list if matches
 **/
ue_description_t* s1ap_is_ue_mme_id_in_list(const uint32_t ue_mme_id);
ue_description_t* s1ap_is_s11_sgw_teid_in_list(const uint32_t teid);

/** \brief Allocate and add to the list a new eNB descriptor
 * @returns Reference to the new eNB element in list
 **/
eNB_description_t* s1ap_new_eNB(void);

/** \brief Allocate and add to the right eNB list a new UE descriptor
 * \param sctp_assoc_id association ID over SCTP
 * @returns Reference to the new UE element in list
 **/
ue_description_t* s1ap_new_ue(const uint32_t sctp_assoc_id);

/** \brief Dump the eNB list
 * Calls dump_eNB for each eNB in list
 **/
void s1ap_dump_eNB_list(void);

/** \brief Dump eNB related information.
 * Calls dump_ue for each UE in list
 * \param eNB_ref eNB structure reference to dump
 **/
void s1ap_dump_eNB(eNB_description_t *eNB_ref);

/** \brief Dump UE related information.
 * \param ue_ref ue structure reference to dump
 **/
void s1ap_dump_ue(ue_description_t *ue_ref);

/** \brief Remove target UE from the list
 * \param ue_ref UE structure reference to remove
 **/
void s1ap_remove_ue(ue_description_t *ue_ref);

/** \brief Remove target eNB from the list and remove any UE associated
 * \param eNB_ref eNB structure reference to remove
 **/
void s1ap_remove_eNB(eNB_description_t *eNB_ref);

#endif /* S1AP_MME_H_ */
