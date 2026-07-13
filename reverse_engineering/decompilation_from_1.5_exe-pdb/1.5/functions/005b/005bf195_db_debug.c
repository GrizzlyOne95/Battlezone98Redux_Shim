/*
 * Entry: 005bf195
 * Name: db_debug
 * Namespace: Global
 * Signature: int db_debug(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl db_debug(lua_State *param_1)

{
  char cVar1;
  lua_State *plVar2;
  FILE *pFVar3;
  char *pcVar4;
  int iVar5;
  char *pcVar6;
  bool bVar7;
  lua_State *local_104;
  char local_100 [252];
  uint local_4;
  
  local_4 = __security_cookie ^ (uint)&local_104;
  local_104 = param_1;
  pFVar3 = __iob_func();
  fputs("lua_debug> ",pFVar3 + 2);
  pFVar3 = __iob_func();
  pcVar4 = fgets(local_100,0xfa,pFVar3);
  plVar2 = local_104;
  do {
    if (pcVar4 == (char *)0x0) {
      return 0;
    }
    iVar5 = 6;
    bVar7 = true;
    pcVar4 = local_100;
    pcVar6 = "cont\n";
    do {
      if (iVar5 == 0) break;
      iVar5 = iVar5 + -1;
      bVar7 = *pcVar4 == *pcVar6;
      pcVar4 = pcVar4 + 1;
      pcVar6 = pcVar6 + 1;
    } while (bVar7);
    if (bVar7) {
      return 0;
    }
    pcVar4 = local_100;
    do {
      cVar1 = *pcVar4;
      pcVar4 = pcVar4 + 1;
    } while (cVar1 != '\0');
    local_104 = plVar2;
    iVar5 = luaL_loadbuffer(plVar2,local_100,(int)pcVar4 - (int)(local_100 + 1),"=(debug command)");
    if ((iVar5 != 0) || (iVar5 = lua_pcall(plVar2,0,0,0), iVar5 != 0)) {
      pFVar3 = __iob_func();
      pFVar3 = pFVar3 + 2;
      pcVar4 = lua_tolstring(plVar2,-1,(uint *)0x0);
      fputs(pcVar4,pFVar3);
      pFVar3 = __iob_func();
      fputs("\n",pFVar3 + 2);
    }
    lua_settop(plVar2,0);
    pFVar3 = __iob_func();
    fputs("lua_debug> ",pFVar3 + 2);
    pFVar3 = __iob_func();
    pcVar4 = fgets(local_100,0xfa,pFVar3);
    plVar2 = local_104;
  } while( true );
}
