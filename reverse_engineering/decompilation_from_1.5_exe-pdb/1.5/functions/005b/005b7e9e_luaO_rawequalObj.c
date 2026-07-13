/*
 * Entry: 005b7e9e
 * Name: luaO_rawequalObj
 * Namespace: Global
 * Signature: int luaO_rawequalObj(lua_TValue * param_1, lua_TValue * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaO_rawequalObj(lua_TValue *param_1,lua_TValue *param_2)

{
  int iVar1;
  
  iVar1 = param_1->tt;
  if (iVar1 != param_2->tt) {
    return 0;
  }
  if (iVar1 != 0) {
    if (((iVar1 == 1) || (iVar1 == 2)) || (iVar1 != 3)) {
      return (uint)((param_1->value).gc == (param_2->value).gc);
    }
    if ((param_2->value).n != (param_1->value).n) {
      return 0;
    }
  }
  return 1;
}
