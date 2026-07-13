/*
 * Entry: 005c373a
 * Name: indexupvalue
 * Namespace: Global
 * Signature: int indexupvalue(FuncState * param_1, TString * param_2, expdesc * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl indexupvalue(FuncState *param_1,TString *param_2,expdesc *param_3)

{
  int *piVar1;
  byte bVar2;
  GCObject *pGVar3;
  undefined4 *in_EAX;
  TString **ppTVar4;
  int iVar5;
  char *unaff_EDI;
  int local_c;
  byte *local_8;
  
  local_c = 0;
  pGVar3 = (GCObject *)*in_EAX;
  piVar1 = &(pGVar3->p).sizeupvalues;
  iVar5 = *piVar1;
  if ((pGVar3->p).nups != '\0') {
    local_8 = (byte *)(in_EAX + 0xd);
    do {
      if (((GCObject *)(uint)local_8[-1] == (param_2->tsv).next) &&
         ((uint)*local_8 == (param_2->tsv).hash)) {
        return local_c;
      }
      local_c = local_c + 1;
      local_8 = local_8 + 2;
    } while (local_c < (int)(uint)(pGVar3->p).nups);
  }
  if (0x3c < (pGVar3->p).nups + 1) {
    errorlimit((FuncState *)0x3c,0x62234c,unaff_EDI);
  }
  if (*piVar1 < (int)((pGVar3->p).nups + 1)) {
    ppTVar4 = luaM_growaux_((lua_State *)in_EAX[4],(pGVar3->p).upvalues,piVar1,4,0x7ffffffd,"");
    (pGVar3->p).upvalues = ppTVar4;
  }
  for (; iVar5 < *piVar1; iVar5 = iVar5 + 1) {
    (pGVar3->p).upvalues[iVar5] = (TString *)0x0;
  }
  (pGVar3->p).upvalues[(pGVar3->p).nups] = (TString *)param_1;
  if ((((uint)param_1->h & 0x300) != 0) && (((pGVar3->gch).marked & 4) != 0)) {
    luaC_barrierf((lua_State *)in_EAX[4],pGVar3,(GCObject *)param_1);
  }
  *(undefined1 *)((int)in_EAX + (uint)(pGVar3->p).nups * 2 + 0x33) = *(undefined1 *)param_2;
  *(char *)((int)in_EAX + (uint)(pGVar3->p).nups * 2 + 0x34) = (char)(param_2->tsv).hash;
  bVar2 = (pGVar3->p).nups;
  (pGVar3->p).nups = bVar2 + 1;
  return (uint)bVar2;
}
