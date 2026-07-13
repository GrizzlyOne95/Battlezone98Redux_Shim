/*
 * Entry: 005bc2bf
 * Name: luaH_next
 * Namespace: Global
 * Signature: int luaH_next(lua_State * param_1, Table * param_2, lua_TValue * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl luaH_next(lua_State *param_1,Table *param_2,lua_TValue *param_3)

{
  TKey *pTVar1;
  int iVar2;
  Node *pNVar3;
  int *piVar4;
  int iVar5;
  lua_TValue *unaff_EDI;
  
  iVar2 = findindex(param_1,param_2,unaff_EDI);
  iVar5 = param_2->sizearray;
  iVar2 = iVar2 + 1;
  if (iVar2 < iVar5) {
    piVar4 = &param_2->array[iVar2].tt;
    do {
      if (*piVar4 != 0) {
        param_3->tt = 3;
        (param_3->value).n = (double)(iVar2 + 1);
        pNVar3 = (Node *)(param_2->array + iVar2);
        goto LAB_005bc33d;
      }
      iVar2 = iVar2 + 1;
      piVar4 = piVar4 + 4;
    } while (iVar2 < iVar5);
  }
  iVar2 = iVar2 - iVar5;
  iVar5 = 1 << (param_2->lsizenode & 0x1f);
  if (iVar2 < iVar5) {
    piVar4 = &param_2->node[iVar2].i_val.tt;
    do {
      if (*piVar4 != 0) {
        pTVar1 = &param_2->node[iVar2].i_key;
        (param_3->value).gc = *(GCObject **)pTVar1;
        *(undefined4 *)((int)&param_3->value + 4) = *(undefined4 *)((int)pTVar1 + 4);
        param_3->tt = (pTVar1->nk).tt;
        pNVar3 = param_2->node + iVar2;
LAB_005bc33d:
        param_3[1].value.gc = (pNVar3->i_val).value.gc;
        *(undefined4 *)((int)&param_3[1].value + 4) =
             *(undefined4 *)((int)&(pNVar3->i_val).value + 4);
        param_3[1].tt = (int)(&(pNVar3->i_val).value)[1].gc;
        return 1;
      }
      iVar2 = iVar2 + 1;
      piVar4 = piVar4 + 8;
    } while (iVar2 < iVar5);
  }
  return 0;
}
