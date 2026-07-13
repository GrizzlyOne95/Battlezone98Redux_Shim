/*
 * Entry: 005b8c2e
 * Name: resume
 * Namespace: Global
 * Signature: void resume(lua_State * param_1, void * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl resume(lua_State *param_1,void *param_2)

{
  int iVar1;
  
  if (param_1->status == '\0') {
    iVar1 = luaD_precall(param_1,(lua_TValue *)((int)param_2 + -0x10),-1);
    if (iVar1 != 0) {
      return;
    }
  }
  else {
    param_1->status = '\0';
    if (*(char *)((param_1->ci->func->value).b + 6) == '\0') {
      param_1->base = param_1->ci->base;
    }
    else {
      iVar1 = luaD_poscall(param_1,param_2);
      if (iVar1 != 0) {
        param_1->top = param_1->ci->top;
      }
    }
  }
  luaV_execute(param_1,((int)param_1->ci - (int)param_1->base_ci) / 0x18);
  return;
}
