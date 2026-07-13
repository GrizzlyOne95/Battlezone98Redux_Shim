/*
 * Entry: 00584fa5
 * Name: find_match
 * Namespace: Global
 * Signature: int find_match(lzo1y_999_t * param_1, lzo1y_999_swd_t * param_2, ulong param_3, ulong param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl find_match(lzo1y_999_t *param_1,lzo1y_999_swd_t *param_2,ulong param_3,ulong param_4)

{
  int iVar1;
  int in_EAX;
  int unaff_ESI;
  lzo1y_999_swd_t *unaff_EDI;
  
  if (param_2 != (lzo1y_999_swd_t *)0x0) {
    swd_accept((lzo1y_999_swd_t *)((int)param_1 - (int)param_2),(ulong)unaff_EDI);
    param_1 = (lzo1y_999_t *)((int)param_1 + (1 - (int)param_2));
  }
  *(int *)(unaff_ESI + 0x30) = (int)&param_1->init + *(int *)(unaff_ESI + 0x30);
  *(undefined4 *)(in_EAX + 0x1c) = 1;
  *(undefined4 *)(in_EAX + 0x20) = 0;
  if (*(int *)(in_EAX + 0x14) != 0) {
    memset(in_EAX + 0xbc,0,0x88);
  }
  swd_findbest(unaff_EDI);
  *(undefined4 *)(unaff_ESI + 8) = *(undefined4 *)(in_EAX + 0x1c);
  *(undefined4 *)(unaff_ESI + 0xc) = *(undefined4 *)(in_EAX + 0x20);
  swd_getbyte(unaff_EDI);
  if (*(int *)(in_EAX + 0x28) < 0) {
    *(undefined4 *)(unaff_ESI + 4) = 0;
    *(undefined4 *)(unaff_ESI + 8) = 0;
  }
  else {
    *(int *)(unaff_ESI + 4) = *(int *)(in_EAX + 0x24) + 1;
  }
  *(int *)(unaff_ESI + 0x18) = *(int *)(unaff_ESI + 0x1c) - *(int *)(unaff_ESI + 4);
  iVar1 = *(int *)(unaff_ESI + 0x2c);
  if (((iVar1 != 0) && (*(code **)(iVar1 + 8) != (code *)0x0)) &&
     (*(uint *)(unaff_ESI + 0x38) < *(uint *)(unaff_ESI + 0x30))) {
    (**(code **)(iVar1 + 8))(iVar1,*(uint *)(unaff_ESI + 0x30),*(undefined4 *)(unaff_ESI + 0x34),0);
    *(int *)(unaff_ESI + 0x38) = *(int *)(unaff_ESI + 0x38) + 0x400;
  }
  return 0;
}
