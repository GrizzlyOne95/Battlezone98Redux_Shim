/*
 * Entry: 0054fd98
 * Name: GetSessionDescSync
 * Namespace: Global
 * Signature: bool GetSessionDescSync(dp_s * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

bool __cdecl GetSessionDescSync(dp_s *param_1)

{
  bool bVar1;
  int iVar2;
  undefined4 local_6c;
  undefined1 local_68 [55];
  byte local_31;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_6c = 0x5f;
  iVar2 = dpGetSessionDesc(param_1,local_68,&local_6c);
  if ((iVar2 == 0) && ((local_31 & 0x80) != 0)) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  return bVar1;
}
