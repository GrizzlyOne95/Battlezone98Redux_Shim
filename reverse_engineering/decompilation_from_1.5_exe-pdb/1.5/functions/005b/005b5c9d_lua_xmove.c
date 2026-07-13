/*
 * Entry: 005b5c9d
 * Name: lua_xmove
 * Namespace: Global
 * Signature: void lua_xmove(lua_State * param_1, lua_State * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl lua_xmove(lua_State *param_1,lua_State *param_2,int param_3)

{
  lua_TValue *plVar1;
  lua_State *plVar2;
  undefined4 *puVar3;
  int iVar4;
  
  plVar2 = param_1;
  if ((param_1 != param_2) && (param_1->top = param_1->top + -param_3, 0 < param_3)) {
    iVar4 = 0;
    param_1 = (lua_State *)param_3;
    do {
      plVar1 = param_2->top;
      puVar3 = (undefined4 *)((int)&plVar2->top->value + iVar4);
      param_2->top = plVar1 + 1;
      (plVar1->value).gc = (GCObject *)*puVar3;
      *(undefined4 *)((int)&plVar1->value + 4) = puVar3[1];
      iVar4 = iVar4 + 0x10;
      param_1 = (lua_State *)((int)&param_1[-1].errfunc + 3);
      plVar1->tt = puVar3[2];
    } while (param_1 != (lua_State *)0x0);
  }
  return;
}
