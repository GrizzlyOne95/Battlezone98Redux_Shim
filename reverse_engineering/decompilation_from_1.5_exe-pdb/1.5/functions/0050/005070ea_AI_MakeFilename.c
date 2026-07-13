/*
 * Entry: 005070ea
 * Name: AI_MakeFilename
 * Namespace: Global
 * Signature: int AI_MakeFilename(char * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl AI_MakeFilename(char *param_1,char *param_2)

{
  char cVar1;
  int iVar2;
  
  if (tinfo.scenariodir[0] != '\0') {
    Mutils_MakeFileName(param_1,tinfo.scenariodir,(char *)0x0,(char *)0x0,param_2,(char *)0x0);
    iVar2 = _access(param_1,0);
    if (iVar2 != -1) {
      return 1;
    }
  }
  if (tinfo.aipdir[0] != '\0') {
    Mutils_MakeFileName(param_1,tinfo.aipdir,(char *)0x0,(char *)0x0,param_2,(char *)0x0);
    iVar2 = _access(param_1,0);
    if (iVar2 != -1) {
      return 1;
    }
  }
  iVar2 = ItemExists(param_2);
  if (iVar2 != 0) {
    iVar2 = (int)param_1 - (int)param_2;
    do {
      cVar1 = *param_2;
      param_2[iVar2] = cVar1;
      param_2 = param_2 + 1;
    } while (cVar1 != '\0');
    return 1;
  }
  *param_1 = '\0';
  return 0;
}
