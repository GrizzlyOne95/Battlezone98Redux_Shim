/*
 * Entry: 005b658f
 * Name: lua_getfenv
 * Namespace: Global
 * Signature: void lua_getfenv(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl lua_getfenv(lua_State *param_1,int param_2)

{
  int iVar1;
  lua_TValue *plVar2;
  GCObject *pGVar3;
  lua_TValue *plVar4;
  lua_State *unaff_ESI;
  int unaff_retaddr;
  
  plVar4 = index2adr(unaff_ESI,unaff_retaddr);
  iVar1 = plVar4->tt;
  if ((iVar1 == 6) || (iVar1 == 7)) {
    plVar2 = param_1->top;
    pGVar3 = *(GCObject **)((plVar4->value).b + 0xc);
    plVar2->tt = 5;
    (plVar2->value).gc = pGVar3;
  }
  else if (iVar1 == 8) {
    iVar1 = (plVar4->value).b;
    plVar4 = param_1->top;
    (plVar4->value).gc = *(GCObject **)(iVar1 + 0x48);
    *(undefined4 *)((int)&plVar4->value + 4) = *(undefined4 *)(iVar1 + 0x4c);
    plVar4->tt = *(int *)(iVar1 + 0x50);
  }
  else {
    param_1->top->tt = 0;
  }
  param_1->top = param_1->top + 1;
  return;
}
