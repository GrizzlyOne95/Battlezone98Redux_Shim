/*
 * Entry: 005bcb69
 * Name: newkey
 * Namespace: Global
 * Signature: lua_TValue * newkey(lua_State * param_1, Table * param_2, lua_TValue * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

lua_TValue * __cdecl newkey(lua_State *param_1,Table *param_2,lua_TValue *param_3)

{
  Node *pNVar1;
  lua_TValue *plVar2;
  Node *pNVar3;
  int iVar4;
  lua_TValue *unaff_ESI;
  Table *unaff_EDI;
  Node *pNVar5;
  
  pNVar1 = mainposition(unaff_EDI,unaff_ESI);
  if (((pNVar1->i_val).tt != 0) || (pNVar1 == &dummynode_)) {
    pNVar5 = param_2->lastfree;
    do {
      if (pNVar5 <= param_2->node) {
        param_2->lastfree = param_2->lastfree + -1;
        pNVar5 = (Node *)0x0;
        break;
      }
      param_2->lastfree = param_2->lastfree + -1;
      pNVar5 = param_2->lastfree;
    } while ((pNVar5->i_key).nk.tt != 0);
    if (pNVar5 == (Node *)0x0) {
      rehash(param_1,(Table *)param_3,(lua_TValue *)unaff_EDI);
      plVar2 = luaH_set(param_1,param_2,param_3);
      return plVar2;
    }
    pNVar3 = mainposition(unaff_EDI,unaff_ESI);
    if (pNVar3 == pNVar1) {
      (pNVar5->i_key).nk.next = (pNVar1->i_key).nk.next;
      (pNVar1->i_key).nk.next = pNVar5;
      pNVar1 = pNVar5;
    }
    else {
      for (; (pNVar3->i_key).nk.next != pNVar1; pNVar3 = (pNVar3->i_key).nk.next) {
      }
      (pNVar3->i_key).nk.next = pNVar5;
      pNVar3 = pNVar1;
      for (iVar4 = 8; iVar4 != 0; iVar4 = iVar4 + -1) {
        (pNVar5->i_val).value.gc = (pNVar3->i_val).value.gc;
        pNVar3 = (Node *)((int)&(pNVar3->i_val).value + 4);
        pNVar5 = (Node *)((int)&(pNVar5->i_val).value + 4);
      }
      (pNVar1->i_key).nk.next = (Node *)0x0;
      (pNVar1->i_val).tt = 0;
    }
  }
  *(GCObject **)&pNVar1->i_key = (param_3->value).gc;
  *(undefined4 *)((int)&pNVar1->i_key + 4) = *(undefined4 *)((int)&param_3->value + 4);
  (pNVar1->i_key).nk.tt = param_3->tt;
  if (((3 < param_3->tt) && ((*(byte *)((param_3->value).b + 5) & 3) != 0)) &&
     ((param_2->marked & 4) != 0)) {
    luaC_barrierback(param_1,param_2);
  }
  return &pNVar1->i_val;
}
