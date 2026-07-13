/*
 * Entry: 0044f2b0
 * Name: Material
 * Namespace: Global
 * Signature: int Material(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Material(int param_1)

{
  return sMaterial[param_1 & 0xf];
}
