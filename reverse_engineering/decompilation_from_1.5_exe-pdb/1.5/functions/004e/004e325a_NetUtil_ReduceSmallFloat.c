/*
 * Entry: 004e325a
 * Name: NetUtil_ReduceSmallFloat
 * Namespace: Global
 * Signature: uchar NetUtil_ReduceSmallFloat(float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uchar __cdecl NetUtil_ReduceSmallFloat(float param_1)

{
  float fVar1;
  uchar extraout_AL;
  
  fVar1 = 1.0;
  if ((param_1 <= 1.0) && (fVar1 = param_1, param_1 < -1.0)) {
    fVar1 = -1.0;
  }
  floor((double)(fVar1 * 127.0 + 0.5));
  _ftol2();
  return extraout_AL;
}
