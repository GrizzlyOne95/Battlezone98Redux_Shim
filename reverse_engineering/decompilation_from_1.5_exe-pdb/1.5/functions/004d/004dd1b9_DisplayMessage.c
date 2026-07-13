/*
 * Entry: 004dd1b9
 * Name: DisplayMessage
 * Namespace: Global
 * Signature: void DisplayMessage(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl DisplayMessage(char *param_1)

{
  char cVar1;
  char *pcVar2;
  char local_408 [1024];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  _vsnprintf(local_408,0x400,param_1,&stack0x00000008);
  pcVar2 = local_408;
  if (Net::CHAT_PACKET_ID_CALLBACK == (_func___cdecl_void_ushort_char_ptr_char_ptr_uint *)0x0) {
    Chat_DisplayMessage(0,pcVar2);
  }
  else {
    do {
      cVar1 = *pcVar2;
      pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
    (*Net::CHAT_PACKET_ID_CALLBACK)(0,(char *)0x0,local_408,(int)pcVar2 - (int)(local_408 + 1));
  }
  return;
}
