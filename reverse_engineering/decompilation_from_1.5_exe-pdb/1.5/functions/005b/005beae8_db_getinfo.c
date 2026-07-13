/*
 * Entry: 005beae8
 * Name: db_getinfo
 * Namespace: Global
 * Signature: int db_getinfo(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl db_getinfo(lua_State *param_1)

{
  lua_State *plVar1;
  char *pcVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int *unaff_EDI;
  lua_Debug *plVar6;
  char *local_70;
  lua_Debug local_6c;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  plVar1 = getthread(param_1,unaff_EDI);
  iVar4 = (int)local_70 + 2;
  pcVar2 = luaL_optlstring(param_1,iVar4,"flnSu",(uint *)0x0);
  iVar5 = (int)local_70 + 1;
  iVar3 = lua_isnumber(param_1,iVar5);
  if (iVar3 == 0) {
    iVar3 = lua_type(param_1,iVar5);
    if (iVar3 == 6) {
      lua_pushfstring(param_1,">%s");
      local_70 = lua_tolstring(param_1,-1,(uint *)0x0);
      lua_pushvalue(param_1,iVar5);
      lua_xmove(param_1,plVar1,1);
      goto LAB_005beb9e;
    }
    pcVar2 = "function or level expected";
LAB_005becd4:
    iVar4 = luaL_argerror(param_1,iVar5,pcVar2);
  }
  else {
    plVar6 = &local_6c;
    iVar5 = lua_tointeger(param_1,iVar5);
    iVar5 = lua_getstack(plVar1,iVar5,plVar6);
    local_70 = pcVar2;
    if (iVar5 == 0) {
      lua_pushnil(param_1);
    }
    else {
LAB_005beb9e:
      iVar5 = lua_getinfo(plVar1,local_70,&local_6c);
      if (iVar5 == 0) {
        pcVar2 = "invalid option";
        iVar5 = iVar4;
        goto LAB_005becd4;
      }
      lua_createtable(param_1,0,2);
      pcVar2 = strchr(local_70,0x53);
      if (pcVar2 != (char *)0x0) {
        settabss(param_1,"source",local_6c.source);
        settabss(param_1,"short_src",local_6c.short_src);
        settabsi(param_1,"linedefined",local_6c.linedefined);
        settabsi(param_1,"lastlinedefined",local_6c.lastlinedefined);
        settabss(param_1,"what",local_6c.what);
      }
      pcVar2 = strchr(local_70,0x6c);
      if (pcVar2 != (char *)0x0) {
        settabsi(param_1,"currentline",local_6c.currentline);
      }
      pcVar2 = strchr(local_70,0x75);
      if (pcVar2 != (char *)0x0) {
        settabsi(param_1,"nups",local_6c.nups);
      }
      pcVar2 = strchr(local_70,0x6e);
      if (pcVar2 != (char *)0x0) {
        settabss(param_1,"name",local_6c.name);
        settabss(param_1,"namewhat",local_6c.namewhat);
      }
      pcVar2 = strchr(local_70,0x4c);
      if (pcVar2 != (char *)0x0) {
        treatstackoption(plVar1,(lua_State *)"activelines",(char *)unaff_EDI);
      }
      pcVar2 = strchr(local_70,0x66);
      if (pcVar2 != (char *)0x0) {
        treatstackoption(plVar1,(lua_State *)"func",(char *)unaff_EDI);
      }
    }
    iVar4 = 1;
  }
  return iVar4;
}
