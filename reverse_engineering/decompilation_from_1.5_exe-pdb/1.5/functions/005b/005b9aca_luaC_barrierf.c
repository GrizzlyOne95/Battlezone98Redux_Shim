/*
 * Entry: 005b9aca
 * Name: luaC_barrierf
 * Namespace: Global
 * Signature: void luaC_barrierf(lua_State * param_1, GCObject * param_2, GCObject * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaC_barrierf(lua_State *param_1,GCObject *param_2,GCObject *param_3)

{
  global_State *pgVar1;
  
  pgVar1 = param_1->l_G;
  if (pgVar1->gcstate == '\x01') {
    reallymarkobject(pgVar1,param_3);
    return;
  }
  (param_2->gch).marked = pgVar1->currentwhite & 3 | (param_2->gch).marked & 0xf8;
  return;
}
