/*
 * Entry: 0054ff1a
 * Name: SetSessionDescBarracks
 * Namespace: Global
 * Signature: void SetSessionDescBarracks(dp_s * param_1, bool param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl SetSessionDescBarracks(dp_s *param_1,bool param_2)

{
  undefined4 local_6c;
  undefined1 local_68 [58];
  byte local_2e;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_6c = 0x5f;
  dpGetSessionDesc(param_1,local_68,&local_6c);
  if (param_2) {
    local_2e = local_2e | 0x80;
  }
  else {
    local_2e = local_2e & 0x7f;
  }
  dpSetSessionDesc(param_1,local_68,0);
  return;
}
