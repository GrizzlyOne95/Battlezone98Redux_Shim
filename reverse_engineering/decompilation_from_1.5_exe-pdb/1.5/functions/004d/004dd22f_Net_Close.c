/*
 * Entry: 004dd22f
 * Name: Net::Close
 * Namespace: Net
 * Signature: void Close(bool param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl Net::Close(bool param_1)

{
  DWORD DVar1;
  int iVar2;
  DWORD DVar3;
  undefined1 local_140 [4];
  undefined1 local_13c [4];
  undefined4 local_138;
  undefined1 local_134 [116];
  undefined1 local_c0 [184];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_c0;
  dpClose(dp);
  DVar1 = Get_TimeNow();
  local_138 = 300;
  while( true ) {
    DVar3 = Get_TimeNow();
    if (DVar1 + 3000 <= DVar3) break;
    iVar2 = dpReadyToFreeze(dp);
    if (iVar2 != 6) break;
    local_138 = 300;
    dpReceive(dp,local_13c,local_140,0,local_134,&local_138);
  }
  if (param_1) {
    DVar1 = Get_TimeNow();
    while( true ) {
      DVar3 = Get_TimeNow();
      if (DVar1 + 3000 <= DVar3) break;
      local_138 = 300;
      dpReceive(dp,local_13c,local_140,0,local_134,&local_138);
    }
  }
  MessageHandler = (_func___cdecl_int_ushort_char_ptr_int *)0x0;
  dpidPrevHost = 0xfa01;
  dpidCurHost = 0xfa01;
  return;
}
