/*
 * Entry: 005b7be5
 * Name: close_state
 * Namespace: Global
 * Signature: void close_state(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl close_state(lua_State *param_1)

{
  global_State *pgVar1;
  lua_State *in_EAX;
  char *pcVar2;
  lua_State *plVar3;
  
  pgVar1 = in_EAX->l_G;
  luaF_close(in_EAX,in_EAX->stack);
  luaC_freeall(in_EAX);
  luaM_realloc_(in_EAX,(in_EAX->l_G->strt).hash,(in_EAX->l_G->strt).size << 2,0);
  plVar3 = in_EAX;
  pcVar2 = luaM_realloc_(in_EAX,(pgVar1->buff).buffer,(pgVar1->buff).buffsize,0);
  (pgVar1->buff).buffsize = 0;
  (pgVar1->buff).buffer = pcVar2;
  freestack(in_EAX,plVar3);
  (*pgVar1->frealloc)(pgVar1->ud,in_EAX,0x178,0);
  return;
}
