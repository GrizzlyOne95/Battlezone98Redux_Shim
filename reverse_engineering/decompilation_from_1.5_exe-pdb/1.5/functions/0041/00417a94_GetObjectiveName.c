/*
 * Entry: 00417a94
 * Name: GetObjectiveName
 * Namespace: Global
 * Signature: int GetObjectiveName(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetObjectiveName(lua_State *param_1)

{
  int iVar1;
  char *pcVar2;
  
  iVar1 = GetHandle(param_1,1);
  pcVar2 = GetObjectiveName(iVar1);
  if (pcVar2 != (char *)0x0) {
    lua_pushstring(param_1,pcVar2);
    return 1;
  }
  return 0;
}
