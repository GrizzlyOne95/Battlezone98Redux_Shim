/*
 * Entry: 005bd8e4
 * Name: luaX_newstring
 * Namespace: Global
 * Signature: TString * luaX_newstring(LexState * param_1, char * param_2, uint param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

TString * __cdecl luaX_newstring(LexState *param_1,char *param_2,uint param_3)

{
  lua_State *plVar1;
  TString *pTVar2;
  lua_TValue *plVar3;
  
  plVar1 = param_1->L;
  pTVar2 = luaS_newlstr(plVar1,param_2,param_3);
  plVar3 = luaH_setstr(plVar1,param_1->fs->h,pTVar2);
  if (plVar3->tt == 0) {
    (plVar3->value).b = 1;
    plVar3->tt = 1;
    if (plVar1->l_G->GCthreshold <= plVar1->l_G->totalbytes) {
      luaC_step(plVar1);
    }
  }
  return pTVar2;
}
