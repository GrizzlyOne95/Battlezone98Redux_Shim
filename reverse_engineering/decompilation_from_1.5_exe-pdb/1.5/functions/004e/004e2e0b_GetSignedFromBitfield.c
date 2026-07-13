/*
 * Entry: 004e2e0b
 * Name: GetSignedFromBitfield
 * Namespace: Global
 * Signature: int GetSignedFromBitfield(void * param_1, uint param_2, uint param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetSignedFromBitfield(void *param_1,uint param_2,uint param_3)

{
  uint uVar1;
  
  uVar1 = GetUnsignedFromBitfield(param_1,param_2,param_3);
  return -((int)uVar1 >> ((byte)param_3 - 1 & 0x1f) & 1U) << ((byte)param_3 & 0x1f) | uVar1;
}
