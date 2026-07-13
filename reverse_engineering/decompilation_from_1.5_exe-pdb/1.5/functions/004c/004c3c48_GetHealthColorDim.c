/*
 * Entry: 004c3c48
 * Name: GetHealthColorDim
 * Namespace: Global
 * Signature: long GetHealthColorDim(float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl GetHealthColorDim(float param_1)

{
  long lVar1;
  
  if (!NAN(param_1) && 0.5 < param_1 != (param_1 == 0.5)) {
    return DisplayInterface::colorDkGreen;
  }
  if (!NAN(param_1) && 0.25 < param_1 != (param_1 == 0.25)) {
    return DisplayInterface::colorDkYellow;
  }
  lVar1 = DisplayInterface::colorDkRed;
  if (NAN(param_1) || 0.0 < param_1 == (param_1 == 0.0)) {
    lVar1 = DisplayInterface::colorBlack;
  }
  return lVar1;
}
