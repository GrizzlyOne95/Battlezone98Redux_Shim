/*
 * Entry: 00520818
 * Name: WaveInit
 * Namespace: Global
 * Signature: void WaveInit(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl WaveInit(void)

{
  int iVar1;
  float10 fVar2;
  int local_8;
  
  local_8 = 0;
  do {
    iVar1 = local_8 + 1;
    fVar2 = (float10)fsin((float10)local_8 * (float10)0.049087387);
    WaveTable[local_8] = (float)fVar2;
    local_8 = iVar1;
  } while (iVar1 < 0x80);
  return;
}
