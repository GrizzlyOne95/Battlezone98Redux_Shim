/*
 * Entry: 005c5d47
 * Name: addk
 * Namespace: Global
 * Signature: int addk(FuncState * param_1, lua_TValue * param_2, lua_TValue * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl addk(FuncState *param_1,lua_TValue *param_2,lua_TValue *param_3)

{
  int *piVar1;
  lua_State *plVar2;
  GCObject *pGVar3;
  undefined4 *in_EAX;
  lua_TValue *plVar4;
  int extraout_EAX;
  Table *pTVar5;
  int iVar6;
  GCObject **ppGVar7;
  int iVar8;
  int *piVar9;
  
  plVar2 = (lua_State *)in_EAX[4];
  plVar4 = luaH_set(plVar2,(Table *)in_EAX[1],(lua_TValue *)param_1);
  pGVar3 = (GCObject *)*in_EAX;
  piVar1 = &(pGVar3->p).sizek;
  iVar8 = *piVar1;
  if (plVar4->tt == 3) {
    _ftol2_sse();
    iVar8 = extraout_EAX;
  }
  else {
    piVar9 = in_EAX + 10;
    iVar6 = *piVar9;
    plVar4->tt = 3;
    (plVar4->value).n = (double)iVar6;
    if (*piVar1 < *piVar9 + 1) {
      pTVar5 = luaM_growaux_(plVar2,(pGVar3->h).metatable,piVar1,0x10,0x3ffff,
                             "constant table overflow");
      (pGVar3->h).metatable = pTVar5;
    }
    if (iVar8 < *piVar1) {
      iVar6 = iVar8 << 4;
      do {
        *(undefined4 *)((int)&((pGVar3->h).metatable)->metatable + iVar6) = 0;
        iVar8 = iVar8 + 1;
        iVar6 = iVar6 + 0x10;
      } while (iVar8 < *piVar1);
    }
    ppGVar7 = &((pGVar3->h).metatable)->next + *piVar9 * 4;
    *ppGVar7 = (param_2->value).gc;
    ppGVar7[1] = (GCObject *)*(undefined4 *)((int)&param_2->value + 4);
    ppGVar7[2] = (GCObject *)param_2->tt;
    if (((3 < param_2->tt) && (((((param_2->value).gc)->gch).marked & 3) != 0)) &&
       (((pGVar3->gch).marked & 4) != 0)) {
      luaC_barrierf(plVar2,pGVar3,(param_2->value).gc);
    }
    iVar8 = *piVar9;
    *piVar9 = iVar8 + 1;
  }
  return iVar8;
}
