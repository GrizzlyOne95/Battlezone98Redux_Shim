/*
 * Entry: 0040b7a4
 * Name: AOI::GetValues
 * Namespace: AOI
 * Signature: int * GetValues(int param_1, bool param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int * __cdecl AOI::GetValues(int param_1,bool param_2)

{
  if (recalc) {
    DoRecalc();
  }
  return values[!param_2][param_1];
}
