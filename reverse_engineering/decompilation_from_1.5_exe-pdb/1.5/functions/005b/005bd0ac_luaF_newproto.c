/*
 * Entry: 005bd0ac
 * Name: luaF_newproto
 * Namespace: Global
 * Signature: Proto * luaF_newproto(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Proto * __cdecl luaF_newproto(lua_State *param_1)

{
  GCObject *pGVar1;
  
  pGVar1 = luaM_realloc_(param_1,(void *)0x0,0,0x4c);
  luaC_link(param_1,pGVar1,'\t');
  (pGVar1->h).metatable = (Table *)0x0;
  (pGVar1->p).sizek = 0;
  (pGVar1->h).node = (Node *)0x0;
  (pGVar1->p).sizep = 0;
  (pGVar1->h).array = (lua_TValue *)0x0;
  (pGVar1->p).sizecode = 0;
  (pGVar1->p).sizelineinfo = 0;
  (pGVar1->p).sizeupvalues = 0;
  (pGVar1->p).nups = '\0';
  (pGVar1->h).sizearray = 0;
  (pGVar1->p).numparams = '\0';
  (pGVar1->p).is_vararg = '\0';
  (pGVar1->p).maxstacksize = '\0';
  (pGVar1->h).lastfree = (Node *)0x0;
  (pGVar1->p).sizelocvars = 0;
  (pGVar1->h).gclist = (GCObject *)0x0;
  (pGVar1->p).linedefined = 0;
  (pGVar1->p).lastlinedefined = 0;
  (pGVar1->p).source = (TString *)0x0;
  return (Proto *)pGVar1;
}
