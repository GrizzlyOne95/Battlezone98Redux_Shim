/*
 * Entry: 004ecc37
 * Name: is_ai_vhcl
 * Namespace: Global
 * Signature: int is_ai_vhcl(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl is_ai_vhcl(_OBJ76 *param_1)

{
  return (byte)~(byte)param_1->flags >> 4 & 1;
}
