/*
 * Entry: 004ddade
 * Name: Net::Send
 * Namespace: Net
 * Signature: int Send(dp_s * param_1, ushort param_2, ushort param_3, int param_4, void * param_5, uint param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
Net::Send(dp_s *param_1,ushort param_2,ushort param_3,int param_4,void *param_5,uint param_6)

{
  int iVar1;
  undefined2 in_stack_0000000a;
  undefined2 in_stack_0000000e;
  dp_s *local_18;
  ushort local_14;
  undefined4 local_10;
  void *local_c;
  uint local_8;
  
  if ((param_2 == 0xfa01) || (param_3 == 0xfa01)) {
    iVar1 = 8;
  }
  else {
    if ((param_3 == 0) && (param_4 == 1)) {
      local_10 = 1;
      local_c = param_5;
      local_8 = param_6;
      broadcastFull = false;
      local_18 = param_1;
      local_14 = param_2;
      iVar1 = dpEnumPlayers(param_1,0,dpEnumPlayersCallbackSend,&local_18,0);
    }
    else {
      iVar1 = dpSend(param_1,_param_2,_param_3,param_4,param_5,param_6);
    }
    if (iVar1 == 3) {
      dwBandwidth = dwMinBandwidth;
      return 3;
    }
  }
  return iVar1;
}
