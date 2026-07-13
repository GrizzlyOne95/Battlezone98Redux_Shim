/*
 * Entry: 004e3986
 * Name: KillMessage
 * Namespace: Global
 * Signature: void KillMessage(int param_1, int param_2, char param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl KillMessage(int param_1,int param_2,char param_3,int param_4)

{
  ushort uVar1;
  ushort uVar2;
  int iVar3;
  undefined2 *puVar4;
  uint uVar5;
  undefined2 local_108;
  char local_106;
  char local_105;
  char local_104;
  char local_103;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_108 = 0x4b4d;
  local_105 = (char)param_2;
  local_106 = (char)param_1;
  local_104 = param_3;
  local_103 = (char)param_4;
  RKillMessage((int)(char)param_1,(int)(char)param_2,param_3,(int)(char)param_4);
  uVar5 = 6;
  puVar4 = &local_108;
  iVar3 = 1;
  uVar2 = 0;
  uVar1 = Net_GetMyPlayerID();
  Net::Send(Net::dp,uVar1,uVar2,iVar3,puVar4,uVar5);
  return;
}
