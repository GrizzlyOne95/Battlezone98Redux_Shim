/*
 * Entry: 005b8425
 * Name: luaD_reallocCI
 * Namespace: Global
 * Signature: void luaD_reallocCI(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaD_reallocCI(lua_State *param_1,int param_2)

{
  CallInfo *pCVar1;
  CallInfo *pCVar2;
  
  pCVar1 = param_1->base_ci;
  if (param_2 + 1U < 0xaaaaaab) {
    pCVar2 = luaM_realloc_(param_1,pCVar1,param_1->size_ci * 0x18,param_2 * 0x18);
  }
  else {
    pCVar2 = luaM_toobig(param_1);
  }
  param_1->size_ci = param_2;
  param_1->base_ci = pCVar2;
  param_1->ci = pCVar2 + ((int)param_1->ci - (int)pCVar1) / 0x18;
  param_1->end_ci = pCVar2 + param_2 + -1;
  return;
}
