/*
 * Entry: 005c3b43
 * Name: open_func
 * Namespace: Global
 * Signature: void open_func(LexState * param_1, FuncState * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl open_func(LexState *param_1,FuncState *param_2)

{
  lua_State *plVar1;
  lua_TValue *plVar2;
  undefined4 *in_EAX;
  GCObject *pGVar3;
  GCObject *pGVar4;
  int unaff_EBX;
  
  plVar1 = *(lua_State **)(unaff_EBX + 0x34);
  pGVar3 = (GCObject *)luaF_newproto(plVar1);
  *in_EAX = pGVar3;
  in_EAX[2] = *(undefined4 *)(unaff_EBX + 0x30);
  in_EAX[3] = unaff_EBX;
  in_EAX[4] = plVar1;
  *(undefined4 **)(unaff_EBX + 0x30) = in_EAX;
  in_EAX[7] = 0xffffffff;
  in_EAX[8] = 0xffffffff;
  in_EAX[6] = 0;
  in_EAX[9] = 0;
  in_EAX[10] = 0;
  in_EAX[0xb] = 0;
  *(undefined2 *)(in_EAX + 0xc) = 0;
  *(undefined1 *)((int)in_EAX + 0x32) = 0;
  in_EAX[5] = 0;
  (pGVar3->p).source = *(TString **)(unaff_EBX + 0x40);
  (pGVar3->p).maxstacksize = '\x02';
  pGVar4 = (GCObject *)luaH_new(plVar1,0,0);
  in_EAX[1] = pGVar4;
  plVar2 = plVar1->top;
  (plVar2->value).gc = pGVar4;
  plVar2->tt = 5;
  if ((int)plVar1->stack_last - (int)plVar1->top < 0x11) {
    luaD_growstack(plVar1,1);
  }
  plVar1->top = plVar1->top + 1;
  plVar2 = plVar1->top;
  (plVar2->value).gc = pGVar3;
  plVar2->tt = 9;
  if ((int)plVar1->stack_last - (int)plVar1->top < 0x11) {
    luaD_growstack(plVar1,1);
  }
  plVar1->top = plVar1->top + 1;
  return;
}
