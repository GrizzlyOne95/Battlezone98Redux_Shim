/*
 * Entry: 005c0b9d
 * Name: str_gsub
 * Namespace: Global
 * Signature: int str_gsub(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl str_gsub(lua_State *param_1)

{
  char cVar1;
  luaL_Buffer *plVar2;
  char *pcVar3;
  char *unaff_EDI;
  luaL_Buffer *plVar4;
  MatchState local_338;
  int local_228;
  uint local_224;
  uint local_220;
  int local_21c;
  luaL_Buffer *local_218;
  luaL_Buffer local_214;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)(local_338.capture + 0x12);
  plVar2 = (luaL_Buffer *)luaL_checklstring(param_1,1,&local_224);
  pcVar3 = luaL_checklstring(param_1,2,(uint *)0x0);
  local_218 = (luaL_Buffer *)lua_type(param_1,3);
  local_228 = luaL_optinteger(param_1,4,local_224 + 1);
  cVar1 = *pcVar3;
  if (cVar1 == '^') {
    pcVar3 = pcVar3 + 1;
  }
  local_220 = (uint)(cVar1 == '^');
  local_21c = 0;
  if ((((local_218 != (luaL_Buffer *)0x3) && (local_218 != (luaL_Buffer *)0x4)) &&
      (local_218 != (luaL_Buffer *)0x6)) && (local_218 != (luaL_Buffer *)0x5)) {
    luaL_argerror(param_1,3,"string/function/table expected");
  }
  luaL_buffinit(param_1,&local_214);
  local_338.src_end = plVar2->buffer + (local_224 - 0xc);
  local_338.L = param_1;
  plVar4 = plVar2;
  local_338.src_init = (char *)plVar2;
  if (local_228 < 1) {
LAB_005c0d07:
    luaL_addlstring(&local_214,(char *)plVar4,(int)local_338.src_end - (int)plVar4);
    luaL_pushresult(&local_214);
    lua_pushinteger(param_1,local_21c);
    return 2;
  }
  do {
    local_338.level = 0;
    local_218 = (luaL_Buffer *)match(&local_338,(char *)plVar2,pcVar3);
    if (local_218 == (luaL_Buffer *)0x0) {
LAB_005c0cb9:
      plVar4 = plVar2;
      if (local_338.src_end <= plVar2) goto LAB_005c0d07;
      if (&local_8 <= local_214.p) {
        luaL_prepbuffer(&local_214);
      }
      *local_214.p = *(undefined1 *)&plVar2->p;
      local_214.p = (char *)((int)local_214.p + 1);
      plVar4 = (luaL_Buffer *)((int)&plVar2->p + 1);
    }
    else {
      local_21c = local_21c + 1;
      add_value((MatchState *)&local_214,plVar2,(char *)local_218,unaff_EDI);
      plVar4 = local_218;
      if (local_218 <= plVar2) goto LAB_005c0cb9;
    }
    if ((local_220 != 0) || (plVar2 = plVar4, local_228 <= local_21c)) goto LAB_005c0d07;
  } while( true );
}
