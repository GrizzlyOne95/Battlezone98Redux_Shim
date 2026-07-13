/*
 * Entry: 005b7b34
 * Name: f_luaopen
 * Namespace: Global
 * Signature: void f_luaopen(lua_State * param_1, void * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl f_luaopen(lua_State *param_1,void *param_2)

{
  global_State *pgVar1;
  global_State *pgVar2;
  GCObject *pGVar3;
  TString *pTVar4;
  lua_State *unaff_EDI;
  
  pgVar1 = param_1->l_G;
  stack_init(param_1,unaff_EDI);
  pGVar3 = (GCObject *)luaH_new(param_1,0,2);
  (param_1->l_gt).value.gc = pGVar3;
  (param_1->l_gt).tt = 5;
  pgVar2 = param_1->l_G;
  pGVar3 = (GCObject *)luaH_new(param_1,0,2);
  (pgVar2->l_registry).value.gc = pGVar3;
  (pgVar2->l_registry).tt = 5;
  luaS_resize(param_1,0x20);
  luaT_init(param_1);
  luaX_init(param_1);
  pTVar4 = luaS_newlstr(param_1,"not enough memory",0x11);
  (pTVar4->tsv).marked = (pTVar4->tsv).marked | 0x20;
  pgVar1->GCthreshold = pgVar1->totalbytes << 2;
  return;
}
