/*
 * Entry: 005b620c
 * Name: lua_topointer
 * Namespace: Global
 * Signature: void * lua_topointer(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl lua_topointer(lua_State *param_1,int param_2)

{
  int iVar1;
  lua_TValue *plVar2;
  void *pvVar3;
  lua_State *unaff_retaddr;
  
  plVar2 = index2adr(unaff_retaddr,(int)param_1);
  iVar1 = plVar2->tt;
  if (iVar1 != 2) {
    if ((iVar1 != 5) && (iVar1 != 6)) {
      if (iVar1 == 7) goto LAB_005b6234;
      if (iVar1 != 8) {
        return (void *)0x0;
      }
    }
    return (plVar2->value).gc;
  }
LAB_005b6234:
  pvVar3 = lua_touserdata(param_1,param_2);
  return pvVar3;
}
