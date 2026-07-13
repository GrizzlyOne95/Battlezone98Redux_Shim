/*
 * Entry: 004e31fe
 * Name: NetUtil_ReduceFloat
 * Namespace: Global
 * Signature: ushort NetUtil_ReduceFloat(float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ushort __cdecl NetUtil_ReduceFloat(float param_1)

{
  float fVar1;
  ushort extraout_AX;
  
  fVar1 = 127.0;
  if ((param_1 <= 127.0) && (fVar1 = param_1, param_1 < -127.0)) {
    fVar1 = -127.0;
  }
  floor((double)(fVar1 * 256.0 + 0.5));
  _ftol2();
  return extraout_AX;
}
