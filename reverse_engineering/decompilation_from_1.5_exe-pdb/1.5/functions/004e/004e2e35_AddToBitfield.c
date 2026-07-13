/*
 * Entry: 004e2e35
 * Name: AddToBitfield
 * Namespace: Global
 * Signature: void AddToBitfield(int param_1, void * param_2, uint param_3, uint param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AddToBitfield(int param_1,void *param_2,uint param_3,uint param_4)

{
  int iVar1;
  uint *puVar2;
  byte bVar3;
  uint uVar5;
  uint uVar6;
  byte bVar4;
  
  puVar2 = (uint *)((param_3 >> 3) + (int)param_2 & 0xfffffffc);
  iVar1 = param_3 + ((int)param_2 - (int)puVar2) * 8;
  uVar5 = param_4 + iVar1;
  bVar3 = (byte)iVar1;
  bVar4 = (byte)uVar5;
  if (uVar5 < 0x20) {
    uVar5 = (1 << (bVar4 & 0x1f)) - (1 << (bVar3 & 0x1f));
    uVar6 = param_1 << (bVar3 & 0x1f);
  }
  else {
    uVar5 = -1 << (bVar3 & 0x1f);
    *puVar2 = param_1 << (bVar3 & 0x1f) & uVar5 | ~uVar5 & *puVar2;
    puVar2 = puVar2 + 1;
    uVar5 = (1 << (bVar4 - 0x20 & 0x1f)) - 1;
    uVar6 = param_1 >> (0x20 - bVar3 & 0x1f);
  }
  *puVar2 = uVar6 & uVar5 | ~uVar5 & *puVar2;
  return;
}
