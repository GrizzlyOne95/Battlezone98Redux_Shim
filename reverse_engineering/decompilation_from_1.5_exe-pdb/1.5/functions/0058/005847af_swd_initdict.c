/*
 * Entry: 005847af
 * Name: swd_initdict
 * Namespace: Global
 * Signature: void swd_initdict(lzo1y_999_swd_t * param_1, uchar * param_2, ulong param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl swd_initdict(lzo1y_999_swd_t *param_1,uchar *param_2,ulong param_3)

{
  uint uVar1;
  uint in_EAX;
  uint in_ECX;
  uint *unaff_ESI;
  
  unaff_ESI[0x52] = 0;
  unaff_ESI[0x51] = 0;
  unaff_ESI[0x53] = 0;
  if ((in_EAX != 0) && (in_ECX != 0)) {
    uVar1 = *unaff_ESI;
    if (uVar1 < in_ECX) {
      in_EAX = in_EAX + (in_ECX - uVar1);
      in_ECX = uVar1;
    }
    unaff_ESI[0x51] = in_EAX;
    unaff_ESI[0x53] = in_ECX;
    unaff_ESI[0x52] = in_EAX + in_ECX;
    memcpy(unaff_ESI + 0x5b,in_EAX,in_ECX);
    unaff_ESI[0x54] = in_ECX;
  }
  return;
}
