/*
 * Entry: 00582ee8
 * Name: WiggleOneShot
 * Namespace: Global
 * Signature: void WiggleOneShot(float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl WiggleOneShot(float param_1)

{
  if (TargetOffset < param_1) {
    TargetOffset = param_1;
    WiggleBurgerOn = 1;
    WiggleOneShotOn = 1;
    CurrentOffset = param_1 - 1.0;
    return;
  }
  return;
}
