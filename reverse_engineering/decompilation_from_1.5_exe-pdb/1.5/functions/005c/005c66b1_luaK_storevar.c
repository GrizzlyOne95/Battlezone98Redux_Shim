/*
 * Entry: 005c66b1
 * Name: luaK_storevar
 * Namespace: Global
 * Signature: void luaK_storevar(FuncState * param_1, expdesc * param_2, expdesc * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaK_storevar(FuncState *param_1,expdesc *param_2,expdesc *param_3)

{
  expkind eVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  expdesc *unaff_ESI;
  expdesc *unaff_EDI;
  OpCode OVar5;
  
  eVar1 = param_2->k;
  if (eVar1 == VLOCAL) {
    freeexp(param_1,unaff_ESI);
    exp2reg((FuncState *)(param_2->u).s.info,(expdesc *)param_1,(int)unaff_ESI);
    return;
  }
  if (eVar1 == VUPVAL) {
    iVar4 = luaK_exp2anyreg(param_1,param_3);
    iVar2 = 0;
    iVar3 = (param_2->u).s.info;
    OVar5 = OP_SETUPVAL;
  }
  else {
    if (eVar1 == VGLOBAL) {
      iVar3 = luaK_exp2anyreg(param_1,param_3);
      luaK_codeABx(param_1,OP_SETGLOBAL,iVar3,(param_2->u).s.info);
      goto LAB_005c6712;
    }
    if (eVar1 != VINDEXED) goto LAB_005c6712;
    iVar2 = luaK_exp2RK(param_1,param_3);
    iVar3 = (param_2->u).s.aux;
    iVar4 = (param_2->u).s.info;
    OVar5 = OP_SETTABLE;
  }
  luaK_codeABC(param_1,OVar5,iVar4,iVar3,iVar2);
LAB_005c6712:
  freeexp(param_1,unaff_EDI);
  return;
}
