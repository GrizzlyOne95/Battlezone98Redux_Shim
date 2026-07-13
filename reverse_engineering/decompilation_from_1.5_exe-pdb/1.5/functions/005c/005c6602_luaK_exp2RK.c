/*
 * Entry: 005c6602
 * Name: luaK_exp2RK
 * Namespace: Global
 * Signature: int luaK_exp2RK(FuncState * param_1, expdesc * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaK_exp2RK(FuncState *param_1,expdesc *param_2)

{
  expkind eVar1;
  uint uVar2;
  Value *pVVar3;
  lua_TValue *unaff_EDI;
  Value local_24;
  undefined4 local_1c;
  Value local_14;
  undefined4 local_c;
  
  luaK_exp2val(param_1,param_2);
  eVar1 = param_2->k;
  if ((int)eVar1 < 1) goto LAB_005c6630;
  if ((int)eVar1 < 4) {
LAB_005c6649:
    if (0xff < param_1->nk) goto LAB_005c6630;
    if (eVar1 == VNIL) {
      local_14.gc = (GCObject *)param_1->h;
      local_1c = 0;
      local_c = 5;
      pVVar3 = &local_24;
LAB_005c6693:
      uVar2 = addk((FuncState *)&local_14,(lua_TValue *)pVVar3,unaff_EDI);
    }
    else {
      if (eVar1 != VKNUM) {
        local_14.gc = (GCObject *)(uint)(eVar1 == VTRUE);
        local_c = 1;
        pVVar3 = &local_14;
        goto LAB_005c6693;
      }
      uVar2 = luaK_numberK(param_1,(double)CONCAT44(unaff_EDI,(param_2->u).s.aux));
    }
    (param_2->u).s.info = uVar2;
    param_2->k = VK;
LAB_005c66aa:
    uVar2 = uVar2 | 0x100;
  }
  else {
    if (eVar1 == VK) {
      uVar2 = (param_2->u).s.info;
      if ((int)uVar2 < 0x100) goto LAB_005c66aa;
    }
    else if (eVar1 == VKNUM) goto LAB_005c6649;
LAB_005c6630:
    uVar2 = luaK_exp2anyreg(param_1,param_2);
  }
  return uVar2;
}
