/*
 * Entry: 00404bfb
 * Name: Clamp
 * Namespace: Global
 * Signature: int Clamp(int param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Clamp(int param_1,int param_2,int param_3)

{
  if (param_1 < param_2) {
    return param_2;
  }
  if (param_3 < param_1) {
    param_1 = param_3;
  }
  return param_1;
}
