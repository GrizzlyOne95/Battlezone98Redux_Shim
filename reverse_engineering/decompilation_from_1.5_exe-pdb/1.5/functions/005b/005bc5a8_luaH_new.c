/*
 * Entry: 005bc5a8
 * Name: luaH_new
 * Namespace: Global
 * Signature: Table * luaH_new(lua_State * param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Table * __cdecl luaH_new(lua_State *param_1,int param_2,int param_3)

{
  GCObject *pGVar1;
  lua_State *plVar2;
  lua_State *plVar3;
  GCObject *pGVar4;
  
  pGVar1 = luaM_realloc_(param_1,(void *)0x0,0,0x20);
  plVar3 = param_1;
  pGVar4 = pGVar1;
  luaC_link(param_1,pGVar1,'\x05');
  (pGVar1->h).metatable = (Table *)0x0;
  (pGVar1->h).flags = 0xff;
  (pGVar1->h).array = (lua_TValue *)0x0;
  (pGVar1->h).sizearray = 0;
  (pGVar1->h).lsizenode = '\0';
  (pGVar1->h).node = &dummynode_;
  plVar2 = param_1;
  setarrayvector(param_1,(Table *)plVar3,(int)pGVar4);
  setnodevector(param_1,(Table *)plVar2,(int)plVar3);
  return (Table *)pGVar1;
}
