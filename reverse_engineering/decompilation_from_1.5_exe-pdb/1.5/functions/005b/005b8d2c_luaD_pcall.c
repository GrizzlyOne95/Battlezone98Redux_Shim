/*
 * Entry: 005b8d2c
 * Name: luaD_pcall
 * Namespace: Global
 * Signature: int luaD_pcall(lua_State * param_1, _func___cdecl_void_lua_State_ptr_void_ptr * param_2, void * param_3, int param_4, int param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
luaD_pcall(lua_State *param_1,_func___cdecl_void_lua_State_ptr_void_ptr *param_2,void *param_3,
          int param_4,int param_5)

{
  uchar uVar1;
  ushort uVar2;
  CallInfo *pCVar3;
  int iVar4;
  int iVar5;
  CallInfo *pCVar6;
  lua_State *unaff_EDI;
  lua_TValue *plVar7;
  
  uVar2 = param_1->nCcalls;
  pCVar6 = param_1->ci;
  pCVar3 = param_1->base_ci;
  uVar1 = param_1->allowhook;
  iVar4 = param_1->errfunc;
  param_1->errfunc = param_5;
  iVar5 = luaD_rawrunprotected(param_1,param_2,param_3);
  if (iVar5 != 0) {
    plVar7 = (lua_TValue *)((int)&param_1->stack->value + param_4);
    luaF_close(param_1,plVar7);
    luaD_seterrorobj(param_1,iVar5,plVar7);
    param_1->nCcalls = uVar2;
    pCVar6 = (CallInfo *)((int)param_1->base_ci + ((int)pCVar6 - (int)pCVar3));
    param_1->ci = pCVar6;
    param_1->base = pCVar6->base;
    param_1->savedpc = pCVar6->savedpc;
    param_1->allowhook = uVar1;
    restore_stack_limit(unaff_EDI);
  }
  param_1->errfunc = iVar4;
  return iVar5;
}
