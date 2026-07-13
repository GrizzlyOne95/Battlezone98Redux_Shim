/*
 * Entry: 005c1188
 * Name: createmetatable
 * Namespace: Global
 * Signature: void createmetatable(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl createmetatable(lua_State *param_1)

{
  lua_State *unaff_ESI;
  
  lua_createtable(unaff_ESI,0,1);
  lua_pushlstring(unaff_ESI,"",0);
  lua_pushvalue(unaff_ESI,-2);
  lua_setmetatable(unaff_ESI,-2);
  lua_settop(unaff_ESI,-2);
  lua_pushvalue(unaff_ESI,-2);
  lua_setfield(unaff_ESI,-2,"__index");
  lua_settop(unaff_ESI,-2);
  return;
}
