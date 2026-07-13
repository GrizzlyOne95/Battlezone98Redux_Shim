/*
 * Entry: 00404bdd
 * Name: Min
 * Namespace: Global
 * Signature: int Min(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Min(int param_1,int param_2)

{
  if (param_2 < param_1) {
    param_1 = param_2;
  }
  return param_1;
}
