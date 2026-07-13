/*
 * Entry: 005bfe1d
 * Name: str_byte
 * Namespace: Global
 * Signature: int str_byte(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl str_byte(lua_State *param_1)

{
  uint uVar1;
  char *pcVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  uint local_8;
  
  pcVar2 = luaL_checklstring(param_1,1,&local_8);
  uVar4 = local_8;
  iVar3 = luaL_optinteger(param_1,2,1);
  uVar1 = local_8;
  if ((iVar3 < 0) && (iVar3 = iVar3 + 1 + uVar4, iVar3 < 0)) {
    iVar3 = 0;
  }
  uVar4 = luaL_optinteger(param_1,3,iVar3);
  if (((int)uVar4 < 0) && (uVar4 = uVar4 + 1 + uVar1, (int)uVar4 < 0)) {
    uVar4 = 0;
  }
  if (iVar3 < 1) {
    iVar3 = 1;
  }
  if (local_8 < uVar4) {
    uVar4 = local_8;
  }
  if ((int)uVar4 < iVar3) {
    iVar5 = 0;
  }
  else {
    iVar5 = (uVar4 - iVar3) + 1;
    if (iVar5 + iVar3 <= (int)uVar4) {
      luaL_error(param_1,"string slice too long");
    }
    luaL_checkstack(param_1,iVar5,"string slice too long");
    iVar6 = 0;
    if (0 < iVar5) {
      do {
        lua_pushinteger(param_1,(uint)(byte)pcVar2[iVar6 + iVar3 + -1]);
        iVar6 = iVar6 + 1;
      } while (iVar6 < iVar5);
    }
  }
  return iVar5;
}
