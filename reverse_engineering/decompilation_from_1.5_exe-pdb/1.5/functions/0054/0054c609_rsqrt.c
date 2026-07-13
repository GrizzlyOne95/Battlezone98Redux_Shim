/*
 * Entry: 0054c609
 * Name: rsqrt
 * Namespace: Global
 * Signature: double rsqrt(double param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

double __cdecl rsqrt(double param_1)

{
  double dVar1;
  uint uVar2;
  
  uVar2 = (0xbfc - (param_1._4_4_ >> 0x14) >> 1) << 0x14 |
          (uint)rsqrt_lookup[param_1._4_4_ >> 0xd & 0xff] << 0xc;
  dVar1 = (double)((ulonglong)uVar2 << 0x20);
  return (Const_Three - dVar1 * dVar1 * param_1) * (double)((ulonglong)uVar2 << 0x20) * Const_Half *
         Const_Error;
}
