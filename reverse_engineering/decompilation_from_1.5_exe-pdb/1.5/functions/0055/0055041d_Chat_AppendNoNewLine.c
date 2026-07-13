/*
 * Entry: 0055041d
 * Name: Chat::AppendNoNewLine
 * Namespace: Chat
 * Signature: void AppendNoNewLine(Chat * this, ulong param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Type propagation algorithm not settling */

void __thiscall Chat::AppendNoNewLine(Chat *this,ulong param_1,char *param_2)

{
  WPARAM local_50;
  char *local_4c;
  WPARAM local_48 [6];
  ulong local_30;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_4c = param_2;
  SendMessageA((HWND)this->hOutput,0xb0,(WPARAM)&local_50,(LPARAM)local_48);
  SendMessageA((HWND)this->hOutput,0xb1,0xffffffff,-1);
  if (*(char *)&this[1].hOutput != '\0') {
    SendMessageA((HWND)this->hOutput,0xc2,0,0x5d2500);
    SendMessageA((HWND)this->hOutput,0xb1,0xffffffff,-1);
    *(undefined1 *)&this[1].hOutput = 0;
  }
  local_48[1] = 0x3c;
  memset(local_48 + 2,0,0x38);
  local_48[2] = 0x40000000;
  if (colors_on == 0) {
    local_30 = 0xff00;
  }
  else {
    local_30 = param_1;
  }
  SendMessageA((HWND)this->hOutput,0x444,1,(LPARAM)(local_48 + 1));
  SendMessageA((HWND)this->hOutput,0xc2,0,(LPARAM)local_4c);
  if (local_50 == local_48[0]) {
    local_48[0] = 0xffffffff;
    local_50 = 0xffffffff;
  }
  SendMessageA((HWND)this->hOutput,0xb1,local_50,local_48[0]);
  SendMessageA((HWND)this->hOutput,0xb7,0,0);
  return;
}
