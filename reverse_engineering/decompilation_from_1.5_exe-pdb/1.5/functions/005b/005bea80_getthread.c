/*
 * Entry: 005bea80
 * Name: getthread
 * Namespace: Global
 * Signature: lua_State * getthread(lua_State * param_1, int * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

lua_State * __cdecl getthread(lua_State *param_1,int *param_2)

{
  int iVar1;
  lua_State *plVar2;
  undefined4 *unaff_ESI;
  
  iVar1 = lua_type(param_1,1);
  if (iVar1 == 8) {
    *unaff_ESI = 1;
    plVar2 = lua_tothread(param_1,1);
    return plVar2;
  }
  *unaff_ESI = 0;
  return param_1;
}
