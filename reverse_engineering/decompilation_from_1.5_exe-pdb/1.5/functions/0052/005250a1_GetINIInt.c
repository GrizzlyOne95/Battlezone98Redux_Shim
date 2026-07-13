/*
 * Entry: 005250a1
 * Name: GetINIInt
 * Namespace: Global
 * Signature: int GetINIInt(char * param_1, char * param_2, int param_3, char * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl GetINIInt(char *param_1,char *param_2,int param_3,char *param_4)

{
  char *pcVar1;
  int iVar2;
  int unaff_EDI;
  int local_1c;
  char local_18 [16];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_1c = param_3;
  if (((*param_4 != '\0') && (*param_1 != '\0')) && (*param_2 != '\0')) {
    pcVar1 = GetFilePtr(param_4);
    if (pcVar1 != (char *)0x0) {
      iVar2 = GetKeyString(param_2,local_18,(char *)0x10,unaff_EDI);
      if (-1 < iVar2) {
        sscanf(local_18,"%i",&local_1c);
      }
    }
  }
  return local_1c;
}
