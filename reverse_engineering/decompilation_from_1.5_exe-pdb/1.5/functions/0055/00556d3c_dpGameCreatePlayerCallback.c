/*
 * Entry: 00556d3c
 * Name: dpGameCreatePlayerCallback
 * Namespace: Global
 * Signature: void dpGameCreatePlayerCallback(ushort param_1, char * param_2, long param_3, void * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl dpGameCreatePlayerCallback(ushort param_1,char *param_2,long param_3,void *param_4)

{
  Chat *this;
  Chat *this_00;
  char local_108 [128];
  undefined1 local_88 [128];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_88;
  if (param_1 == 0xfa01) {
    builtin_strncpy(local_108," Failed",8);
    bCreatePlayerFailed = true;
    memset(local_108 + 8,0,0xf8);
    read_text_label("multi_message","fail",local_108);
    Chat::Append(this_00,(char *)&chatGame);
  }
  else {
    builtin_strncpy(local_108," Success",9);
    Net::myPlayerID = param_1;
    bSetPlayerBlob = true;
    memset(local_108 + 9,0,0xf7);
    read_text_label("multi_message","success",local_108);
    Chat::Append(this,(char *)&chatGame);
  }
  bCreatingPlayer = false;
  return;
}
