/*
 * Entry: 004ecc22
 * Name: is_user_vhcl
 * Namespace: Global
 * Signature: int is_user_vhcl(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl is_user_vhcl(_OBJ76 *param_1)

{
  if ((param_1 != (_OBJ76 *)0x0) && ((param_1->flags & 0x10) != 0)) {
    return 1;
  }
  return 0;
}
