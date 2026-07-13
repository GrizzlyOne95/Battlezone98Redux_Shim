/*
 * Entry: 005b6c4f
 * Name: lua_setupvalue
 * Namespace: Global
 * Signature: char * lua_setupvalue(lua_State * param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl lua_setupvalue(lua_State *param_1,int param_2,int param_3)

{
  lua_TValue *plVar1;
  GCObject *pGVar2;
  lua_TValue *plVar3;
  char *pcVar4;
  undefined4 *in_ECX;
  lua_TValue **unaff_EBX;
  int unaff_ESI;
  lua_State *unaff_EDI;
  
  plVar3 = index2adr(unaff_EDI,unaff_ESI);
  pcVar4 = aux_upvalue((lua_TValue *)unaff_EDI,unaff_ESI,unaff_EBX);
  if (pcVar4 != (char *)0x0) {
    param_1->top = param_1->top + -1;
    plVar1 = param_1->top;
    *in_ECX = (plVar1->value).gc;
    in_ECX[1] = *(undefined4 *)((int)&plVar1->value + 4);
    in_ECX[2] = plVar1->tt;
    if (((3 < param_1->top->tt) &&
        (pGVar2 = (param_1->top->value).gc, ((pGVar2->gch).marked & 3) != 0)) &&
       (((((plVar3->value).gc)->gch).marked & 4) != 0)) {
      luaC_barrierf(param_1,(plVar3->value).gc,pGVar2);
    }
  }
  return pcVar4;
}
