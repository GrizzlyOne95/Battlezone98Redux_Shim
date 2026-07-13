/*
 * Entry: 00545029
 * Name: SetZBufferRange
 * Namespace: Global
 * Signature: void SetZBufferRange(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SetZBufferRange(int param_1)

{
  if (param_1 == 0) {
    k0 = 1.0000603;
    k1 = -0.099005975;
  }
  else if (param_1 == 1) {
    k0 = 0.12500754;
    k1 = -0.012375747;
  }
  else {
    k0 = 1.0000528;
    k1 = -0.086630225;
  }
  return;
}
