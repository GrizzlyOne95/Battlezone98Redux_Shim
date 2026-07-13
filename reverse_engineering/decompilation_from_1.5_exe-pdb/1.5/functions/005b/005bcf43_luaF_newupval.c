/*
 * Entry: 005bcf43
 * Name: luaF_newupval
 * Namespace: Global
 * Signature: UpVal * luaF_newupval(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

UpVal * __cdecl luaF_newupval(lua_State *param_1)

{
  GCObject *pGVar1;
  
  pGVar1 = luaM_realloc_(param_1,(void *)0x0,0,0x20);
  luaC_link(param_1,pGVar1,'\n');
  (pGVar1->h).metatable = (Table *)&(pGVar1->h).node;
  (pGVar1->h).gclist = (GCObject *)0x0;
  return (UpVal *)pGVar1;
}
