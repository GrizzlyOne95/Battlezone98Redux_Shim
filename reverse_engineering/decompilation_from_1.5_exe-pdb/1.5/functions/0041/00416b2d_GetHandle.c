/*
 * Entry: 00416b2d
 * Name: GetHandle
 * Namespace: Global
 * Signature: int GetHandle(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetHandle(lua_State *param_1,int param_2)

{
  void *pvVar1;
  
  pvVar1 = luaL_testudata(param_1,param_2,"Handle");
  return (int)pvVar1;
}
