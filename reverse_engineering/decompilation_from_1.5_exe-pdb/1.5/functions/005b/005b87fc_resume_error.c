/*
 * Entry: 005b87fc
 * Name: resume_error
 * Namespace: Global
 * Signature: int resume_error(lua_State * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl resume_error(lua_State *param_1,char *param_2)

{
  lua_TValue *plVar1;
  GCObject **ppGVar2;
  lua_State *plVar3;
  GCObject *pGVar4;
  lua_State *unaff_ESI;
  
  plVar1 = unaff_ESI->ci->base;
  unaff_ESI->top = plVar1;
  plVar3 = param_1;
  do {
    ppGVar2 = &plVar3->next;
    plVar3 = (lua_State *)((int)&plVar3->next + 1);
  } while (*(char *)ppGVar2 != '\0');
  pGVar4 = (GCObject *)
           luaS_newlstr(unaff_ESI,(char *)param_1,(int)plVar3 - (int)((int)&param_1->next + 1));
  (plVar1->value).gc = pGVar4;
  plVar1->tt = 4;
  if ((int)unaff_ESI->stack_last - (int)unaff_ESI->top < 0x11) {
    luaD_growstack(unaff_ESI,1);
  }
  unaff_ESI->top = unaff_ESI->top + 1;
  return 2;
}
