/*
 * Entry: 004dd103
 * Name: dpEnumPlayersCallbackFlags
 * Namespace: Global
 * Signature: void dpEnumPlayersCallbackFlags(ushort param_1, char * param_2, long param_3, void * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl dpEnumPlayersCallbackFlags(ushort param_1,char *param_2,long param_3,void *param_4)

{
  NetPlayer *pNVar1;
  int iVar2;
  undefined2 in_stack_00000006;
  int local_10c;
  undefined1 local_108 [256];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  pNVar1 = NetPlayer::Find(param_1);
  if ((pNVar1 != (NetPlayer *)0x0) && (pNVar1->flagIndex == 0)) {
    local_10c = 0x100;
    iVar2 = dpGetPlayerData(Net::dp,_param_1,0xd,local_108,&local_10c,0);
    if ((iVar2 == 0) && (local_10c == 0x100)) {
      reload_flags = 1;
    }
  }
  return;
}
