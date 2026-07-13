/*
 * Entry: 00550508
 * Name: Chat::Clear
 * Namespace: Chat
 * Signature: void Clear(Chat * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Chat::Clear(Chat *this)

{
  *(undefined1 *)&this[1].hOutput = 0;
  SetWindowTextA((HWND)this->hOutput,(LPCSTR)0x0);
  SendMessageA((HWND)this->hOutput,0xb1,0xffffffff,-1);
  SendMessageA((HWND)this->hOutput,0xb7,0,0);
  return;
}
