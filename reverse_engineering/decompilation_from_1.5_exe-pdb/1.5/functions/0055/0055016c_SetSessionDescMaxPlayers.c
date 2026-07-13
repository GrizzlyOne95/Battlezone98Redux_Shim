/*
 * Entry: 0055016c
 * Name: SetSessionDescMaxPlayers
 * Namespace: Global
 * Signature: void SetSessionDescMaxPlayers(dp_s * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl SetSessionDescMaxPlayers(dp_s *param_1,int param_2)

{
  undefined4 local_6c;
  undefined1 local_68 [17];
  undefined2 local_57;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_6c = 0x5f;
  dpGetSessionDesc(param_1,local_68,&local_6c);
  local_57 = (undefined2)param_2;
  dpSetSessionDesc(param_1,local_68,0);
  return;
}
