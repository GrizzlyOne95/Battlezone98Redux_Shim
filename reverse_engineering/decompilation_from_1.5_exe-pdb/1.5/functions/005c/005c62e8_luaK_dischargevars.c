/*
 * Entry: 005c62e8
 * Name: luaK_dischargevars
 * Namespace: Global
 * Signature: void luaK_dischargevars(FuncState * param_1, expdesc * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaK_dischargevars(FuncState *param_1,expdesc *param_2)

{
  expkind eVar1;
  FuncState *extraout_EAX;
  int iVar2;
  int unaff_ESI;
  FuncState *pFVar3;
  
  eVar1 = param_2->k;
  if (eVar1 == VLOCAL) {
    param_2->k = VNONRELOC;
  }
  else {
    if (eVar1 == VUPVAL) {
      iVar2 = luaK_codeABC(param_1,OP_GETUPVAL,0,(param_2->u).s.info,0);
    }
    else if (eVar1 == VGLOBAL) {
      iVar2 = luaK_codeABx(param_1,OP_GETGLOBAL,0,(param_2->u).s.info);
    }
    else {
      if (eVar1 != VINDEXED) {
        if (1 < eVar1 - VCALL) {
          return;
        }
        luaK_setoneret(param_1,param_2);
        return;
      }
      pFVar3 = (FuncState *)(param_2->u).s.aux;
      freereg(pFVar3,unaff_ESI);
      freereg((FuncState *)(param_2->u).s.info,(int)pFVar3);
      iVar2 = luaK_codeABC(extraout_EAX,OP_GETTABLE,0,(param_2->u).s.info,(param_2->u).s.aux);
    }
    (param_2->u).s.info = iVar2;
    param_2->k = VRELOCABLE;
  }
  return;
}
