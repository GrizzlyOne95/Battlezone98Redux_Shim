/*
 * Entry: 005b9e2e
 * Name: collectvalidlines
 * Namespace: Global
 * Signature: void collectvalidlines(lua_State * param_1, Closure * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl collectvalidlines(lua_State *param_1,Closure *param_2)

{
  int iVar1;
  GCObject *pGVar2;
  lua_TValue *plVar3;
  int unaff_EBX;
  int iVar4;
  lua_State *unaff_EDI;
  
  iVar4 = 0;
  if ((unaff_EBX == 0) || (*(char *)(unaff_EBX + 6) != '\0')) {
    unaff_EDI->top->tt = 0;
  }
  else {
    pGVar2 = (GCObject *)luaH_new(unaff_EDI,0,0);
    iVar1 = *(int *)(*(int *)(unaff_EBX + 0x10) + 0x14);
    if (0 < *(int *)(*(int *)(unaff_EBX + 0x10) + 0x30)) {
      do {
        plVar3 = luaH_setnum(unaff_EDI,&pGVar2->h,*(int *)(iVar1 + iVar4 * 4));
        (plVar3->value).b = 1;
        plVar3->tt = 1;
        iVar4 = iVar4 + 1;
      } while (iVar4 < *(int *)(*(int *)(unaff_EBX + 0x10) + 0x30));
    }
    plVar3 = unaff_EDI->top;
    (plVar3->value).gc = pGVar2;
    plVar3->tt = 5;
  }
  if ((int)unaff_EDI->stack_last - (int)unaff_EDI->top < 0x11) {
    luaD_growstack(unaff_EDI,1);
  }
  unaff_EDI->top = unaff_EDI->top + 1;
  return;
}
