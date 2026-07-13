/*
 * Entry: 00418445
 * Name: ClearObjectives
 * Namespace: Global
 * Signature: int ClearObjectives(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl ClearObjectives(lua_State *param_1)

{
  InfoDisplay::ClearObjectives(&infoDisplay);
  return 0;
}
