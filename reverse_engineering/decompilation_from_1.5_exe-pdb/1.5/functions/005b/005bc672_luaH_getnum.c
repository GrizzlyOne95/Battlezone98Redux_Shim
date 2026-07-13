/*
 * Entry: 005bc672
 * Name: luaH_getnum
 * Namespace: Global
 * Signature: lua_TValue * luaH_getnum(Table * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

lua_TValue * __cdecl luaH_getnum(Table *param_1,int param_2)

{
  Node *pNVar1;
  lua_TValue *plVar2;
  undefined4 unaff_ESI;
  Table *pTVar3;
  undefined4 uStack_8;
  
  if (param_2 - 1U < (uint)param_1->sizearray) {
    plVar2 = param_1->array + param_2 + -1;
  }
  else {
    pTVar3 = SUB84((double)param_2,0);
    uStack_8 = (undefined4)((ulonglong)(double)param_2 >> 0x20);
    pNVar1 = hashnum(pTVar3,(double)CONCAT44(pTVar3,unaff_ESI));
    do {
      if (((pNVar1->i_key).nk.tt == 3) &&
         ((double)CONCAT44(uStack_8,pTVar3) == *(double *)&pNVar1->i_key)) {
        return &pNVar1->i_val;
      }
      pNVar1 = (pNVar1->i_key).nk.next;
    } while (pNVar1 != (Node *)0x0);
    plVar2 = &luaO_nilobject_;
  }
  return plVar2;
}
