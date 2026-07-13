/*
 * Entry: 005ba63b
 * Name: luaG_errormsg
 * Namespace: Global
 * Signature: void luaG_errormsg(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaG_errormsg(lua_State *param_1)

{
  lua_TValue *plVar1;
  undefined4 *puVar2;
  
  if (param_1->errfunc != 0) {
    puVar2 = (undefined4 *)((int)&param_1->stack->value + param_1->errfunc);
    if (puVar2[2] != 6) {
                    /* WARNING: Subroutine does not return */
      luaD_throw(param_1,5);
    }
    plVar1 = param_1->top;
    (plVar1->value).gc = plVar1[-1].value.gc;
    *(undefined4 *)((int)&plVar1->value + 4) = *(undefined4 *)((int)&plVar1[-1].value + 4);
    plVar1->tt = plVar1[-1].tt;
    plVar1 = param_1->top;
    plVar1[-1].value.gc = (GCObject *)*puVar2;
    *(undefined4 *)((int)&plVar1[-1].value + 4) = puVar2[1];
    plVar1[-1].tt = puVar2[2];
    if ((int)param_1->stack_last - (int)param_1->top < 0x11) {
      luaD_growstack(param_1,1);
    }
    param_1->top = param_1->top + 1;
    luaD_call(param_1,param_1->top + -2,1);
  }
                    /* WARNING: Subroutine does not return */
  luaD_throw(param_1,2);
}
