/*
 * Entry: 00416a0a
 * Name: LuaWarning
 * Namespace: Global
 * Signature: int LuaWarning(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl LuaWarning(lua_State *param_1)

{
  int iVar1;
  lua_State *unaff_ESI;
  
  SetConsoleTextAttribute(console_stdout,0xe);
  iVar1 = LuaOutput(unaff_ESI);
  return iVar1;
}
