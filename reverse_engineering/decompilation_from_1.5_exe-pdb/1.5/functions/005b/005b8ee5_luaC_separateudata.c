/*
 * Entry: 005b8ee5
 * Name: luaC_separateudata
 * Namespace: Global
 * Signature: uint luaC_separateudata(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __cdecl luaC_separateudata(lua_State *param_1,int param_2)

{
  global_State *pgVar1;
  Table *pTVar2;
  GCObject *pGVar3;
  lua_TValue *plVar4;
  GCObject *pGVar5;
  uint local_8;
  
  local_8 = 0;
  pgVar1 = param_1->l_G;
  pGVar3 = (GCObject *)pgVar1->mainthread;
  while (pGVar5 = pGVar3, pGVar3 = (pGVar5->gch).next, pGVar3 != (GCObject *)0x0) {
    if (((((pGVar3->gch).marked & 3) != 0) || (param_2 != 0)) && (((pGVar3->gch).marked & 8) == 0))
    {
      pTVar2 = (pGVar3->h).metatable;
      if (((pTVar2 == (Table *)0x0) || ((pTVar2->flags & 4) != 0)) ||
         (plVar4 = luaT_gettm(pTVar2,TM_GC,param_1->l_G->tmname[2]), plVar4 == (lua_TValue *)0x0)) {
        (pGVar3->gch).marked = (pGVar3->gch).marked | 8;
      }
      else {
        (pGVar3->gch).marked = (pGVar3->gch).marked | 8;
        local_8 = (int)(pGVar3->h).node + 0x98 + (local_8 - 0x80);
        (pGVar5->gch).next = (pGVar3->gch).next;
        if (pgVar1->tmudata == (GCObject *)0x0) {
          (pGVar3->gch).next = pGVar3;
        }
        else {
          (pGVar3->gch).next = (pgVar1->tmudata->gch).next;
          (pgVar1->tmudata->gch).next = pGVar3;
        }
        pgVar1->tmudata = pGVar3;
        pGVar3 = pGVar5;
      }
    }
  }
  return local_8;
}
