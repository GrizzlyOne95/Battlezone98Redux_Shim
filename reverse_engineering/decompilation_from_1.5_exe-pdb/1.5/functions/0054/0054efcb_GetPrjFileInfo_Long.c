/*
 * Entry: 0054efcb
 * Name: GetPrjFileInfo_Long
 * Namespace: Global
 * Signature: int GetPrjFileInfo_Long(char * param_1, long * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl GetPrjFileInfo_Long(char *param_1,long *param_2)

{
  int iVar1;
  long lVar2;
  int iVar3;
  char *pcVar4;
  char local_108 [256];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  iVar3 = 0;
  iVar1 = GetPrjFileInfo(param_1,local_108,0x100);
  if ((iVar1 != 0) && (local_108[0] != '\0')) {
    pcVar4 = local_108;
    do {
      iVar1 = isdigit((int)*pcVar4);
      if (iVar1 == 0) break;
      pcVar4 = pcVar4 + 1;
    } while (*pcVar4 != '\0');
    if ((*pcVar4 != '\0') && (iVar1 = isspace((int)*pcVar4), iVar1 == 0)) {
      return 0;
    }
    lVar2 = atol(local_108);
    *param_2 = lVar2;
    iVar3 = 1;
  }
  return iVar3;
}
