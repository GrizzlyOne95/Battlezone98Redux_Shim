/*
 * Entry: 00504569
 * Name: Repair_Buffer_Edge
 * Namespace: Global
 * Signature: void Repair_Buffer_Edge(VIDEO_DEVICE * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Repair_Buffer_Edge(VIDEO_DEVICE *param_1)

{
  uchar uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uchar *puVar5;
  uchar *puVar6;
  
  puVar6 = (param_1->Viewport).Buffer;
  if (puVar6 != (uchar *)0x0) {
    iVar3 = (param_1->Viewport).Width;
    uVar4 = (param_1->Viewport).Height;
    puVar6 = puVar6 + iVar3 + -1;
    uVar2 = uVar4 >> 2;
    uVar4 = uVar4 & 3;
    do {
      uVar1 = puVar6[iVar3 + -1];
      *puVar6 = puVar6[-1];
      puVar6[iVar3] = uVar1;
      uVar1 = puVar6[iVar3 * 2 + -1];
      puVar6[iVar3 * 2] = uVar1;
      puVar6[iVar3 * 3] = uVar1;
      puVar6 = puVar6 + iVar3 * 4;
      uVar2 = uVar2 - 1;
    } while (uVar2 != 0);
    for (; uVar4 != 0; uVar4 = uVar4 - 1) {
      *puVar6 = uVar1;
      puVar6 = puVar6 + iVar3;
    }
    puVar5 = puVar6 + iVar3 * -2 + 1 + -iVar3;
    puVar6 = puVar6 + iVar3 * -2 + 1;
    for (; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar6 = *puVar5;
      puVar5 = puVar5 + 1;
      puVar6 = puVar6 + 1;
    }
  }
  return;
}
