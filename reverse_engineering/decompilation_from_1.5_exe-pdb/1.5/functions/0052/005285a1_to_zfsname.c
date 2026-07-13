/*
 * Entry: 005285a1
 * Name: to_zfsname
 * Namespace: Global
 * Signature: void to_zfsname(char * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl to_zfsname(char *param_1,char *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 0;
  iVar2 = (int)param_1 - (int)param_2;
  do {
    if (*param_2 == '\0') break;
    iVar1 = tolower((int)*param_2);
    iVar3 = iVar3 + 1;
    param_2[iVar2] = (char)iVar1;
    param_2 = param_2 + 1;
  } while (iVar3 < 0x10);
  if (iVar3 < 0x10) {
    memset(param_1 + iVar3,0,0x10 - iVar3);
  }
  return;
}
