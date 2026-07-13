/*
 * Entry: 00510d5f
 * Name: Id_Claim
 * Namespace: Global
 * Signature: int Id_Claim(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Id_Claim(int param_1)

{
  if (id_nextavail <= param_1) {
    id_nextavail = param_1 + 1;
  }
  return 1;
}
