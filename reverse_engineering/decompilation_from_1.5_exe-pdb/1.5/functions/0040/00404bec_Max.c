/*
 * Entry: 00404bec
 * Name: Max
 * Namespace: Global
 * Signature: int Max(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Max(int param_1,int param_2)

{
  if (param_1 < param_2) {
    param_1 = param_2;
  }
  return param_1;
}
