/*
 * Entry: 004ecd7f
 * Name: obj_find_gameflag
 * Namespace: Global
 * Signature: _OBJ76 * obj_find_gameflag(_OBJ76 * param_1, ulong param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_OBJ76 * __cdecl obj_find_gameflag(_OBJ76 *param_1,ulong param_2)

{
  _OBJ76 *p_Var1;
  _OBJ76 *p_Var2;
  
  if ((param_1 != (_OBJ76 *)0x0) && ((param_1->flags & param_2) == 0)) {
    for (p_Var2 = param_1->child; p_Var2 != (_OBJ76 *)0x0; p_Var2 = p_Var2->sibling) {
      p_Var1 = obj_find_gameflag(p_Var2,param_2);
      if (p_Var1 != (_OBJ76 *)0x0) {
        return p_Var1;
      }
    }
    param_1 = (_OBJ76 *)0x0;
  }
  return param_1;
}
