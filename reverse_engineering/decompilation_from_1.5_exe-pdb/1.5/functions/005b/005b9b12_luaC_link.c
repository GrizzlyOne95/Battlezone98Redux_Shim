/*
 * Entry: 005b9b12
 * Name: luaC_link
 * Namespace: Global
 * Signature: void luaC_link(lua_State * param_1, GCObject * param_2, uchar param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaC_link(lua_State *param_1,GCObject *param_2,uchar param_3)

{
  global_State *pgVar1;
  
  pgVar1 = param_1->l_G;
  (param_2->gch).next = pgVar1->rootgc;
  pgVar1->rootgc = param_2;
  (param_2->gch).marked = pgVar1->currentwhite & 3;
  (param_2->gch).tt = param_3;
  return;
}
