/*
 * Entry: 005b8a1b
 * Name: luaD_precall
 * Namespace: Global
 * Signature: int luaD_precall(lua_State * param_1, lua_TValue * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaD_precall(lua_State *param_1,lua_TValue *param_2,int param_3)

{
  lua_State *plVar1;
  uint uVar2;
  CallInfo *pCVar3;
  int iVar4;
  lua_TValue *plVar5;
  lua_State *unaff_EDI;
  int iVar6;
  
  if (param_2->tt != 6) {
    param_2 = tryfuncTM((lua_State *)param_2,(lua_TValue *)unaff_EDI);
  }
  iVar6 = (int)param_2 - (int)param_1->stack;
  iVar4 = (param_2->value).b;
  param_1->ci->savedpc = param_1->savedpc;
  if (*(char *)(iVar4 + 6) == '\0') {
    plVar1 = *(lua_State **)(iVar4 + 0x10);
    uVar2 = (uint)*(byte *)((int)&(plVar1->l_gt).value + 3);
    if ((int)param_1->stack_last - (int)param_1->top <= (int)(uVar2 * 0x10)) {
      luaD_growstack(param_1,uVar2);
    }
    plVar5 = (lua_TValue *)((int)param_1->stack + iVar6);
    if (*(char *)((int)&(plVar1->l_gt).value + 2) == '\0') {
      param_2 = plVar5 + 1;
      if (param_2 + *(byte *)((int)&(plVar1->l_gt).value + 1) < param_1->top) {
        param_1->top = param_2 + *(byte *)((int)&(plVar1->l_gt).value + 1);
      }
    }
    else {
      param_2 = adjust_varargs(plVar1,(Proto *)(((int)param_1->top - (int)plVar5 >> 4) + -1),
                               (int)unaff_EDI);
      plVar5 = (lua_TValue *)((int)param_1->stack + iVar6);
    }
    if (param_1->ci == param_1->end_ci) {
      pCVar3 = growCI(unaff_EDI);
    }
    else {
      pCVar3 = param_1->ci + 1;
      param_1->ci = pCVar3;
    }
    pCVar3->base = param_2;
    pCVar3->func = plVar5;
    param_1->base = param_2;
    pCVar3->top = param_2 + *(byte *)((int)&(plVar1->l_gt).value + 3);
    param_1->savedpc = (uint *)plVar1->base;
    pCVar3->tailcalls = 0;
    pCVar3->nresults = param_3;
    for (plVar5 = param_1->top; plVar5 < pCVar3->top; plVar5 = plVar5 + 1) {
      plVar5->tt = 0;
    }
    param_1->top = pCVar3->top;
    if ((param_1->hookmask & 1) != 0) {
      param_1->savedpc = param_1->savedpc + 1;
      luaD_callhook(param_1,0,-1);
      param_1->savedpc = param_1->savedpc + -1;
    }
    iVar4 = 0;
  }
  else {
    if ((int)param_1->stack_last - (int)param_1->top < 0x141) {
      luaD_growstack(param_1,0x14);
    }
    if (param_1->ci == param_1->end_ci) {
      pCVar3 = growCI(unaff_EDI);
    }
    else {
      pCVar3 = param_1->ci + 1;
      param_1->ci = pCVar3;
    }
    plVar5 = (lua_TValue *)((int)param_1->stack + iVar6);
    pCVar3->func = plVar5;
    plVar5 = plVar5 + 1;
    pCVar3->base = plVar5;
    param_1->base = plVar5;
    pCVar3->top = param_1->top + 0x14;
    pCVar3->nresults = param_3;
    if ((param_1->hookmask & 1) != 0) {
      luaD_callhook(param_1,0,-1);
    }
    iVar4 = (**(code **)((param_1->ci->func->value).b + 0x10))(param_1);
    if (iVar4 < 0) {
      iVar4 = 2;
    }
    else {
      luaD_poscall(param_1,param_1->top + -iVar4);
      iVar4 = 1;
    }
  }
  return iVar4;
}
