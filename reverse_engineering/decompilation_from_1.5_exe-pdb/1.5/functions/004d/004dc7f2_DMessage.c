/*
 * Entry: 004dc7f2
 * Name: DMessage
 * Namespace: Global
 * Signature: void DMessage(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl DMessage(char *param_1)

{
  ushort uVar1;
  char *pcVar2;
  char local_408 [1024];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  _vsnprintf(local_408,0x400,param_1,&stack0x00000008);
  pcVar2 = local_408;
  uVar1 = Net_GetMyPlayerID();
  Chat_DisplayMessage(uVar1,pcVar2);
  return;
}
