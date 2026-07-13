/*
 * Entry: 005ba964
 * Name: luaT_init
 * Namespace: Global
 * Signature: void luaT_init(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaT_init(lua_State *param_1)

{
  byte *pbVar1;
  char cVar2;
  char *pcVar3;
  char *pcVar4;
  TString *pTVar5;
  int iVar6;
  
  iVar6 = 0xbc;
  do {
    pcVar3 = *(char **)("attempt to compare two %s values" + iVar6 + 0x20);
    pcVar4 = pcVar3;
    do {
      cVar2 = *pcVar4;
      pcVar4 = pcVar4 + 1;
    } while (cVar2 != '\0');
    pTVar5 = luaS_newlstr(param_1,pcVar3,(int)pcVar4 - (int)(pcVar3 + 1));
    *(TString **)((int)&(param_1->l_G->strt).hash + iVar6) = pTVar5;
    pbVar1 = (byte *)(*(int *)((int)&(param_1->l_G->strt).hash + iVar6) + 5);
    *pbVar1 = *pbVar1 | 0x20;
    iVar6 = iVar6 + 4;
  } while (iVar6 < 0x100);
  return;
}
