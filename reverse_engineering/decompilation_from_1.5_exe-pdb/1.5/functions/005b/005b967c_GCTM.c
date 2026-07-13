/*
 * Entry: 005b967c
 * Name: GCTM
 * Namespace: Global
 * Signature: void GCTM(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl GCTM(lua_State *param_1)

{
  uchar uVar1;
  global_State *pgVar2;
  GCObject *pGVar3;
  GCObject *pGVar4;
  Table *pTVar5;
  uint uVar6;
  lua_TValue *plVar7;
  lua_TValue *plVar8;
  lua_State *unaff_ESI;
  
  pgVar2 = unaff_ESI->l_G;
  pGVar3 = pgVar2->tmudata;
  pGVar4 = (pGVar3->gch).next;
  if (pGVar4 == pGVar3) {
    pgVar2->tmudata = (GCObject *)0x0;
  }
  else {
    (pGVar3->gch).next = (pGVar4->gch).next;
  }
  (pGVar4->gch).next = pgVar2->mainthread->next;
  pgVar2->mainthread->next = pGVar4;
  (pGVar4->gch).marked = pgVar2->currentwhite & 3 | (pGVar4->gch).marked & 0xf8;
  pTVar5 = (pGVar4->h).metatable;
  if ((pTVar5 != (Table *)0x0) && ((pTVar5->flags & 4) == 0)) {
    plVar8 = luaT_gettm(pTVar5,TM_GC,unaff_ESI->l_G->tmname[2]);
    if (plVar8 != (lua_TValue *)0x0) {
      uVar1 = unaff_ESI->allowhook;
      uVar6 = pgVar2->GCthreshold;
      unaff_ESI->allowhook = '\0';
      pgVar2->GCthreshold = pgVar2->totalbytes * 2;
      plVar7 = unaff_ESI->top;
      (plVar7->value).gc = (plVar8->value).gc;
      *(undefined4 *)((int)&plVar7->value + 4) = *(undefined4 *)((int)&plVar8->value + 4);
      plVar7->tt = plVar8->tt;
      plVar8 = unaff_ESI->top;
      plVar8[1].value.b = (int)pGVar4;
      plVar8[1].tt = 7;
      unaff_ESI->top = unaff_ESI->top + 2;
      luaD_call(unaff_ESI,unaff_ESI->top + -2,0);
      unaff_ESI->allowhook = uVar1;
      pgVar2->GCthreshold = uVar6;
    }
  }
  return;
}
