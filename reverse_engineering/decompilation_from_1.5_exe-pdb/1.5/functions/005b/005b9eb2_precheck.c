/*
 * Entry: 005b9eb2
 * Name: precheck
 * Namespace: Global
 * Signature: int precheck(Proto * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl precheck(Proto *param_1)

{
  byte bVar1;
  int iVar2;
  int in_EAX;
  
  if (*(byte *)(in_EAX + 0x4b) < 0xfb) {
    bVar1 = *(byte *)(in_EAX + 0x4a);
    if (((bVar1 & 1) + (uint)*(byte *)(in_EAX + 0x49) <= (uint)*(byte *)(in_EAX + 0x4b)) &&
       ((((bVar1 & 4) == 0 || ((bVar1 & 1) != 0)) &&
        (*(int *)(in_EAX + 0x24) <= (int)(uint)*(byte *)(in_EAX + 0x48))))) {
      iVar2 = *(int *)(in_EAX + 0x2c);
      if ((((*(int *)(in_EAX + 0x30) == iVar2) || (*(int *)(in_EAX + 0x30) == 0)) && (0 < iVar2)) &&
         (((byte)*(undefined4 *)(*(int *)(in_EAX + 0xc) + -4 + iVar2 * 4) & 0x3f) == 0x1e)) {
        return 1;
      }
    }
  }
  return 0;
}
