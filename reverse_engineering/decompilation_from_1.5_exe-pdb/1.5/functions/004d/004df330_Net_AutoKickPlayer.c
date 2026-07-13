/*
 * Entry: 004df330
 * Name: Net_AutoKickPlayer
 * Namespace: Global
 * Signature: void Net_AutoKickPlayer(ushort param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl Net_AutoKickPlayer(ushort param_1)

{
  undefined2 in_stack_00000006;
  undefined2 local_14;
  ushort local_12;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_14 = 0x4b41;
  Net::Send(Net::dp,Net::myPlayerID,param_1,1,&local_14,2);
  local_14 = 0x5341;
  local_12 = param_1;
  Net::Send(Net::dp,Net::myPlayerID,0,1,&local_14,4);
  if (Net::bRemovePlayerOnKick != 0) {
    dpDestroyPlayer(Net::dp,_param_1);
  }
  return;
}
