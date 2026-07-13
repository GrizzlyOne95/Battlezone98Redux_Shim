/*
 * Entry: 005bcc7c
 * Name: luaS_resize
 * Namespace: Global
 * Signature: void luaS_resize(lua_State * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaS_resize(lua_State *param_1,int param_2)

{
  global_State *pgVar1;
  GCObject *pGVar2;
  GCObject *pGVar3;
  GCObject **ppGVar4;
  int iVar5;
  GCObject **ppGVar6;
  int local_8;
  
  if (param_1->l_G->gcstate != '\x02') {
    if (param_2 + 1U < 0x40000000) {
      ppGVar4 = luaM_realloc_(param_1,(void *)0x0,0,param_2 << 2);
    }
    else {
      ppGVar4 = luaM_toobig(param_1);
    }
    pgVar1 = param_1->l_G;
    iVar5 = param_2;
    ppGVar6 = ppGVar4;
    if (0 < param_2) {
      for (; iVar5 != 0; iVar5 = iVar5 + -1) {
        *ppGVar6 = (GCObject *)0x0;
        ppGVar6 = ppGVar6 + 1;
      }
    }
    local_8 = 0;
    if (0 < (pgVar1->strt).size) {
      do {
        pGVar3 = (pgVar1->strt).hash[local_8];
        while (pGVar3 != (GCObject *)0x0) {
          pGVar2 = (pGVar3->gch).next;
          (pGVar3->gch).next = ppGVar4[*(uint *)((int)pGVar3 + 8) & param_2 - 1U];
          ppGVar4[*(uint *)((int)pGVar3 + 8) & param_2 - 1U] = pGVar3;
          pGVar3 = pGVar2;
        }
        local_8 = local_8 + 1;
      } while (local_8 < (pgVar1->strt).size);
    }
    luaM_realloc_(param_1,(pgVar1->strt).hash,(pgVar1->strt).size << 2,0);
    (pgVar1->strt).size = param_2;
    (pgVar1->strt).hash = ppGVar4;
  }
  return;
}
