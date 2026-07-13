/*
 * Entry: 004e332b
 * Name: NetUtil_ReducePositionFloat
 * Namespace: Global
 * Signature: ushort NetUtil_ReducePositionFloat(float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ushort __cdecl NetUtil_ReducePositionFloat(float param_1)

{
  ushort extraout_AX;
  
  if (param_1 < -2047.0) {
    param_1 = -2047.0;
  }
  if (!NAN(param_1) && 2047.0 < param_1 != (param_1 == 2047.0)) {
    param_1 = 2047.0;
  }
  floor((double)(param_1 * 0.0625 + 0.5));
  _ftol2();
  return extraout_AX;
}
