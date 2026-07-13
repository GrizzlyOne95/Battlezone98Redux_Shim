/*
 * Entry: 004de670
 * Name: Net::SendGameInfoData
 * Namespace: Net
 * Signature: void SendGameInfoData(dp_s * param_1, ushort param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl Net::SendGameInfoData(dp_s *param_1,ushort param_2)

{
  undefined2 in_stack_0000000a;
  int local_408;
  int local_404;
  int local_400;
  int local_3fc;
  undefined1 local_3f8;
  undefined1 local_3f7;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_408 = TimeLimit;
  local_404 = KillLimit;
  local_400 = FlagLimit;
  local_3fc = iStartLivesLeft;
  local_3f8 = bSniper;
  local_3f7 = bNations;
  dpSetPlayerData(param_1,_param_2,0xc,&local_408,0x14,0);
  return;
}
