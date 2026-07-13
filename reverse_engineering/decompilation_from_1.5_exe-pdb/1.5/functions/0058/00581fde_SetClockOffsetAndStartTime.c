/*
 * Entry: 00581fde
 * Name: SetClockOffsetAndStartTime
 * Namespace: Global
 * Signature: void SetClockOffsetAndStartTime(ulong param_1, int param_2, ulong param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SetClockOffsetAndStartTime(ulong param_1,int param_2,ulong param_3)

{
  BAddOffset = param_2;
  dwOffset = param_1;
  dwStartTime = param_3;
  return;
}
