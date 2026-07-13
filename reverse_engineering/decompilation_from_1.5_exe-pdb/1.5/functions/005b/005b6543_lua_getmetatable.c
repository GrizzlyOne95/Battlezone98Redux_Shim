/*
 * Entry: 005b6543
 * Name: lua_getmetatable
 * Namespace: Global
 * Signature: int lua_getmetatable(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl lua_getmetatable(lua_State *param_1,int param_2)

{
  int iVar1;
  lua_TValue *plVar2;
  GCObject *pGVar3;
  lua_State *unaff_ESI;
  int unaff_retaddr;
  
  plVar2 = index2adr(unaff_ESI,unaff_retaddr);
  iVar1 = plVar2->tt;
  if ((iVar1 == 5) || (iVar1 == 7)) {
    pGVar3 = *(GCObject **)((plVar2->value).b + 8);
  }
  else {
    pGVar3 = (GCObject *)param_1->l_G->mt[iVar1];
  }
  if (pGVar3 == (GCObject *)0x0) {
    return 0;
  }
  plVar2 = param_1->top;
  (plVar2->value).gc = pGVar3;
  plVar2->tt = 5;
  param_1->top = param_1->top + 1;
  return 1;
}
