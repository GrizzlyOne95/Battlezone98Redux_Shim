/*
 * Entry: 005b9751
 * Name: luaC_freeall
 * Namespace: Global
 * Signature: void luaC_freeall(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaC_freeall(lua_State *param_1)

{
  global_State *pgVar1;
  int iVar2;
  
  pgVar1 = param_1->l_G;
  pgVar1->currentwhite = 'C';
  sweeplist(param_1,&pgVar1->rootgc,0xfffffffd);
  iVar2 = 0;
  if (0 < (pgVar1->strt).size) {
    do {
      sweeplist(param_1,(pgVar1->strt).hash + iVar2,0xfffffffd);
      iVar2 = iVar2 + 1;
    } while (iVar2 < (pgVar1->strt).size);
  }
  return;
}
