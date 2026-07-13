/*
 * Entry: 004e08c2
 * Name: Net_BroadCastMessage
 * Namespace: Global
 * Signature: void Net_BroadCastMessage(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl Net_BroadCastMessage(char *param_1)

{
  char cVar1;
  char *pcVar2;
  char local_114 [268];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_114[0] = 'P';
  local_114[1] = 'C';
  _vsnprintf(local_114 + 2,0x10a,param_1,&stack0x00000008);
  pcVar2 = local_114 + 2;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  Net_BroadCast(local_114,(int)(pcVar2 + (3 - (int)(local_114 + 3))));
  return;
}
