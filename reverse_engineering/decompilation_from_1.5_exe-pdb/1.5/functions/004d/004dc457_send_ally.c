/*
 * Entry: 004dc457
 * Name: send_ally
 * Namespace: Global
 * Signature: void send_ally(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl send_ally(int param_1,int param_2)

{
  ushort uVar1;
  dp_s *pdVar2;
  ushort uVar3;
  int iVar4;
  undefined2 *puVar5;
  uint uVar6;
  undefined2 local_6c;
  int local_6a;
  int local_66;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_6a = GameObject_GetUserTeam();
  local_66 = param_1;
  local_6c = 0x616c;
  if (param_2 == 0) {
    local_6c = 0x756c;
  }
  uVar6 = 10;
  puVar5 = &local_6c;
  iVar4 = 1;
  uVar3 = 0;
  uVar1 = Net_GetMyPlayerID();
  pdVar2 = Net_GetDP();
  Net_Send(pdVar2,uVar1,uVar3,iVar4,puVar5,uVar6);
  return;
}
