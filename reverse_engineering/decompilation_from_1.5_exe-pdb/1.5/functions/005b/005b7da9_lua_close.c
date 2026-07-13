/*
 * Entry: 005b7da9
 * Name: lua_close
 * Namespace: Global
 * Signature: void lua_close(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl lua_close(lua_State *param_1)

{
  lua_State *plVar1;
  lua_TValue *plVar2;
  int iVar3;
  
  plVar1 = param_1->l_G->mainthread;
  luaF_close(plVar1,plVar1->stack);
  luaC_separateudata(plVar1,1);
  plVar1->errfunc = 0;
  do {
    plVar1->ci = plVar1->base_ci;
    plVar2 = plVar1->base_ci->base;
    plVar1->top = plVar2;
    plVar1->base = plVar2;
    plVar1->baseCcalls = 0;
    plVar1->nCcalls = 0;
    iVar3 = luaD_rawrunprotected(plVar1,callallgcTM,(void *)0x0);
  } while (iVar3 != 0);
  close_state(param_1);
  return;
}
