/*
 * Entry: 004190c4
 * Name: DisplayMessage
 * Namespace: Global
 * Signature: int DisplayMessage(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl DisplayMessage(lua_State *param_1)

{
  lua_tolstring(param_1,1,(uint *)0x0);
  DisplayMessage("%s");
  return 0;
}
