/*
 * Entry: 0055080f
 * Name: SessionList::ModifyListItem
 * Namespace: SessionList
 * Signature: long ModifyListItem(SessionList * this, Session * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

long __thiscall SessionList::ModifyListItem(SessionList *this,Session *param_1)

{
  WPARAM wParam;
  WPARAM WVar1;
  LRESULT LVar2;
  bool bVar3;
  undefined1 local_6c [100];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  wParam = FindItemIndex(this,(param_1->dp_session).field4_0xf.karma);
  if (wParam != 0xffffffff) {
    WVar1 = SendMessageA((HWND)this->hList,0x188,0,0);
    bVar3 = wParam == WVar1;
    LVar2 = SendMessageA((HWND)this->hList,0x182,wParam,0);
    this->l = LVar2;
    (**(code **)(this->_padding_ + 8))(local_6c,param_1);
    WVar1 = SendMessageA((HWND)this->hList,0x180,0,(LPARAM)local_6c);
    wParam = 0xffffffff;
    if ((WVar1 != 0xffffffff) && (WVar1 != 0xfffffffe)) {
      wParam = WVar1;
      if (bVar3) {
        wParam = SendMessageA((HWND)this->hList,0x186,WVar1,0);
      }
      LVar2 = SendMessageA((HWND)this->hList,0x19a,wParam,
                           (int)(param_1->dp_session).field4_0xf.karma);
      this->l = LVar2;
    }
  }
  return wParam;
}
