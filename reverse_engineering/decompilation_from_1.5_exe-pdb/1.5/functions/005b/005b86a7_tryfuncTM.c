/*
 * Entry: 005b86a7
 * Name: tryfuncTM
 * Namespace: Global
 * Signature: lua_TValue * tryfuncTM(lua_State * param_1, lua_TValue * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

lua_TValue * __cdecl tryfuncTM(lua_State *param_1,lua_TValue *param_2)

{
  lua_State *plVar1;
  lua_TValue *plVar2;
  lua_TValue *plVar3;
  lua_State *plVar4;
  lua_State *unaff_ESI;
  
  plVar2 = luaT_gettmbyobj(unaff_ESI,(lua_TValue *)param_1,TM_CALL);
  plVar3 = unaff_ESI->stack;
  if (plVar2->tt != 6) {
    luaG_typeerror(unaff_ESI,(lua_TValue *)param_1,"call");
  }
  plVar4 = (lua_State *)unaff_ESI->top;
  plVar1 = plVar4;
  for (; param_1 < plVar4; plVar4 = (lua_State *)&plVar4[-1].openupval) {
    ((Value *)&plVar4->next)->gc = plVar1[-1].openupval;
    *(GCObject **)&plVar4->tt = plVar1[-1].gclist;
    plVar1->top = (lua_TValue *)plVar1[-1].errorJmp;
    plVar1 = (lua_State *)&plVar1[-1].openupval;
  }
  if ((int)unaff_ESI->stack_last - (int)unaff_ESI->top < 0x11) {
    luaD_growstack(unaff_ESI,1);
  }
  unaff_ESI->top = unaff_ESI->top + 1;
  plVar3 = (lua_TValue *)((int)unaff_ESI->stack + ((int)param_1 - (int)plVar3));
  (plVar3->value).gc = (plVar2->value).gc;
  *(undefined4 *)((int)&plVar3->value + 4) = *(undefined4 *)((int)&plVar2->value + 4);
  plVar3->tt = plVar2->tt;
  return plVar3;
}
