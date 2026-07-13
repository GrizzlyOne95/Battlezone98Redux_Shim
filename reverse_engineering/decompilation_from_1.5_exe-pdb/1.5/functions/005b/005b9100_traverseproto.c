/*
 * Entry: 005b9100
 * Name: traverseproto
 * Namespace: Global
 * Signature: void traverseproto(global_State * param_1, Proto * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl traverseproto(global_State *param_1,Proto *param_2)

{
  byte *pbVar1;
  GCObject *pGVar2;
  undefined4 *puVar3;
  int *piVar4;
  int in_EDX;
  int extraout_EDX;
  int extraout_EDX_00;
  int iVar5;
  int iVar6;
  
  if (*(int *)(in_EDX + 0x20) != 0) {
    pbVar1 = (byte *)(*(int *)(in_EDX + 0x20) + 5);
    *pbVar1 = *pbVar1 & 0xfc;
  }
  iVar6 = 0;
  if (0 < *(int *)(in_EDX + 0x28)) {
    iVar5 = 0;
    do {
      puVar3 = (undefined4 *)(*(int *)(in_EDX + 8) + iVar5);
      if ((3 < (int)puVar3[2]) && (pGVar2 = (GCObject *)*puVar3, ((pGVar2->gch).marked & 3) != 0)) {
        reallymarkobject(param_1,pGVar2);
        in_EDX = extraout_EDX;
      }
      iVar6 = iVar6 + 1;
      iVar5 = iVar5 + 0x10;
    } while (iVar6 < *(int *)(in_EDX + 0x28));
  }
  iVar6 = 0;
  if (0 < *(int *)(in_EDX + 0x24)) {
    do {
      if (*(int *)(*(int *)(in_EDX + 0x1c) + iVar6 * 4) != 0) {
        pbVar1 = (byte *)(*(int *)(*(int *)(in_EDX + 0x1c) + iVar6 * 4) + 5);
        *pbVar1 = *pbVar1 & 0xfc;
      }
      iVar6 = iVar6 + 1;
    } while (iVar6 < *(int *)(in_EDX + 0x24));
  }
  iVar6 = 0;
  if (0 < *(int *)(in_EDX + 0x34)) {
    do {
      piVar4 = (int *)(*(int *)(in_EDX + 0x10) + iVar6 * 4);
      if ((*piVar4 != 0) && (pGVar2 = (GCObject *)*piVar4, ((pGVar2->gch).marked & 3) != 0)) {
        reallymarkobject(param_1,pGVar2);
        in_EDX = extraout_EDX_00;
      }
      iVar6 = iVar6 + 1;
    } while (iVar6 < *(int *)(in_EDX + 0x34));
  }
  iVar6 = 0;
  if (0 < *(int *)(in_EDX + 0x38)) {
    iVar5 = 0;
    do {
      if (*(int *)(iVar5 + *(int *)(in_EDX + 0x18)) != 0) {
        piVar4 = (int *)(*(int *)(in_EDX + 0x18) + iVar5);
        *(byte *)(*piVar4 + 5) = *(byte *)(*piVar4 + 5) & 0xfc;
      }
      iVar6 = iVar6 + 1;
      iVar5 = iVar5 + 0xc;
    } while (iVar6 < *(int *)(in_EDX + 0x38));
  }
  return;
}
