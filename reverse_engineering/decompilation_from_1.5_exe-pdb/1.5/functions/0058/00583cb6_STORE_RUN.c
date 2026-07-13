/*
 * Entry: 00583cb6
 * Name: STORE_RUN
 * Namespace: Global
 * Signature: uchar * STORE_RUN(lzo1x_999_t * param_1, uchar * param_2, uchar * param_3, ulong param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uchar * __cdecl STORE_RUN(lzo1x_999_t *param_1,uchar *param_2,uchar *param_3,ulong param_4)

{
  uchar *in_EAX;
  byte bVar1;
  int iVar2;
  uchar *puVar3;
  int unaff_EDI;
  uchar *local_8;
  
  *(int *)(unaff_EDI + 0x3c) = (int)(param_2 + *(int *)(unaff_EDI + 0x3c));
  bVar1 = (byte)param_2;
  if ((in_EAX == *(uchar **)(unaff_EDI + 0x28)) && (param_2 < (uchar *)0xef)) {
    *in_EAX = bVar1 + 0x11;
    in_EAX = in_EAX + 1;
  }
  else if (param_2 < (uchar *)0x4) {
    in_EAX[-2] = in_EAX[-2] | bVar1;
    *(int *)(unaff_EDI + 0x68) = *(int *)(unaff_EDI + 0x68) + 1;
  }
  else if (param_2 < (uchar *)0x13) {
    *in_EAX = bVar1 - 3;
    in_EAX = in_EAX + 1;
    *(int *)(unaff_EDI + 0x6c) = *(int *)(unaff_EDI + 0x6c) + 1;
  }
  else {
    local_8 = param_2 + -0x12;
    *in_EAX = '\0';
    puVar3 = in_EAX + 1;
    if ((uchar *)0xff < local_8) {
      iVar2 = (uint)(param_2 + -0x112) / 0xff + 1;
      memset(puVar3,0,iVar2);
      puVar3 = puVar3 + iVar2;
      do {
        local_8 = local_8 + -0xff;
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
    *puVar3 = (uchar)local_8;
    in_EAX = puVar3 + 1;
    *(int *)(unaff_EDI + 0x70) = *(int *)(unaff_EDI + 0x70) + 1;
  }
  do {
    *in_EAX = (uchar)param_1->init;
    in_EAX = in_EAX + 1;
    param_1 = (lzo1x_999_t *)((int)&param_1->init + 1);
    param_2 = param_2 + -1;
  } while (param_2 != (uchar *)0x0);
  return in_EAX;
}
