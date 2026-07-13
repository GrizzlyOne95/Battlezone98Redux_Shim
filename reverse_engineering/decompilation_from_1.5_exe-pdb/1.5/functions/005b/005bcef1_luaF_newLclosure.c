/*
 * Entry: 005bcef1
 * Name: luaF_newLclosure
 * Namespace: Global
 * Signature: Closure * luaF_newLclosure(lua_State * param_1, int param_2, Table * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Closure * __cdecl luaF_newLclosure(lua_State *param_1,int param_2,Table *param_3)

{
  uint uVar1;
  GCObject *pGVar2;
  undefined4 *puVar3;
  
  uVar1 = param_2 * 4 + 0x14;
  pGVar2 = luaM_realloc_(param_1,(void *)0x0,0,uVar1);
  luaC_link(param_1,pGVar2,'\x06');
  (pGVar2->h).flags = '\0';
  (pGVar2->h).array = (lua_TValue *)param_3;
  (pGVar2->h).lsizenode = (uchar)param_2;
  if (param_2 != 0) {
    puVar3 = (undefined4 *)(uVar1 + (int)pGVar2);
    do {
      puVar3 = puVar3 + -1;
      *puVar3 = 0;
      param_2 = param_2 + -1;
    } while (param_2 != 0);
  }
  return (Closure *)pGVar2;
}
