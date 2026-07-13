/*
 * Entry: 00584f55
 * Name: init_match
 * Namespace: Global
 * Signature: int init_match(lzo1y_999_t * param_1, lzo1y_999_swd_t * param_2, uchar * param_3, ulong param_4, ulong param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
init_match(lzo1y_999_t *param_1,lzo1y_999_swd_t *param_2,uchar *param_3,ulong param_4,ulong param_5)

{
  undefined4 *in_EAX;
  int iVar1;
  int in_ECX;
  ulong unaff_ESI;
  uchar *unaff_EDI;
  
  *in_EAX = 1;
  *(undefined4 **)(in_ECX + 0xb4) = in_EAX;
  in_EAX[5] = 0;
  in_EAX[4] = 0;
  in_EAX[0xe] = 0;
  in_EAX[0xd] = 0;
  in_EAX[0xc] = 0;
  in_EAX[0x11] = 0;
  in_EAX[0x10] = 0;
  in_EAX[0xf] = 0;
  in_EAX[0x12] = 0;
  iVar1 = swd_init(param_2,unaff_EDI,unaff_ESI);
  if (iVar1 == 0) {
    *(uint *)(in_ECX + 0x14) = (uint)param_3 & 1;
    iVar1 = 0;
  }
  return iVar1;
}
