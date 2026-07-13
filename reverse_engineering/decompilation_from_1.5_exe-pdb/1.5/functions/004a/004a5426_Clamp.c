/*
 * Entry: 004a5426
 * Name: Clamp
 * Namespace: Global
 * Signature: double Clamp(double param_1, double param_2, double param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

double __cdecl Clamp(double param_1,double param_2,double param_3)

{
  if (param_1 < param_2) {
    return param_2;
  }
  if (param_3 < param_1) {
    return param_3;
  }
  return param_1;
}
