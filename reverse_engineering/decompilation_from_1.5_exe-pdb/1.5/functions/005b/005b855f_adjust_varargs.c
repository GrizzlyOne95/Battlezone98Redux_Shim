/*
 * Entry: 005b855f
 * Name: adjust_varargs
 * Namespace: Global
 * Signature: lua_TValue * adjust_varargs(lua_State * param_1, Proto * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

lua_TValue * __cdecl adjust_varargs(lua_State *param_1,Proto *param_2,int param_3)

{
  lua_TValue *plVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  lua_TValue *plVar5;
  TString *pTVar6;
  int iVar7;
  uint uVar8;
  int *piVar9;
  lua_State *unaff_ESI;
  undefined4 *puVar10;
  GCObject *local_8;
  
  uVar8 = (uint)*(byte *)((int)&(param_1->l_gt).value + 1);
  local_8 = (GCObject *)0x0;
  if ((int)param_2 < (int)uVar8) {
    iVar2 = uVar8 - (int)param_2;
    param_2 = (Proto *)((int)param_2 + iVar2);
    do {
      unaff_ESI->top->tt = 0;
      unaff_ESI->top = unaff_ESI->top + 1;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  if (((ulonglong)(param_1->l_gt).value & 0x40000) != 0) {
    iVar2 = (int)param_2 - uVar8;
    if (unaff_ESI->l_G->GCthreshold <= unaff_ESI->l_G->totalbytes) {
      luaC_step(unaff_ESI);
    }
    uVar3 = (uint)*(byte *)((int)&(param_1->l_gt).value + 3);
    if ((int)unaff_ESI->stack_last - (int)unaff_ESI->top <= (int)(uVar3 * 0x10)) {
      luaD_growstack(unaff_ESI,uVar3);
    }
    local_8 = (GCObject *)luaH_new(unaff_ESI,iVar2,1);
    iVar4 = 0;
    if (0 < iVar2) {
      iVar7 = iVar2 * -0x10;
      do {
        puVar10 = (undefined4 *)((int)&unaff_ESI->top->value + iVar7);
        iVar4 = iVar4 + 1;
        plVar5 = luaH_setnum(unaff_ESI,&local_8->h,iVar4);
        iVar7 = iVar7 + 0x10;
        (plVar5->value).gc = (GCObject *)*puVar10;
        *(undefined4 *)((int)&plVar5->value + 4) = puVar10[1];
        plVar5->tt = puVar10[2];
      } while (iVar4 < iVar2);
    }
    pTVar6 = luaS_newlstr(unaff_ESI,"n",1);
    plVar5 = luaH_setstr(unaff_ESI,&local_8->h,pTVar6);
    (plVar5->value).n = (double)iVar2;
    plVar5->tt = 3;
  }
  plVar5 = unaff_ESI->top;
  if (uVar8 != 0) {
    piVar9 = &plVar5[-(int)param_2].tt;
    do {
      plVar1 = unaff_ESI->top;
      unaff_ESI->top = plVar1 + 1;
      (plVar1->value).gc = (((lua_TValue *)(piVar9 + -2))->value).gc;
      *(int *)((int)&plVar1->value + 4) = piVar9[-1];
      plVar1->tt = *piVar9;
      *piVar9 = 0;
      piVar9 = piVar9 + 4;
      uVar8 = uVar8 - 1;
    } while (uVar8 != 0);
  }
  if (local_8 != (GCObject *)0x0) {
    plVar1 = unaff_ESI->top;
    unaff_ESI->top = plVar1 + 1;
    (plVar1->value).gc = local_8;
    plVar1->tt = 5;
  }
  return plVar5;
}
