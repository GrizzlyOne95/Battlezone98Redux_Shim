/*
 * Entry: 004db025
 * Name: GetHealthColor
 * Namespace: Global
 * Signature: long GetHealthColor(float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl GetHealthColor(float param_1)

{
  long lVar1;
  
  if (0.5 <= param_1) {
    return DisplayInterface::colorGreen;
  }
  if (!NAN(param_1) && 0.25 < param_1 != (param_1 == 0.25)) {
    return DisplayInterface::colorYellow;
  }
  lVar1 = DisplayInterface::colorRed;
  if (NAN(param_1) || 0.0 < param_1 == (param_1 == 0.0)) {
    lVar1 = DisplayInterface::colorBlack;
  }
  return lVar1;
}
