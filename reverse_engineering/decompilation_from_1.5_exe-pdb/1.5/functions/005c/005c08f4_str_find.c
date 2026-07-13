/*
 * Entry: 005c08f4
 * Name: str_find
 * Namespace: Global
 * Signature: int str_find(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl str_find(lua_State *param_1)

{
  int iVar1;
  
  iVar1 = str_find_aux(param_1,1);
  return iVar1;
}
