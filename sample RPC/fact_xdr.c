/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "fact.h"

bool_t
xdr_num (XDR *xdrs, num *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->a))
		 return FALSE;
	return TRUE;
}
