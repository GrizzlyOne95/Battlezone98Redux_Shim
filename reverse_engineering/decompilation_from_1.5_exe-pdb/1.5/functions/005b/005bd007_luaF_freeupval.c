/*
 * Entry: 005bd007
 * Name: luaF_freeupval
 * Namespace: Global
 * Signature: void luaF_freeupval(lua_State * param_1, UpVal * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaF_freeupval(lua_State *param_1,UpVal *param_2)

{
  <unnamed_tag_00001197> *p<Var1;
  
  p<Var1 = &param_2->u;
  if (param_2->v != (lua_TValue *)p<Var1) {
    (((param_2->u).l.next)->u).l.prev = (p<Var1->l).prev;
    (((p<Var1->l).prev)->u).l.next = (param_2->u).l.next;
  }
  luaM_realloc_(param_1,param_2,0x20,0);
  return;
}
