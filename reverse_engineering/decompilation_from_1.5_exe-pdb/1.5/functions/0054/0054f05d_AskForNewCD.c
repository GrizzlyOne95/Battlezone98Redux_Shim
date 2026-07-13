/*
 * Entry: 0054f05d
 * Name: AskForNewCD
 * Namespace: Global
 * Signature: int AskForNewCD(char param_1, char * param_2, char * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl AskForNewCD(char param_1,char *param_2,char *param_3)

{
  char *pcVar1;
  int iVar2;
  
  do {
    pcVar1 = (char *)_StrLookupFind(_DAT_00224566,"Please insert CD \"%s\"",param_3);
    I76Warning(pcVar1);
    iVar2 = FindCDByName(param_2,1);
  } while (iVar2 == 0);
  return 1;
}
