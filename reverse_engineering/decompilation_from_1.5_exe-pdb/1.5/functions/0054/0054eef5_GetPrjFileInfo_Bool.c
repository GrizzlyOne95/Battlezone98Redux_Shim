/*
 * Entry: 0054eef5
 * Name: GetPrjFileInfo_Bool
 * Namespace: Global
 * Signature: int GetPrjFileInfo_Bool(char * param_1, int * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl GetPrjFileInfo_Bool(char *param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  char local_108 [128];
  undefined1 local_88 [128];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_88;
  iVar2 = 0;
  iVar1 = GetPrjFileInfo(param_1,local_108,0x100);
  if (iVar1 != 0) {
    iVar1 = _stricmp(local_108,"TRUE");
    if (((iVar1 == 0) || (iVar1 = _stricmp(local_108,"ON"), iVar1 == 0)) ||
       (iVar1 = _stricmp(local_108,"1"), iVar1 == 0)) {
      iVar1 = 1;
    }
    else {
      iVar1 = _stricmp(local_108,"FALSE");
      if (((iVar1 != 0) && (iVar1 = _stricmp(local_108,"OFF"), iVar1 != 0)) &&
         (iVar1 = _stricmp(local_108,"0"), iVar1 != 0)) {
        return 0;
      }
      iVar1 = 0;
    }
    iVar2 = 1;
    *param_2 = iVar1;
  }
  return iVar2;
}
