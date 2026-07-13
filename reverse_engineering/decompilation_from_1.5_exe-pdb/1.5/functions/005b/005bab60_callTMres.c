/*
 * Entry: 005bab60
 * Name: callTMres
 * Namespace: Global
 * Signature: void callTMres(lua_State * param_1, lua_TValue * param_2, lua_TValue * param_3, lua_TValue * param_4, lua_TValue * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
callTMres(lua_State *param_1,lua_TValue *param_2,lua_TValue *param_3,lua_TValue *param_4,
         lua_TValue *param_5)

{
  lua_TValue *plVar1;
  lua_TValue *plVar2;
  int in_EAX;
  undefined4 *in_ECX;
  undefined4 *in_EDX;
  undefined4 *puVar3;
  
  plVar1 = param_1->stack;
  plVar2 = param_1->top;
  (plVar2->value).gc = (param_2->value).gc;
  *(undefined4 *)((int)&plVar2->value + 4) = *(undefined4 *)((int)&param_2->value + 4);
  plVar2->tt = param_2->tt;
  plVar2 = param_1->top;
  plVar2[1].value.gc = (GCObject *)*in_EDX;
  *(undefined4 *)((int)&plVar2[1].value + 4) = in_EDX[1];
  plVar2[1].tt = in_EDX[2];
  plVar2 = param_1->top;
  plVar2[2].value.gc = (GCObject *)*in_ECX;
  *(undefined4 *)((int)&plVar2[2].value + 4) = in_ECX[1];
  plVar2[2].tt = in_ECX[2];
  if ((int)param_1->stack_last - (int)param_1->top < 0x31) {
    luaD_growstack(param_1,3);
  }
  param_1->top = param_1->top + 3;
  luaD_call(param_1,param_1->top + -3,1);
  param_1->top = param_1->top + -1;
  plVar2 = param_1->top;
  puVar3 = (undefined4 *)((int)param_1->stack + (in_EAX - (int)plVar1));
  *puVar3 = (plVar2->value).gc;
  puVar3[1] = *(undefined4 *)((int)&plVar2->value + 4);
  puVar3[2] = plVar2->tt;
  return;
}
