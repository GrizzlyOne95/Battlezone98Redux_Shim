/*
 * Entry: 005bfb4e
 * Name: str_sub
 * Namespace: Global
 * Signature: int str_sub(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl str_sub(lua_State *param_1)

{
  uint uVar1;
  char *pcVar2;
  int iVar3;
  uint uVar4;
  uint local_8;
  
  pcVar2 = luaL_checklstring(param_1,1,&local_8);
  uVar4 = local_8;
  iVar3 = luaL_checkinteger(param_1,2);
  uVar1 = local_8;
  if ((iVar3 < 0) && (iVar3 = iVar3 + 1 + uVar4, iVar3 < 0)) {
    iVar3 = 0;
  }
  uVar4 = luaL_optinteger(param_1,3,-1);
  if (((int)uVar4 < 0) && (uVar4 = uVar4 + 1 + uVar1, (int)uVar4 < 0)) {
    uVar4 = 0;
  }
  if (iVar3 < 1) {
    iVar3 = 1;
  }
  if ((int)local_8 < (int)uVar4) {
    uVar4 = local_8;
  }
  if ((int)uVar4 < iVar3) {
    uVar4 = 0;
    pcVar2 = "";
  }
  else {
    uVar4 = (uVar4 - iVar3) + 1;
    pcVar2 = pcVar2 + iVar3 + -1;
  }
  lua_pushlstring(param_1,pcVar2,uVar4);
  return 1;
}
