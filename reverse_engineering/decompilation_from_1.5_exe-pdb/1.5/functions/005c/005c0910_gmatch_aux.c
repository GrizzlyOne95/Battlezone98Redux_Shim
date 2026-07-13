/*
 * Entry: 005c0910
 * Name: gmatch_aux
 * Namespace: Global
 * Signature: int gmatch_aux(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl gmatch_aux(lua_State *param_1)

{
  char *pcVar1;
  int iVar2;
  MatchState *pMVar3;
  lua_State *plVar4;
  MatchState local_11c;
  char *local_c;
  MatchState *local_8;
  
  plVar4 = param_1;
  pcVar1 = lua_tolstring(param_1,-0x2713,(uint *)&param_1);
  local_c = lua_tolstring(plVar4,-0x2714,(uint *)0x0);
  local_11c.src_end = pcVar1 + (int)&param_1->next;
  local_11c.L = plVar4;
  local_11c.src_init = pcVar1;
  iVar2 = lua_tointeger(plVar4,-0x2715);
  pMVar3 = (MatchState *)(pcVar1 + iVar2);
  while( true ) {
    if (local_11c.src_end < pMVar3) {
      return 0;
    }
    local_11c.level = 0;
    local_8 = (MatchState *)match(&local_11c,(char *)pMVar3,local_c);
    if (local_8 != (MatchState *)0x0) break;
    pMVar3 = (MatchState *)((int)&pMVar3->src_init + 1);
    local_8 = (MatchState *)0x0;
  }
  iVar2 = (int)local_8 - (int)pcVar1;
  if (local_8 == pMVar3) {
    iVar2 = iVar2 + 1;
  }
  lua_pushinteger(plVar4,iVar2);
  lua_replace(plVar4,-0x2715);
  iVar2 = push_captures(pMVar3,(char *)local_8,(char *)plVar4);
  return iVar2;
}
