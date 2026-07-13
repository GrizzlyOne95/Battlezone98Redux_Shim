/*
 * Entry: 005bceb1
 * Name: luaF_newCclosure
 * Namespace: Global
 * Signature: Closure * luaF_newCclosure(lua_State * param_1, int param_2, Table * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Closure * __cdecl luaF_newCclosure(lua_State *param_1,int param_2,Table *param_3)

{
  GCObject *pGVar1;
  
  pGVar1 = luaM_realloc_(param_1,(void *)0x0,0,param_2 * 0x10 + 0x18);
  luaC_link(param_1,pGVar1,'\x06');
  (pGVar1->h).array = (lua_TValue *)param_3;
  (pGVar1->h).lsizenode = (uchar)param_2;
  (pGVar1->h).flags = '\x01';
  return (Closure *)pGVar1;
}
