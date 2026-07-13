/*
 * Entry: 005c2bdc
 * Name: luaB_loadstring
 * Namespace: Global
 * Signature: int luaB_loadstring(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaB_loadstring(lua_State *param_1)

{
  char *pcVar1;
  char *pcVar2;
  int iVar3;
  uint local_8;
  
  pcVar1 = luaL_checklstring(param_1,1,&local_8);
  pcVar2 = luaL_optlstring(param_1,2,pcVar1,(uint *)0x0);
  iVar3 = luaL_loadbuffer(param_1,pcVar1,local_8,pcVar2);
  iVar3 = load_aux(param_1,iVar3);
  return iVar3;
}
