/*
 * Entry: 004e0e09
 * Name: NetPlayer_IsPlayerEnemy
 * Namespace: Global
 * Signature: int NetPlayer_IsPlayerEnemy(ushort param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl NetPlayer_IsPlayerEnemy(ushort param_1)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  Team *this;
  undefined2 in_stack_00000006;
  undefined4 local_1c;
  char local_18 [16];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_1c = 0x10;
  iVar2 = dpGetPlayerBlob(Net::dp,_param_1,local_18,&local_1c);
  if (iVar2 == 0) {
    uVar3 = (int)local_18[0] & 0xf;
    this = Team::GetTeam(Net::Team);
    bVar1 = Team::EnemyP(this,uVar3);
    uVar3 = (uint)bVar1;
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}
