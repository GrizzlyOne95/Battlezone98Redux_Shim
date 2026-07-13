/*
 * Entry: 0054f090
 * Name: CheckForI76CD
 * Namespace: Global
 * Signature: long CheckForI76CD(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

long __cdecl CheckForI76CD(int param_1)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  long lVar4;
  
  lVar4 = 0;
  if (CDError == 0) {
    PlayerDone();
    PlayerInit();
    lVar4 = 1;
  }
  else {
    PlayerInit();
    if (CDError == 0) {
      PlayerDone();
      do {
        iVar2 = FindCDByName("BZONE",1);
        if ((iVar2 != 0) && (iVar2 = PlayerInit(), iVar2 != 0)) {
          return 1;
        }
        cVar1 = WhichCD;
        if (param_1 == 0) {
          return 0;
        }
        pcVar3 = (char *)_StrLookupFind(_DAT_00224566,"Battlezone CD 2");
        iVar2 = AskForNewCD(cVar1,"BZONE",pcVar3);
      } while (iVar2 != 0);
    }
    else {
      lVar4 = -1;
    }
  }
  return lVar4;
}
