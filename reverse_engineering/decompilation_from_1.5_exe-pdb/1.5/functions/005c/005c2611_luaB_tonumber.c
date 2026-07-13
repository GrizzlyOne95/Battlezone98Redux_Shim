/*
 * Entry: 005c2611
 * Name: luaB_tonumber
 * Namespace: Global
 * Signature: int luaB_tonumber(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaB_tonumber(lua_State *param_1)

{
  int iVar1;
  byte *_Str;
  ulong uVar2;
  undefined4 unaff_EDI;
  double dVar3;
  byte *local_8;
  
  iVar1 = luaL_optinteger(param_1,2,10);
  if (iVar1 == 10) {
    luaL_checkany(param_1,1);
    iVar1 = lua_isnumber(param_1,1);
    if (iVar1 != 0) {
      dVar3 = lua_tonumber(param_1,1);
      lua_pushnumber(param_1,(double)CONCAT44(unaff_EDI,(int)((ulonglong)dVar3 >> 0x20)));
      return 1;
    }
  }
  else {
    _Str = (byte *)luaL_checklstring(param_1,1,(uint *)0x0);
    if ((iVar1 < 2) || (0x24 < iVar1)) {
      luaL_argerror(param_1,2,"base out of range");
    }
    uVar2 = strtoul((char *)_Str,(char **)&local_8,iVar1);
    if (_Str != local_8) {
      while (iVar1 = isspace((uint)*local_8), iVar1 != 0) {
        local_8 = local_8 + 1;
      }
      if (*local_8 == 0) {
        dVar3 = (double)(int)uVar2;
        if ((int)uVar2 < 0) {
          dVar3 = dVar3 + 4294967296.0;
        }
        lua_pushnumber(param_1,(double)CONCAT44(unaff_EDI,(int)((ulonglong)dVar3 >> 0x20)));
        return 1;
      }
    }
  }
  lua_pushnil(param_1);
  return 1;
}
