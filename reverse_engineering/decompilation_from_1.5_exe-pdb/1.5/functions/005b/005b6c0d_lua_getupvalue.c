/*
 * Entry: 005b6c0d
 * Name: lua_getupvalue
 * Namespace: Global
 * Signature: char * lua_getupvalue(lua_State * param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl lua_getupvalue(lua_State *param_1,int param_2,int param_3)

{
  lua_TValue *plVar1;
  char *pcVar2;
  int unaff_ESI;
  lua_State *unaff_EDI;
  lua_TValue **extraout_var;
  lua_TValue **pplVar3;
  
  index2adr(unaff_EDI,unaff_ESI);
  pplVar3 = extraout_var;
  pcVar2 = aux_upvalue((lua_TValue *)unaff_EDI,unaff_ESI,extraout_var);
  if (pcVar2 != (char *)0x0) {
    plVar1 = param_1->top;
    (plVar1->value).gc = (GCObject *)*pplVar3;
    *(lua_TValue **)((int)&plVar1->value + 4) = pplVar3[1];
    plVar1->tt = (int)pplVar3[2];
    param_1->top = param_1->top + 1;
  }
  return pcVar2;
}
