/*
 * Entry: 005b9af9
 * Name: luaC_barrierback
 * Namespace: Global
 * Signature: void luaC_barrierback(lua_State * param_1, Table * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaC_barrierback(lua_State *param_1,Table *param_2)

{
  global_State *pgVar1;
  
  pgVar1 = param_1->l_G;
  param_2->marked = param_2->marked & 0xfb;
  param_2->gclist = pgVar1->grayagain;
  pgVar1->grayagain = (GCObject *)param_2;
  return;
}
