/*
 * Entry: 005ba79d
 * Name: lua_getinfo
 * Namespace: Global
 * Signature: int lua_getinfo(lua_State * param_1, char * param_2, lua_Debug * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl lua_getinfo(lua_State *param_1,char *param_2,lua_Debug *param_3)

{
  lua_TValue *plVar1;
  int iVar2;
  char *pcVar3;
  CallInfo *unaff_EBX;
  GCObject *pGVar4;
  Closure *unaff_ESI;
  lua_State *unaff_EDI;
  
  pGVar4 = (GCObject *)0x0;
  if (*param_2 == '>') {
    param_2 = param_2 + 1;
    pGVar4 = param_1->top[-1].value.gc;
    param_1->top = param_1->top + -1;
  }
  else if (param_3->i_ci != 0) {
    pGVar4 = ((param_1->base_ci[param_3->i_ci].func)->value).gc;
  }
  iVar2 = auxgetinfo(param_1,(char *)pGVar4,(lua_Debug *)unaff_EDI,unaff_ESI,unaff_EBX);
  pcVar3 = strchr(param_2,0x66);
  if (pcVar3 != (char *)0x0) {
    plVar1 = param_1->top;
    if (pGVar4 == (GCObject *)0x0) {
      plVar1->tt = 0;
    }
    else {
      (plVar1->value).gc = pGVar4;
      plVar1->tt = 6;
    }
    if ((int)param_1->stack_last - (int)param_1->top < 0x11) {
      luaD_growstack(param_1,1);
    }
    param_1->top = param_1->top + 1;
  }
  pcVar3 = strchr(param_2,0x4c);
  if (pcVar3 != (char *)0x0) {
    collectvalidlines(unaff_EDI,unaff_ESI);
  }
  return iVar2;
}
