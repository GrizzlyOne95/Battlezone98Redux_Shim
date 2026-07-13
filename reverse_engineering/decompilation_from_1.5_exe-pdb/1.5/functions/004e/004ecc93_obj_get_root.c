/*
 * Entry: 004ecc93
 * Name: obj_get_root
 * Namespace: Global
 * Signature: _OBJ76 * obj_get_root(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_OBJ76 * __cdecl obj_get_root(_OBJ76 *param_1)

{
  _OBJ76 *p_Var1;
  
  do {
    p_Var1 = param_1;
    param_1 = p_Var1->parent;
  } while (param_1 != (_OBJ76 *)0x0);
  return p_Var1;
}
