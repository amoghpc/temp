/*
 * Generated by asn1c-0.9.24 (http://lionet.info/asn1c)
 * From ASN.1 module "S1AP-IEs"
 * 	found in "/home/openair/openair-cn/S1AP/MESSAGES/ASN1/R10.5/S1AP-IEs.asn"
 * 	`asn1c -gen-PER`
 */

#ifndef	_S1ap_HandoverRestrictionList_H_
#define	_S1ap_HandoverRestrictionList_H_


#include <asn_application.h>

/* Including external dependencies */
#include "S1ap-PLMNidentity.h"
#include "S1ap-ForbiddenInterRATs.h"
#include <constr_SEQUENCE.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declarations */
struct S1ap_EPLMNs;
struct S1ap_ForbiddenTAs;
struct S1ap_ForbiddenLAs;
struct S1ap_IE_Extensions;

/* S1ap-HandoverRestrictionList */
typedef struct S1ap_HandoverRestrictionList {
	S1ap_PLMNidentity_t	 servingPLMN;
	struct S1ap_EPLMNs	*equivalentPLMNs	/* OPTIONAL */;
	struct S1ap_ForbiddenTAs	*forbiddenTAs	/* OPTIONAL */;
	struct S1ap_ForbiddenLAs	*forbiddenLAs	/* OPTIONAL */;
	S1ap_ForbiddenInterRATs_t	*forbiddenInterRATs	/* OPTIONAL */;
	struct S1ap_IE_Extensions	*iE_Extensions	/* OPTIONAL */;
	/*
	 * This type is extensible,
	 * possible extensions are below.
	 */
	
	/* Context for parsing across buffer boundaries */
	asn_struct_ctx_t _asn_ctx;
} S1ap_HandoverRestrictionList_t;

/* Implementation */
extern asn_TYPE_descriptor_t asn_DEF_S1ap_HandoverRestrictionList;

#ifdef __cplusplus
}
#endif

/* Referred external types */
#include "S1ap-EPLMNs.h"
#include "S1ap-ForbiddenTAs.h"
#include "S1ap-ForbiddenLAs.h"
#include "S1ap-IE-Extensions.h"

#endif	/* _S1ap_HandoverRestrictionList_H_ */
#include <asn_internal.h>
