/*
 * Entry: 004ecd16
 * Name: CheckParentDeath
 * Namespace: Global
 * Signature: int CheckParentDeath(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl CheckParentDeath(_OBJ76 *param_1)

{
  _OBJ76 *p_Var1;
  
  p_Var1 = param_1->parent;
  if (((p_Var1 != (_OBJ76 *)0x0) && (p_Var1->parent == (_OBJ76 *)0x0)) &&
     ((p_Var1->flags & 0x200) == 0)) {
    p_Var1->flags = p_Var1->flags | 0x200;
    return 1;
  }
  return 0;
}
