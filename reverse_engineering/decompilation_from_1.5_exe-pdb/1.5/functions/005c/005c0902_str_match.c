/*
 * Entry: 005c0902
 * Name: str_match
 * Namespace: Global
 * Signature: int str_match(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl str_match(lua_State *param_1)

{
  int iVar1;
  
  iVar1 = str_find_aux(param_1,0);
  return iVar1;
}
