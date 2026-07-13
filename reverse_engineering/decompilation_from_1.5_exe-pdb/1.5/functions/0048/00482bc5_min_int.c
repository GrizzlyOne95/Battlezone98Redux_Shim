/*
 * Entry: 00482bc5
 * Name: min<int>
 * Namespace: Global
 * Signature: int min<int>(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl min<int>(int param_1,int param_2)

{
  if (param_2 <= param_1) {
    param_1 = param_2;
  }
  return param_1;
}
