/*
 * Entry: 004de989
 * Name: dpEnumPlayersCallback
 * Namespace: Global
 * Signature: void dpEnumPlayersCallback(ushort param_1, char * param_2, long param_3, void * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl dpEnumPlayersCallback(ushort param_1,char *param_2,long param_3,void *param_4)

{
  char cVar1;
  int iVar2;
  undefined2 in_stack_00000006;
  int local_1c;
  char local_18 [16];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  if (param_1 == 0xfa01) {
    *(undefined4 *)param_4 = 4;
  }
  else {
    local_1c = 0x10;
    iVar2 = dpGetPlayerBlob(Net::dp,_param_1,local_18,&local_1c);
    if ((iVar2 == 0) && (local_1c != 0)) {
      NetPlayer::AddPlayer(param_1,param_2,(int)local_18[0] & 0xf);
      if ((param_3 & 1U) != 0) {
        Net::SetMyPlayerId(param_4,param_1);
        iVar2 = (int)Net::player_name - (int)param_2;
        do {
          cVar1 = *param_2;
          param_2[iVar2] = cVar1;
          param_2 = param_2 + 1;
          Net::Team = (int)local_18[0];
        } while (cVar1 != '\0');
      }
    }
  }
  return;
}
