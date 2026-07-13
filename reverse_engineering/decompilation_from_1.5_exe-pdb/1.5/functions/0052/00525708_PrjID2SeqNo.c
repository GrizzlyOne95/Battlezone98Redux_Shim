/*
 * Entry: 00525708
 * Name: PrjID2SeqNo
 * Namespace: Global
 * Signature: short PrjID2SeqNo(long64 param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

short __cdecl PrjID2SeqNo(long64 param_1)

{
  uint uVar1;
  int iVar2;
  byte *pbVar3;
  
  uVar1 = 0;
  pbVar3 = &stack0x0000000c;
  iVar2 = 0;
  do {
    pbVar3 = pbVar3 + -1;
    if ((*pbVar3 & 0x80) != 0) {
      uVar1 = uVar1 | 1 << ((byte)iVar2 & 0x1f);
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 < 8);
  return (short)uVar1;
}
