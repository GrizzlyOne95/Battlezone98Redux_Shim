/*
 * Entry: 004169f0
 * Name: LuaPrint
 * Namespace: Global
 * Signature: int LuaPrint(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl LuaPrint(lua_State *param_1)

{
  int iVar1;
  lua_State *unaff_ESI;
  
  SetConsoleTextAttribute(console_stdout,0xf);
  iVar1 = LuaOutput(unaff_ESI);
  return iVar1;
}
