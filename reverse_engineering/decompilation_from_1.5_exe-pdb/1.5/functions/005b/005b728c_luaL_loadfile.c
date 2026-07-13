/*
 * Entry: 005b728c
 * Name: luaL_loadfile
 * Namespace: Global
 * Signature: int luaL_loadfile(lua_State * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl luaL_loadfile(lua_State *param_1,char *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  undefined4 local_210;
  FILE *local_20c;
  undefined1 local_198 [400];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_198;
  iVar1 = lua_gettop(param_1);
  local_210 = 0;
  iVar1 = iVar1 + 1;
  if (param_2 == (char *)0x0) {
    lua_pushlstring(param_1,"=stdin",6);
    local_20c = __iob_func();
LAB_005b72e4:
    iVar2 = getc(local_20c);
    if (iVar2 == 0x23) {
      local_210 = 1;
      do {
        iVar2 = getc(local_20c);
        if (iVar2 == -1) break;
      } while (iVar2 != 10);
      if (iVar2 == 10) {
        iVar2 = getc(local_20c);
      }
    }
    if ((iVar2 == 0x1b) && (param_2 != (char *)0x0)) {
      local_20c = freopen(param_2,"rb",local_20c);
      if (local_20c == (FILE *)0x0) {
        pcVar4 = "reopen";
        goto LAB_005b7369;
      }
      do {
        iVar2 = getc(local_20c);
        if (iVar2 == -1) break;
      } while (iVar2 != 0x1b);
      local_210 = 0;
    }
    ungetc(iVar2,local_20c);
    pcVar4 = lua_tolstring(param_1,-1,(uint *)0x0);
    iVar3 = lua_load(param_1,getF,&local_210,pcVar4);
    iVar2 = ferror(local_20c);
    if (param_2 != (char *)0x0) {
      fclose(local_20c);
    }
    if (iVar2 == 0) {
      lua_remove(param_1,iVar1);
    }
    else {
      lua_settop(param_1,iVar1);
      iVar3 = errfile(param_1,"read",iVar1);
    }
  }
  else {
    lua_pushfstring(param_1,"@%s");
    local_20c = fopen(param_2,"r");
    if (local_20c != (FILE *)0x0) goto LAB_005b72e4;
    pcVar4 = "open";
LAB_005b7369:
    local_20c = (FILE *)0x0;
    iVar3 = errfile(param_1,pcVar4,iVar1);
  }
  return iVar3;
}
