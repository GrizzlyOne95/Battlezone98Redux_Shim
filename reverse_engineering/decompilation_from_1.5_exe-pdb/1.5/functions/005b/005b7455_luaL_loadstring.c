/*
 * Entry: 005b7455
 * Name: luaL_loadstring
 * Namespace: Global
 * Signature: int luaL_loadstring(lua_State * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaL_loadstring(lua_State *param_1,char *param_2)

{
  char cVar1;
  char *pcVar2;
  int iVar3;
  
  pcVar2 = param_2;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  iVar3 = luaL_loadbuffer(param_1,param_2,(int)pcVar2 - (int)(param_2 + 1),param_2);
  return iVar3;
}
