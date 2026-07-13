/*
 * Entry: 005501fd
 * Name: GetSessionDescCRC
 * Namespace: Global
 * Signature: ulong GetSessionDescCRC(dp_s * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

ulong __cdecl GetSessionDescCRC(dp_s *param_1)

{
  undefined4 local_6c;
  undefined1 local_68 [79];
  ulong local_19;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_6c = 0x5f;
  dpGetSessionDesc(param_1,local_68,&local_6c);
  return local_19;
}
