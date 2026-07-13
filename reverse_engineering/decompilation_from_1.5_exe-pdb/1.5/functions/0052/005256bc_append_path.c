/*
 * Entry: 005256bc
 * Name: append_path
 * Namespace: Global
 * Signature: char * append_path(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl append_path(char *param_1)

{
  char cVar1;
  int iVar2;
  
  memset(tempname,0,0x50);
  if (loadpath[0] == '\0') {
    iVar2 = (int)tempname - (int)param_1;
    do {
      cVar1 = *param_1;
      param_1[iVar2] = cVar1;
      param_1 = param_1 + 1;
    } while (cVar1 != '\0');
  }
  else {
    sprintf(tempname,"%s\\%s",loadpath,param_1);
  }
  return tempname;
}
