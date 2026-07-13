/*
 * Entry: 005b877c
 * Name: luaD_poscall
 * Namespace: Global
 * Signature: int luaD_poscall(lua_State * param_1, lua_TValue * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaD_poscall(lua_State *param_1,lua_TValue *param_2)

{
  CallInfo *pCVar1;
  lua_State *plVar2;
  lua_State *plVar3;
  lua_State *plVar4;
  lua_TValue *unaff_ESI;
  lua_State *unaff_EDI;
  lua_TValue *plVar5;
  
  plVar3 = param_1;
  if ((param_1->hookmask & 2) != 0) {
    param_2 = callrethooks(unaff_EDI,unaff_ESI);
  }
  pCVar1 = param_1->ci;
  param_1->ci = pCVar1 + -1;
  plVar2 = (lua_State *)pCVar1->nresults;
  plVar5 = pCVar1->func;
  param_1->base = pCVar1[-1].base;
  param_1->savedpc = pCVar1[-1].savedpc;
  plVar4 = plVar2;
  for (; (plVar4 != (lua_State *)0x0 && (param_2 < param_1->top)); param_2 = param_2 + 1) {
    (plVar5->value).gc = (param_2->value).gc;
    *(undefined4 *)((int)&plVar5->value + 4) = *(undefined4 *)((int)&param_2->value + 4);
    plVar4 = (lua_State *)((int)&plVar4[-1].errfunc + 3);
    plVar5->tt = param_2->tt;
    plVar5 = plVar5 + 1;
  }
  while (param_1 = plVar4, 0 < (int)param_1) {
    plVar5->tt = 0;
    plVar5 = plVar5 + 1;
    plVar4 = (lua_State *)((int)&param_1[-1].errfunc + 3);
  }
  plVar3->top = plVar5;
  return (int)(undefined1 *)((int)&plVar2->next + 1);
}
