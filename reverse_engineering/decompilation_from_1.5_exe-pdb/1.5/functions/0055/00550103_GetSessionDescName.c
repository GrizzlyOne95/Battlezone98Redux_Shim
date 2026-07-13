/*
 * Entry: 00550103
 * Name: GetSessionDescName
 * Namespace: Global
 * Signature: char * GetSessionDescName(dp_s * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

char * __cdecl GetSessionDescName(dp_s *param_1)

{
  int iVar1;
  int iVar2;
  undefined4 local_6c;
  undefined1 local_68 [55];
  byte abStack_31 [41];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_6c = 0x5f;
  iVar1 = dpGetSessionDesc(param_1,local_68,&local_6c);
  iVar2 = 0;
  if (iVar1 == 0) {
    do {
      ca[iVar2] = abStack_31[iVar2] & 0x7f;
      iVar2 = iVar2 + 1;
    } while (iVar2 < 10);
  }
  else {
    ca[0] = '\0';
    ca[1] = '\0';
    ca[2] = '\0';
    ca[3] = '\0';
    ca[4] = '\0';
    ca[5] = '\0';
    ca[6] = '\0';
    ca[7] = '\0';
    ca[8] = '\0';
    ca[9] = '\0';
  }
  ca[10] = '\0';
  return ca;
}
