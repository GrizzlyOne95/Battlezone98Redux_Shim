/*
 * Entry: 005b7086
 * Name: luaL_addvalue
 * Namespace: Global
 * Signature: void luaL_addvalue(luaL_Buffer * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaL_addvalue(luaL_Buffer *param_1)

{
  lua_State *plVar1;
  luaL_Buffer *plVar2;
  char *pcVar3;
  int iVar4;
  luaL_Buffer *unaff_EDI;
  
  plVar2 = param_1;
  plVar1 = param_1->L;
  pcVar3 = lua_tolstring(plVar1,-1,(uint *)&param_1);
  if ((luaL_Buffer *)((int)plVar2 + (0x20c - (int)plVar2->p)) < param_1) {
    iVar4 = emptybuffer(unaff_EDI);
    if (iVar4 != 0) {
      lua_insert(plVar1,-2);
    }
    plVar2->lvl = plVar2->lvl + 1;
    adjuststack(unaff_EDI);
  }
  else {
    memcpy(plVar2->p,pcVar3,param_1);
    plVar2->p = param_1->buffer + (int)(plVar2->p + -0xc);
    lua_settop(plVar1,-2);
  }
  return;
}
