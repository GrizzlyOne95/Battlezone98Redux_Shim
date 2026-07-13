/*
 * Entry: 005bd783
 * Name: luaX_init
 * Namespace: Global
 * Signature: void luaX_init(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl luaX_init(lua_State *param_1)

{
  char *pcVar1;
  char *pcVar2;
  TString *pTVar3;
  char cVar4;
  int iVar5;
  
  iVar5 = 0;
  do {
    pcVar1 = luaX_tokens[iVar5];
    pcVar2 = pcVar1;
    do {
      cVar4 = *pcVar2;
      pcVar2 = pcVar2 + 1;
    } while (cVar4 != '\0');
    pTVar3 = luaS_newlstr(param_1,pcVar1,(int)pcVar2 - (int)(pcVar1 + 1));
    (pTVar3->tsv).marked = (pTVar3->tsv).marked | 0x20;
    cVar4 = (char)iVar5;
    iVar5 = iVar5 + 1;
    (pTVar3->tsv).reserved = cVar4 + '\x01';
  } while (iVar5 < 0x15);
  return;
}
