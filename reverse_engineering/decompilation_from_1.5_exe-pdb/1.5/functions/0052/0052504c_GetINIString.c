/*
 * Entry: 0052504c
 * Name: GetINIString
 * Namespace: Global
 * Signature: ulong GetINIString(char * param_1, char * param_2, char * param_3, char * param_4, ulong param_5, char * param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ulong __cdecl
GetINIString(char *param_1,char *param_2,char *param_3,char *param_4,ulong param_5,char *param_6)

{
  char *pcVar1;
  int unaff_EBX;
  
  strncpy(param_4,param_3,param_5);
  param_4[param_5 - 1] = '\0';
  if ((((*param_6 != '\0') && (*param_1 != '\0')) && (*param_2 != '\0')) &&
     (pcVar1 = GetFilePtr(param_6), pcVar1 != (char *)0x0)) {
    GetKeyString(param_2,param_4,(char *)param_5,unaff_EBX);
  }
  return 0;
}
