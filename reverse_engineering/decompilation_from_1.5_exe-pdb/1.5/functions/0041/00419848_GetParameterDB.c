/*
 * Entry: 00419848
 * Name: GetParameterDB
 * Namespace: Global
 * Signature: ParameterDB * GetParameterDB(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ParameterDB * __cdecl GetParameterDB(lua_State *param_1,int param_2)

{
  ParameterDB *pPVar1;
  
  pPVar1 = luaL_checkudata(param_1,param_2,"ParameterDB");
  return pPVar1;
}
