/*
 * Entry: 005bf2b5
 * Name: db_errorfb
 * Namespace: Global
 * Signature: int db_errorfb(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl db_errorfb(lua_State *param_1)

{
  char cVar1;
  bool bVar2;
  lua_State *plVar3;
  int iVar4;
  uint uVar5;
  int *unaff_EDI;
  char *pcVar6;
  uint uVar7;
  int local_74;
  lua_Debug local_6c;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  bVar2 = true;
  plVar3 = getthread(param_1,unaff_EDI);
  iVar4 = lua_isnumber(param_1,local_74 + 2);
  if (iVar4 == 0) {
    uVar5 = (uint)(param_1 == plVar3);
  }
  else {
    uVar5 = lua_tointeger(param_1,local_74 + 2);
    lua_settop(param_1,-2);
  }
  iVar4 = lua_gettop(param_1);
  if (iVar4 == local_74) {
    uVar7 = 0;
    pcVar6 = "";
  }
  else {
    iVar4 = lua_isstring(param_1,local_74 + 1);
    if (iVar4 == 0) {
      return 1;
    }
    uVar7 = 1;
    pcVar6 = "\n";
  }
  lua_pushlstring(param_1,pcVar6,uVar7);
  lua_pushlstring(param_1,"stack traceback:",0x10);
  iVar4 = lua_getstack(plVar3,uVar5,&local_6c);
  while (iVar4 != 0) {
    uVar7 = uVar5 + 1;
    if (((int)uVar7 < 0xd) || (!bVar2)) {
      lua_pushlstring(param_1,"\n\t",2);
      lua_getinfo(plVar3,"Snl",&local_6c);
      lua_pushfstring(param_1,"%s:");
      if (0 < local_6c.currentline) {
        lua_pushfstring(param_1,"%d:");
      }
      if (*local_6c.namewhat == '\0') {
        cVar1 = *local_6c.what;
        if (cVar1 == 'm') {
          lua_pushfstring(param_1," in main chunk");
        }
        else if ((cVar1 == 'C') || (cVar1 == 't')) {
          lua_pushlstring(param_1," ?",2);
        }
        else {
          lua_pushfstring(param_1," in function <%s:%d>");
        }
      }
      else {
        lua_pushfstring(param_1," in function \'%s\'");
      }
      iVar4 = lua_gettop(param_1);
      lua_concat(param_1,iVar4 - local_74);
    }
    else {
      iVar4 = lua_getstack(plVar3,uVar5 + 0xb,&local_6c);
      if (iVar4 != 0) {
        lua_pushlstring(param_1,"\n\t...",5);
        iVar4 = lua_getstack(plVar3,uVar5 + 0xb,&local_6c);
        uVar5 = uVar7;
        while (iVar4 != 0) {
          iVar4 = lua_getstack(plVar3,uVar5 + 0xb,&local_6c);
          uVar5 = uVar5 + 1;
        }
      }
      bVar2 = false;
      uVar7 = uVar5;
    }
    iVar4 = lua_getstack(plVar3,uVar7,&local_6c);
    uVar5 = uVar7;
  }
  iVar4 = lua_gettop(param_1);
  lua_concat(param_1,iVar4 - local_74);
  return 1;
}
