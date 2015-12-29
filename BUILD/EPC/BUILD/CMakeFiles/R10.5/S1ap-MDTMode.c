/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "S1AP-IEs"
 * 	found in "/home/openair/openair-cn/S1AP/MESSAGES/ASN1/R10.5/S1AP-IEs.asn"
 * 	`asn1c -gen-PER`
 */

#include "S1ap-MDTMode.h"

static asn_per_constraints_t asn_PER_type_S1ap_MDTMode_constr_1 GCC_NOTUSED = {
	{ APC_CONSTRAINED | APC_EXTENSIBLE,  1,  1,  0,  1 }	/* (0..1,...) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_TYPE_member_t asn_MBR_S1ap_MDTMode_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct S1ap_MDTMode, choice.immediateMDT),
		(ASN_TAG_CLASS_CONTEXT | (0 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_S1ap_ImmediateMDT,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"immediateMDT"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct S1ap_MDTMode, choice.loggedMDT),
		(ASN_TAG_CLASS_CONTEXT | (1 << 2)),
		-1,	/* IMPLICIT tag at current level */
		&asn_DEF_S1ap_LoggedMDT,
		0,	/* Defer constraints checking to the member type */
		0,	/* No PER visible constraints */
		0,
		"loggedMDT"
		},
};
static asn_TYPE_tag2member_t asn_MAP_S1ap_MDTMode_tag2el_1[] = {
    { (ASN_TAG_CLASS_CONTEXT | (0 << 2)), 0, 0, 0 }, /* immediateMDT at 849 */
    { (ASN_TAG_CLASS_CONTEXT | (1 << 2)), 1, 0, 0 } /* loggedMDT at 850 */
};
static asn_CHOICE_specifics_t asn_SPC_S1ap_MDTMode_specs_1 = {
	sizeof(struct S1ap_MDTMode),
	offsetof(struct S1ap_MDTMode, _asn_ctx),
	offsetof(struct S1ap_MDTMode, present),
	sizeof(((struct S1ap_MDTMode *)0)->present),
	asn_MAP_S1ap_MDTMode_tag2el_1,
	2,	/* Count of tags in the map */
	0,
	2	/* Extensions start */
};
asn_TYPE_descriptor_t asn_DEF_S1ap_MDTMode = {
	"S1ap-MDTMode",
	"S1ap-MDTMode",
	CHOICE_free,
	CHOICE_print,
	CHOICE_constraint,
	CHOICE_decode_ber,
	CHOICE_encode_der,
	CHOICE_decode_xer,
	CHOICE_encode_xer,
	CHOICE_decode_uper,
	CHOICE_encode_uper,
	CHOICE_decode_aper,
	CHOICE_encode_aper,
	CHOICE_outmost_tag,
	0,	/* No effective tags (pointer) */
	0,	/* No effective tags (count) */
	0,	/* No tags (pointer) */
	0,	/* No tags (count) */
	&asn_PER_type_S1ap_MDTMode_constr_1,
	asn_MBR_S1ap_MDTMode_1,
	2,	/* Elements count */
	&asn_SPC_S1ap_MDTMode_specs_1	/* Additional specs */
};

