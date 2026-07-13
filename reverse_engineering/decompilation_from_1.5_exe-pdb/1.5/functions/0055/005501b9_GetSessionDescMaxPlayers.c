/*
 * Entry: 005501b9
 * Name: GetSessionDescMaxPlayers
 * Namespace: Global
 * Signature: int GetSessionDescMaxPlayers(dp_s * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl GetSessionDescMaxPlayers(dp_s *param_1)

{
  int iVar1;
  undefined4 local_6c;
  undefined1 local_68 [17];
  short local_57;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_6c = 0x5f;
  iVar1 = dpGetSessionDesc(param_1,local_68,&local_6c);
  if (iVar1 == 0) {
    iVar1 = (int)local_57;
  }
  else {
    iVar1 = 2;
  }
  return iVar1;
}
