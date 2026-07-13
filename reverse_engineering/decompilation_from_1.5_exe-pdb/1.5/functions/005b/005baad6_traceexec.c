/*
 * Entry: 005baad6
 * Name: traceexec
 * Namespace: Global
 * Signature: void traceexec(lua_State * param_1, uint * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl traceexec(lua_State *param_1,uint *param_2)

{
  byte bVar1;
  lua_State *plVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  lua_State *unaff_ESI;
  
  bVar1 = unaff_ESI->hookmask;
  plVar2 = (lua_State *)unaff_ESI->savedpc;
  unaff_ESI->savedpc = (uint *)param_1;
  if (((bVar1 & 8) != 0) && (unaff_ESI->hookcount == 0)) {
    unaff_ESI->hookcount = unaff_ESI->basehookcount;
    luaD_callhook(unaff_ESI,3,-1);
  }
  if ((bVar1 & 4) != 0) {
    iVar5 = *(int *)((unaff_ESI->ci->func->value).b + 0x10);
    iVar3 = *(int *)(iVar5 + 0xc);
    iVar5 = *(int *)(iVar5 + 0x14);
    iVar4 = ((int)param_1 - iVar3 >> 2) + -1;
    if (iVar5 == 0) {
      iVar6 = 0;
    }
    else {
      iVar6 = *(int *)(iVar5 + iVar4 * 4);
    }
    if ((iVar4 != 0) && (plVar2 < param_1)) {
      if (iVar5 == 0) {
        iVar5 = 0;
      }
      else {
        iVar5 = *(int *)(iVar5 + -4 + ((int)plVar2 - iVar3 >> 2) * 4);
      }
      if (iVar6 == iVar5) {
        return;
      }
    }
    luaD_callhook(unaff_ESI,2,iVar6);
  }
  return;
}
