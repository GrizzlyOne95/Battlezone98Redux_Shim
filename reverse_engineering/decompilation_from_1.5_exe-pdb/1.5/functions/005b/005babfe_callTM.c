/*
 * Entry: 005babfe
 * Name: callTM
 * Namespace: Global
 * Signature: void callTM(lua_State * param_1, lua_TValue * param_2, lua_TValue * param_3, lua_TValue * param_4, lua_TValue * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
callTM(lua_State *param_1,lua_TValue *param_2,lua_TValue *param_3,lua_TValue *param_4,
      lua_TValue *param_5)

{
  lua_TValue *plVar1;
  undefined4 *in_EAX;
  undefined4 *in_ECX;
  undefined4 *in_EDX;
  lua_State *unaff_ESI;
  
  plVar1 = unaff_ESI->top;
  (plVar1->value).gc = param_1->next;
  *(undefined4 *)((int)&plVar1->value + 4) = *(undefined4 *)&param_1->tt;
  plVar1->tt = (int)param_1->top;
  plVar1 = unaff_ESI->top;
  plVar1[1].value.gc = (GCObject *)*in_EAX;
  *(undefined4 *)((int)&plVar1[1].value + 4) = in_EAX[1];
  plVar1[1].tt = in_EAX[2];
  plVar1 = unaff_ESI->top;
  plVar1[2].value.gc = (GCObject *)*in_EDX;
  *(undefined4 *)((int)&plVar1[2].value + 4) = in_EDX[1];
  plVar1[2].tt = in_EDX[2];
  plVar1 = unaff_ESI->top;
  plVar1[3].value.gc = (GCObject *)*in_ECX;
  *(undefined4 *)((int)&plVar1[3].value + 4) = in_ECX[1];
  plVar1[3].tt = in_ECX[2];
  if ((int)unaff_ESI->stack_last - (int)unaff_ESI->top < 0x41) {
    luaD_growstack(unaff_ESI,4);
  }
  unaff_ESI->top = unaff_ESI->top + 4;
  luaD_call(unaff_ESI,unaff_ESI->top + -4,0);
  return;
}
