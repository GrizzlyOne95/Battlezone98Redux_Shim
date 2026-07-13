/*
 * Entry: 00584aa8
 * Name: swd_getbyte
 * Namespace: Global
 * Signature: void swd_getbyte(lzo1y_999_swd_t * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl swd_getbyte(lzo1y_999_swd_t *param_1)

{
  int iVar1;
  byte *pbVar2;
  int in_EAX;
  int *piVar3;
  uint uVar4;
  
  iVar1 = *(int *)(in_EAX + 0xb4);
  pbVar2 = *(byte **)(iVar1 + 0x1c);
  if (pbVar2 < *(byte **)(iVar1 + 0x24)) {
    uVar4 = (uint)*pbVar2;
    *(byte **)(iVar1 + 0x1c) = pbVar2 + 1;
  }
  else {
    uVar4 = 0xffffffff;
  }
  if ((int)uVar4 < 0) {
    if (*(int *)(in_EAX + 0x24) != 0) {
      *(int *)(in_EAX + 0x24) = *(int *)(in_EAX + 0x24) + -1;
    }
    *(undefined1 *)(*(int *)(in_EAX + 0x150) + 0x16c + in_EAX) = 0;
    if (*(uint *)(in_EAX + 0x150) < *(uint *)(in_EAX + 4)) {
      *(undefined1 *)(*(uint *)(in_EAX + 0x150) + *(int *)(in_EAX + 0x160)) = 0;
    }
  }
  else {
    *(char *)(*(int *)(in_EAX + 0x150) + 0x16c + in_EAX) = (char)uVar4;
    if (*(uint *)(in_EAX + 0x150) < *(uint *)(in_EAX + 4)) {
      *(char *)(*(uint *)(in_EAX + 0x150) + *(int *)(in_EAX + 0x160)) = (char)uVar4;
    }
  }
  *(int *)(in_EAX + 0x150) = *(int *)(in_EAX + 0x150) + 1;
  iVar1 = *(int *)(in_EAX + 0x15c);
  if (*(int *)(in_EAX + 0x150) == iVar1) {
    *(undefined4 *)(in_EAX + 0x150) = 0;
  }
  piVar3 = (int *)(in_EAX + 0x154);
  *piVar3 = *piVar3 + 1;
  if (*piVar3 == iVar1) {
    *piVar3 = 0;
  }
  piVar3 = (int *)(in_EAX + 0x158);
  *piVar3 = *piVar3 + 1;
  if (*piVar3 == iVar1) {
    *piVar3 = 0;
  }
  return;
}
