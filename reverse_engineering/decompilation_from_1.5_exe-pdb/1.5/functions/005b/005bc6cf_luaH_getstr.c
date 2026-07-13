/*
 * Entry: 005bc6cf
 * Name: luaH_getstr
 * Namespace: Global
 * Signature: lua_TValue * luaH_getstr(Table * param_1, TString * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

lua_TValue * __cdecl luaH_getstr(Table *param_1,TString *param_2)

{
  Node *pNVar1;
  
  pNVar1 = param_1->node + ((1 << (param_1->lsizenode & 0x1f)) - 1U & (param_2->tsv).hash);
  while (((pNVar1->i_key).nk.tt != 4 || (*(TString **)&pNVar1->i_key != param_2))) {
    pNVar1 = (pNVar1->i_key).nk.next;
    if (pNVar1 == (Node *)0x0) {
      return &luaO_nilobject_;
    }
  }
  return &pNVar1->i_val;
}
