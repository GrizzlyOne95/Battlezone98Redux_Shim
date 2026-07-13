/*
 * Entry: 005bc701
 * Name: luaH_get
 * Namespace: Global
 * Signature: lua_TValue * luaH_get(Table * param_1, lua_TValue * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

lua_TValue * __cdecl luaH_get(Table *param_1,lua_TValue *param_2)

{
  lua_TValue *plVar1;
  Node *pNVar2;
  int iVar3;
  lua_TValue *unaff_ESI;
  Table *unaff_EDI;
  
  iVar3 = param_2->tt;
  if (iVar3 != 0) {
    if (iVar3 == 3) {
      if ((double)(int)ROUND((param_2->value).n) == (param_2->value).n) {
        plVar1 = luaH_getnum(param_1,(int)ROUND((param_2->value).n));
        return plVar1;
      }
    }
    else if (iVar3 == 4) {
      plVar1 = luaH_getstr(param_1,&((param_2->value).gc)->ts);
      return plVar1;
    }
    pNVar2 = mainposition(unaff_EDI,unaff_ESI);
    do {
      iVar3 = luaO_rawequalObj(&(pNVar2->i_key).tvk,param_2);
      if (iVar3 != 0) {
        return &pNVar2->i_val;
      }
      pNVar2 = (pNVar2->i_key).nk.next;
    } while (pNVar2 != (Node *)0x0);
  }
  return &luaO_nilobject_;
}
