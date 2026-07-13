/*
 * Entry: 005bcdbd
 * Name: luaS_newlstr
 * Namespace: Global
 * Signature: TString * luaS_newlstr(lua_State * param_1, char * param_2, uint param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

TString * __cdecl luaS_newlstr(lua_State *param_1,char *param_2,uint param_3)

{
  char *pcVar1;
  uint uVar2;
  GCObject *pGVar3;
  TString *pTVar4;
  uint uVar5;
  uint unaff_ESI;
  char *pcVar6;
  uint unaff_EDI;
  bool bVar7;
  
  uVar2 = (param_3 >> 5) + 1;
  pcVar1 = (char *)param_3;
  for (uVar5 = param_3; uVar2 <= uVar5; uVar5 = uVar5 - uVar2) {
    pcVar1 = (char *)((uint)pcVar1 ^
                     (uint)(byte)param_2[uVar5 - 1] + (int)pcVar1 * 0x20 + ((uint)pcVar1 >> 2));
  }
  pGVar3 = (param_1->l_G->strt).hash[(param_1->l_G->strt).size - 1U & (uint)pcVar1];
  do {
    if (pGVar3 == (GCObject *)0x0) {
      pTVar4 = newlstr((lua_State *)param_2,pcVar1,unaff_EDI,unaff_ESI);
      return pTVar4;
    }
    if (*(uint *)((int)pGVar3 + 0xc) == param_3) {
      bVar7 = true;
      uVar5 = param_3;
      pcVar6 = param_2;
      pTVar4 = (TString *)((int)pGVar3 + 0x10);
      do {
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        bVar7 = *pcVar6 == *(char *)pTVar4;
        pcVar6 = pcVar6 + 1;
        pTVar4 = (TString *)((int)&(pTVar4->tsv).next + 1);
      } while (bVar7);
      if (bVar7) {
        if (((pGVar3->gch).marked & 3 & ~param_1->l_G->currentwhite) == 0) {
          return (TString *)pGVar3;
        }
        (pGVar3->gch).marked = (pGVar3->gch).marked ^ 3;
        return (TString *)pGVar3;
      }
    }
    pGVar3 = (pGVar3->gch).next;
  } while( true );
}
