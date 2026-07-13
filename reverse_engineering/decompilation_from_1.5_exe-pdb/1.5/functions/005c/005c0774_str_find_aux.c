/*
 * Entry: 005c0774
 * Name: str_find_aux
 * Namespace: Global
 * Signature: int str_find_aux(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl str_find_aux(lua_State *param_1,int param_2)

{
  char cVar1;
  char *pcVar2;
  int iVar3;
  char *pcVar4;
  uint uVar5;
  MatchState *pMVar6;
  char *unaff_EDI;
  MatchState local_124;
  uint local_14;
  char *local_10;
  uint local_c;
  char *local_8;
  
  pcVar2 = luaL_checklstring(param_1,1,&local_c);
  local_8 = luaL_checklstring(param_1,2,(uint *)&local_10);
  uVar5 = local_c;
  iVar3 = luaL_optinteger(param_1,3,1);
  if ((iVar3 < 0) && (iVar3 = iVar3 + 1 + uVar5, iVar3 < 0)) {
    iVar3 = 0;
  }
  uVar5 = iVar3 - 1;
  if ((int)uVar5 < 0) {
    uVar5 = 0;
  }
  else if (local_c < uVar5) {
    uVar5 = local_c;
  }
  if ((param_2 == 0) ||
     ((iVar3 = lua_toboolean(param_1,4), iVar3 == 0 &&
      (pcVar4 = strpbrk(local_8,"^$*+?.([%-"), pcVar4 != (char *)0x0)))) {
    cVar1 = *local_8;
    if (cVar1 == '^') {
      local_8 = local_8 + 1;
    }
    local_14 = (uint)(cVar1 == '^');
    local_124.L = param_1;
    local_124.src_end = pcVar2 + local_c;
    pMVar6 = (MatchState *)(pcVar2 + uVar5);
    local_124.src_init = pcVar2;
    do {
      local_124.level = 0;
      pcVar4 = match(&local_124,(char *)pMVar6,local_8);
      if (pcVar4 != (char *)0x0) {
        if (param_2 == 0) {
          iVar3 = push_captures(pMVar6,pcVar4,unaff_EDI);
          return iVar3;
        }
        lua_pushinteger(param_1,(int)pMVar6 + (1 - (int)pcVar2));
        lua_pushinteger(param_1,(int)pcVar4 - (int)pcVar2);
        iVar3 = push_captures((MatchState *)0x0,(char *)0x0,(char *)param_1);
        iVar3 = iVar3 + 1;
        goto LAB_005c08ab;
      }
    } while ((pMVar6 < local_124.src_end) &&
            (pMVar6 = (MatchState *)((int)&pMVar6->src_init + 1), local_14 == 0));
  }
  else {
    pcVar4 = lmemfind(pcVar2 + uVar5,local_c - uVar5,local_10,(uint)unaff_EDI);
    if (pcVar4 != (char *)0x0) {
      lua_pushinteger(param_1,((int)pcVar4 - (int)pcVar2) + 1);
      lua_pushinteger(param_1,(int)(local_10 + ((int)pcVar4 - (int)pcVar2)));
      return 2;
    }
  }
  lua_pushnil(param_1);
  iVar3 = 0;
LAB_005c08ab:
  return iVar3 + 1;
}
