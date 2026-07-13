/*
 * Entry: 00419d0a
 * Name: GetMapTRNFilename
 * Namespace: Global
 * Signature: int GetMapTRNFilename(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetMapTRNFilename(lua_State *param_1)

{
  lua_pushstring(param_1,missionName);
  return 1;
}
