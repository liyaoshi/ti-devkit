/* _LDnorm function -- IEEE 754 version */
#include "xmath.h"
_STD_BEGIN

 #if _DLONG == 0
	/* not needed -- 64-bit */
        /*-------------------------------------------------------------------*/
        /* _DLONG == 0 means "long double" is 64 bits, and in the original   */
        /* Dinkum source, that means _LDnorm is not actually needed;         */
        /* _LDunscale will call _Dnorm directly.  However, due to            */
        /* TI-specific changes to xxfmod.h, we do call FNAME(Dnorm), so we   */
        /* do need this function after all.                                  */
        /*-------------------------------------------------------------------*/
  #if defined(_32_BIT_LDOUBLE)
short _LDnorm(unsigned short *ps)
        { 
            return (_FDnorm(ps)); /* 32-bit */
        }
  #elif !defined(_32_BIT_DOUBLE)
short _LDnorm(unsigned short *ps)
        {
            return (_Dnorm(ps)); /* 64-bit */
        }
  #else
short _LDnorm(unsigned short *ps)
	{	/* normalize double fraction -- 64-bit */
	short xchar;
	unsigned short sign = (unsigned short)(ps[_D0] & _DSIGN);

	xchar = 1;
	if ((ps[_D0] &= _DFRAC) != 0 || ps[_D1]
		|| ps[_D2] || ps[_D3])
		{	/* nonzero, scale */
		for (; ps[_D0] == 0; xchar -= 16)
			{	/* shift left by 16 */
			ps[_D0] = ps[_D1], ps[_D1] = ps[_D2];
			ps[_D2] = ps[_D3], ps[_D3] = 0;
			}
		for (; ps[_D0] < 1 << _DOFF; --xchar)
			{	/* shift left by 1 */
			ps[_D0] = (unsigned short)(ps[_D0] << 1 | ps[_D1] >> 15);
			ps[_D1] = (unsigned short)(ps[_D1] << 1 | ps[_D2] >> 15);
			ps[_D2] = (unsigned short)(ps[_D2] << 1 | ps[_D3] >> 15);
			ps[_D3] <<= 1;
			}
		for (; 1 << (_DOFF + 1) <= ps[_D0]; ++xchar)
			{	/* shift right by 1 */
			ps[_D3] = (unsigned short)(ps[_D3] >> 1 | ps[_D2] << 15);
			ps[_D2] = (unsigned short)(ps[_D2] >> 1 | ps[_D1] << 15);
			ps[_D1] = (unsigned short)(ps[_D1] >> 1 | ps[_D0] << 15);
			ps[_D0] >>= 1;
			}
		ps[_D0] &= _DFRAC;
		}
	ps[_D0] |= sign;
	return (xchar);
	}
  #endif /* defined(_32_BIT_LDOUBLE) */

 #elif _DLONG == 1
short _LDnorm(unsigned short *ps)
	{	/* normalize long double fraction -- 80-bit */
	short xchar;
	unsigned short sign = ps[_L0];

	xchar = 0;
	for (ps[_L0] = 0; ps[_L0] == 0 && ps[_L1] < 0x100;
		xchar -= 16)
		{	/* shift left by 16 */
		ps[_L0] = ps[_L1];
		ps[_L1] = ps[_L2], ps[_L2] = ps[_L3];
		ps[_L3] = ps[_L4], ps[_L4] = 0;
		}
	if (ps[_L0] == 0)
		for (; ps[_L1] < (1U << _LOFF); --xchar)
			{	/* shift left by 1 */
			ps[_L1] = ps[_L1] << 1 | ps[_L2] >> 15;
			ps[_L2] = ps[_L2] << 1 | ps[_L3] >> 15;
			ps[_L3] = ps[_L3] << 1 | ps[_L4] >> 15;
			ps[_L4] <<= 1;
			}
	for (; ps[_L0] != 0; ++xchar)
		{	/* shift right by 1 */
		ps[_L4] = ps[_L4] >> 1 | ps[_L3] << 15;
		ps[_L3] = ps[_L3] >> 1 | ps[_L2] << 15;
		ps[_L2] = ps[_L2] >> 1 | ps[_L1] << 15;
		ps[_L1] = ps[_L1] >> 1 | ps[_L0] << 15;
		ps[_L0] >>= 1;
		}
	ps[_L0] = sign;
	return (xchar);
	}

 #else	/* 1 < _DLONG */
short _LDnorm(unsigned short *ps)
	{	/* normalize long double fraction -- 128-bit SPARC */
	short xchar;
	unsigned short sign = ps[_L0];

	xchar = 1;
	if (ps[_L1] != 0 || ps[_L2] != 0 || ps[_L3] != 0
		|| ps[_L4] != 0 || ps[_L5] != 0 || ps[_L6] != 0
		|| ps[_L7] != 0)
		{	/* nonzero, scale */
		for (ps[_L0] = 0; ps[_L0] == 0 && ps[_L1] < 0x100;
			xchar -= 16)
			{	/* shift left by 16 */
			ps[_L0] = ps[_L1];
			ps[_L1] = ps[_L2], ps[_L2] = ps[_L3];
			ps[_L3] = ps[_L4], ps[_L4] = ps[_L5];
			ps[_L5] = ps[_L6], ps[_L6] = ps[_L7];
			ps[_L7] = 0;
			}
		for (; ps[_L0] == 0; --xchar)
			{	/* shift left by 1 */
			ps[_L0] = ps[_L0] << 1 | ps[_L1] >> 15;
			ps[_L1] = ps[_L1] << 1 | ps[_L2] >> 15;
			ps[_L2] = ps[_L2] << 1 | ps[_L3] >> 15;
			ps[_L3] = ps[_L3] << 1 | ps[_L4] >> 15;
			ps[_L4] = ps[_L4] << 1 | ps[_L5] >> 15;
			ps[_L5] = ps[_L5] << 1 | ps[_L6] >> 15;
			ps[_L6] = ps[_L6] << 1 | ps[_L7] >> 15;
			ps[_L7] <<= 1;
			}
		for (; 1 < ps[_L0]; ++xchar)
			{	/* shift right by 1 */
			ps[_L7] = ps[_L7] >> 1 | ps[_L6] << 15;
			ps[_L6] = ps[_L6] >> 1 | ps[_L5] << 15;
			ps[_L5] = ps[_L5] >> 1 | ps[_L4] << 15;
			ps[_L4] = ps[_L4] >> 1 | ps[_L3] << 15;
			ps[_L3] = ps[_L3] >> 1 | ps[_L2] << 15;
			ps[_L2] = ps[_L2] >> 1 | ps[_L1] << 15;
			ps[_L1] = ps[_L1] >> 1 | ps[_L0] << 15;
			ps[_L0] >>= 1;
			}
		}
	ps[_L0] = sign;
	return (xchar);
	}
 #endif /* _DLONG */

_STD_END

/*
 * Copyright (c) 1992-2004 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
V4.02:1476 */
