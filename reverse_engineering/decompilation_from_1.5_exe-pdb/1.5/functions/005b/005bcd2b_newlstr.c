/*
 * Entry: 005bcd2b
 * Name: newlstr
 * Namespace: Global
 * Signature: TString * newlstr(lua_State * param_1, char * param_2, uint param_3, uint param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

TString * __cdecl newlstr(lua_State *param_1,char *param_2,uint param_3,uint param_4)

{
  uint *puVar1;
  global_State *pgVar2;
  GCObject *pGVar3;
  uint uVar4;
  lua_State *unaff_EBX;
  lua_TValue *unaff_EDI;
  
  if ((undefined1 *)0xffffffed < (undefined1 *)((int)&unaff_EDI->value + 1U)) {
    luaM_toobig(unaff_EBX);
  }
  pGVar3 = luaM_realloc_(unaff_EBX,(void *)0x0,0,(uint)((int)&unaff_EDI[1].value + 1));
  (pGVar3->h).metatable = (Table *)param_2;
  (pGVar3->h).array = unaff_EDI;
  (pGVar3->gch).marked = unaff_EBX->l_G->currentwhite & 3;
  (pGVar3->gch).tt = '\x04';
  (pGVar3->h).flags = '\0';
  memcpy(&pGVar3->ts + 1,param_1);
  *(undefined1 *)((int)pGVar3 + (int)(unaff_EDI + 1)) = 0;
  pgVar2 = unaff_EBX->l_G;
  uVar4 = (uint)param_2 & (pgVar2->strt).size - 1U;
  (pGVar3->gch).next = (pgVar2->strt).hash[uVar4];
  (pgVar2->strt).hash[uVar4] = pGVar3;
  puVar1 = &(pgVar2->strt).nuse;
  *puVar1 = *puVar1 + 1;
  uVar4 = (pgVar2->strt).size;
  if ((uVar4 < (pgVar2->strt).nuse) && ((int)uVar4 < 0x3fffffff)) {
    luaS_resize(unaff_EBX,uVar4 * 2);
  }
  return (TString *)pGVar3;
}
