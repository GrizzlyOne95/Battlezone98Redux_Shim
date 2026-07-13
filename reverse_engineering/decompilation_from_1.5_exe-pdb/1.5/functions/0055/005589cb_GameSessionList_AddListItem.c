/*
 * Entry: 005589cb
 * Name: GameSessionList::AddListItem
 * Namespace: GameSessionList
 * Signature: long AddListItem(GameSessionList * this, Session * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

long __thiscall GameSessionList::AddListItem(GameSessionList *this,Session *param_1)

{
  WPARAM wParam;
  LRESULT LVar1;
  undefined1 local_6c [100];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  (**(code **)(*(int *)this + 8))(local_6c,param_1);
  wParam = SendMessageA(*(HWND *)&this->field_0x10,0x180,0,(LPARAM)local_6c);
  if ((wParam == 0xffffffff) || (wParam == 0xfffffffe)) {
    wParam = 0xffffffff;
  }
  else {
    LVar1 = SendMessageA(*(HWND *)&this->field_0x10,0x19a,wParam,
                         (int)(param_1->dp_session).field4_0xf.karma);
    *(LRESULT *)&this->field_0x2c = LVar1;
  }
  return wParam;
}
