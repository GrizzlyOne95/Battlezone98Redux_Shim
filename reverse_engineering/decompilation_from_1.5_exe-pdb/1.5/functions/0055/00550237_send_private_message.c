/*
 * Entry: 00550237
 * Name: send_private_message
 * Namespace: Global
 * Signature: void send_private_message(dp_s * param_1, ushort param_2, ushort param_3, char * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl send_private_message(dp_s *param_1,ushort param_2,ushort param_3,char *param_4)

{
  char cVar1;
  char *pcVar2;
  dp_s *unaff_ESI;
  undefined2 in_stack_0000000e;
  undefined2 local_408;
  char local_406 [1022];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  pcVar2 = _param_3;
  do {
    cVar1 = *pcVar2;
    pcVar2[(int)(local_406 + -(int)_param_3)] = cVar1;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  local_408 = 0x5370;
  pcVar2 = _param_3 + 1;
  do {
    cVar1 = *_param_3;
    _param_3 = _param_3 + 1;
  } while (cVar1 != '\0');
  _param_3 = _param_3 + (3 - (int)pcVar2);
  if ((char *)0xf4 < _param_3) {
    _param_3 = (char *)0xf4;
  }
  Net::Send(unaff_ESI,(ushort)param_1,param_2,1,&local_408,(uint)_param_3);
  return;
}
