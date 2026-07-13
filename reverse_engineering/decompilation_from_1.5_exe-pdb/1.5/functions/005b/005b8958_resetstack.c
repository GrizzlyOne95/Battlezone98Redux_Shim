/*
 * Entry: 005b8958
 * Name: resetstack
 * Namespace: Global
 * Signature: void resetstack(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl resetstack(lua_State *param_1,int param_2)

{
  lua_TValue *plVar1;
  lua_State *unaff_ESI;
  lua_State *unaff_retaddr;
  
  unaff_ESI->ci = unaff_ESI->base_ci;
  plVar1 = unaff_ESI->base_ci->base;
  unaff_ESI->base = plVar1;
  luaF_close(unaff_ESI,plVar1);
  luaD_seterrorobj(unaff_ESI,(int)param_1,unaff_ESI->base);
  unaff_ESI->nCcalls = unaff_ESI->baseCcalls;
  unaff_ESI->allowhook = '\x01';
  restore_stack_limit(unaff_retaddr);
  unaff_ESI->errfunc = 0;
  unaff_ESI->errorJmp = (lua_longjmp *)0x0;
  return;
}
