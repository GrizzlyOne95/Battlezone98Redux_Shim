/*
 * Entry: 004e2dc6
 * Name: GetUnsignedFromBitfield
 * Namespace: Global
 * Signature: int GetUnsignedFromBitfield(void * param_1, uint param_2, uint param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetUnsignedFromBitfield(void *param_1,uint param_2,uint param_3)

{
  int iVar1;
  uint *puVar2;
  byte bVar3;
  uint uVar4;
  
  puVar2 = (uint *)((param_2 >> 3) + (int)param_1 & 0xfffffffc);
  iVar1 = param_2 + ((int)param_1 - (int)puVar2) * 8;
  bVar3 = (byte)iVar1;
  uVar4 = *puVar2 >> (bVar3 & 0x1f);
  if (0x1f < iVar1 + param_3) {
    uVar4 = uVar4 | puVar2[1] << (0x20 - bVar3 & 0x1f);
  }
  return (1 << ((byte)param_3 & 0x1f)) - 1U & uVar4;
}
