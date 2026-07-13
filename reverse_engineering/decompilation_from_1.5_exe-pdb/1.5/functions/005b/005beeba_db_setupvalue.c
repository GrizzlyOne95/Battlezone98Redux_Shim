/*
 * Entry: 005beeba
 * Name: db_setupvalue
 * Namespace: Global
 * Signature: int db_setupvalue(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl db_setupvalue(lua_State *param_1)

{
  int iVar1;
  
  luaL_checkany(param_1,3);
  iVar1 = auxupvalue((lua_State *)0x0,(int)param_1);
  return iVar1;
}
