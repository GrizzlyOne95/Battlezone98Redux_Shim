/*
 * Entry: 0054fdde
 * Name: SetSessionDescStart
 * Namespace: Global
 * Signature: void SetSessionDescStart(dp_s * param_1, bool param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl SetSessionDescStart(dp_s *param_1,bool param_2)

{
  undefined4 local_6c;
  undefined1 local_68 [56];
  byte local_30;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_6c = 0x5f;
  dpGetSessionDesc(param_1,local_68,&local_6c);
  if (param_2) {
    local_30 = local_30 | 0x80;
  }
  else {
    local_30 = local_30 & 0x7f;
  }
  dpSetSessionDesc(param_1,local_68,0);
  return;
}
