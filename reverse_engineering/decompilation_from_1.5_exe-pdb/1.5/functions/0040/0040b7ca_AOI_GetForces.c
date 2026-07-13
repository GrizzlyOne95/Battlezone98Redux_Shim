/*
 * Entry: 0040b7ca
 * Name: AOI::GetForces
 * Namespace: AOI
 * Signature: int * GetForces(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int * __cdecl AOI::GetForces(int param_1)

{
  if (recalc) {
    DoRecalc();
  }
  return forces[param_1];
}
