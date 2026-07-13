/*
 * Entry: 005b9c2c
 * Name: lua_getstack
 * Namespace: Global
 * Signature: int lua_getstack(lua_State * param_1, int param_2, lua_Debug * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl lua_getstack(lua_State *param_1,int param_2,lua_Debug *param_3)

{
  CallInfo *pCVar1;
  
  pCVar1 = param_1->ci;
  if (0 < param_2) {
    do {
      if (pCVar1 <= param_1->base_ci) break;
      param_2 = param_2 + -1;
      if (*(char *)((pCVar1->func->value).b + 6) == '\0') {
        param_2 = param_2 - pCVar1->tailcalls;
      }
      pCVar1 = pCVar1 + -1;
    } while (0 < param_2);
  }
  if (param_2 == 0) {
    if (param_1->base_ci < pCVar1) {
      param_3->i_ci = ((int)pCVar1 - (int)param_1->base_ci) / 0x18;
      return 1;
    }
  }
  else if (param_2 < 0) {
    param_3->i_ci = 0;
    return 1;
  }
  return 0;
}
