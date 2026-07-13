/*
 * Entry: 005503a3
 * Name: Chat::Init
 * Namespace: Chat
 * Signature: void Init(Chat * this, HWND__ * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall Chat::Init(Chat *this,HWND__ *param_1)

{
  undefined4 local_44;
  undefined4 local_40 [4];
  undefined4 local_30;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  this->hOutput = param_1;
  *(undefined1 *)&this[1].hOutput = 0;
  SetNetworkFont(param_1);
  SendMessageA((HWND)this->hOutput,0x443,0,0);
  local_44 = 0x3c;
  memset(local_40,0,0x38);
  local_40[0] = 0x40000000;
  local_30 = 0xff00;
  SendMessageA((HWND)this->hOutput,0x444,0,(LPARAM)&local_44);
  return;
}
