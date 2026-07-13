/*
 * Entry: 0054fc4f
 * Name: NetLoop
 * Namespace: Global
 * Signature: void NetLoop(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl NetLoop(void)

{
  DWORD DVar1;
  int iVar2;
  DWORD DVar3;
  undefined1 local_140 [4];
  undefined4 local_13c;
  undefined1 local_138 [4];
  undefined1 local_134 [116];
  undefined1 local_c0 [184];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_c0;
  DVar1 = Get_TimeNow();
  while( true ) {
    DVar3 = Get_TimeNow();
    if (DVar1 + 3000 <= DVar3) {
      return;
    }
    iVar2 = dpReadyToFreeze(Net::dp);
    if (iVar2 != 6) break;
    local_13c = 300;
    iVar2 = dpReceive(Net::dp,local_138,local_140,0,local_134,&local_13c);
    if ((iVar2 != 0) && (iVar2 != 2)) {
      return;
    }
  }
  return;
}
