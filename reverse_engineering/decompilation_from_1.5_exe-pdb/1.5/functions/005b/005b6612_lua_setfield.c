/*
 * Entry: 005b6612
 * Name: lua_setfield
 * Namespace: Global
 * Signature: void lua_setfield(lua_State * param_1, int param_2, char * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl lua_setfield(lua_State *param_1,int param_2,char *param_3)

{
  char cVar1;
  lua_TValue *plVar2;
  char *pcVar3;
  int unaff_ESI;
  lua_State *unaff_EDI;
  Value local_14;
  undefined4 local_c;
  
  plVar2 = index2adr(unaff_EDI,unaff_ESI);
  pcVar3 = param_3;
  do {
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  local_14.gc = (GCObject *)luaS_newlstr(param_1,param_3,(int)pcVar3 - (int)(param_3 + 1));
  local_c = 4;
  luaV_settable(param_1,plVar2,(lua_TValue *)&local_14,param_1->top + -1);
  param_1->top = param_1->top + -1;
  return;
}
