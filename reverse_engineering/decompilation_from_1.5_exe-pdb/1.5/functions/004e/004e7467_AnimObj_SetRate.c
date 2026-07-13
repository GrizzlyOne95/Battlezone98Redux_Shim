/*
 * Entry: 004e7467
 * Name: AnimObj_SetRate
 * Namespace: Global
 * Signature: long AnimObj_SetRate(int param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl AnimObj_SetRate(int param_1,float param_2)

{
  if ((uint)param_1 < 0x200) {
    AnimActiveList[param_1].frameRate = param_2;
    return 0;
  }
  return -1;
}
