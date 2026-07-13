/*
 * Entry: 00525651
 * Name: fix_fname
 * Namespace: Global
 * Signature: char * fix_fname(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl fix_fname(char *param_1)

{
  char cVar1;
  char *pcVar2;
  int iVar3;
  
  memset(tempname,0,0x50);
  if (((loadpath[0] != '\0') && (pcVar2 = strchr(param_1,0x5c), pcVar2 == (char *)0x0)) &&
     (pcVar2 = strchr(param_1,0x2f), pcVar2 == (char *)0x0)) {
    sprintf(tempname,"%s\\%s",loadpath,param_1);
    return tempname;
  }
  iVar3 = (int)tempname - (int)param_1;
  do {
    cVar1 = *param_1;
    param_1[iVar3] = cVar1;
    param_1 = param_1 + 1;
  } while (cVar1 != '\0');
  return tempname;
}
