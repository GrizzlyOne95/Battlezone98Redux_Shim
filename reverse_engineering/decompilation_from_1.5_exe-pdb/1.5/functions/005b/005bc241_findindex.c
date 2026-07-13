/*
 * Entry: 005bc241
 * Name: findindex
 * Namespace: Global
 * Signature: int findindex(lua_State * param_1, Table * param_2, lua_TValue * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl findindex(lua_State *param_1,Table *param_2,lua_TValue *param_3)

{
  int iVar1;
  Node *pNVar2;
  Table *unaff_ESI;
  lua_TValue *unaff_EDI;
  lua_TValue *unaff_retaddr;
  
  if (unaff_EDI->tt == 0) {
    return -1;
  }
  iVar1 = arrayindex(unaff_retaddr);
  if ((0 < iVar1) && (iVar1 <= param_2->sizearray)) {
    return iVar1 + -1;
  }
  pNVar2 = mainposition(unaff_ESI,unaff_retaddr);
  while( true ) {
    iVar1 = luaO_rawequalObj(&(pNVar2->i_key).tvk,unaff_EDI);
    if ((iVar1 != 0) ||
       ((((pNVar2->i_key).nk.tt == 0xb && (3 < unaff_EDI->tt)) &&
        (*(GCObject **)&pNVar2->i_key == (unaff_EDI->value).gc)))) break;
    pNVar2 = (pNVar2->i_key).nk.next;
    if (pNVar2 == (Node *)0x0) {
      luaG_runerror(param_1,"invalid key to \'next\'");
      return 0;
    }
  }
  return ((int)pNVar2 - (int)param_2->node >> 5) + param_2->sizearray;
}
