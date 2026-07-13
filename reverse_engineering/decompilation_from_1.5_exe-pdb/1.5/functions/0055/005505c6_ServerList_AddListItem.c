/*
 * Entry: 005505c6
 * Name: ServerList::AddListItem
 * Namespace: ServerList
 * Signature: void AddListItem(ServerList * this, Server * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall ServerList::AddListItem(ServerList *this,Server *param_1)

{
  WPARAM wParam;
  LRESULT LVar1;
  undefined1 local_6c [100];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  (**(code **)(this->_padding_ + 8))(local_6c,param_1);
  wParam = SendMessageA((HWND)this->hList,0x180,0,(LPARAM)local_6c);
  this->l = wParam;
  if ((wParam != 0xffffffff) && (wParam != 0xfffffffe)) {
    LVar1 = SendMessageA((HWND)this->hList,0x19a,wParam,0);
    this->l = LVar1;
    if (LVar1 == -1) {
      SendMessageA((HWND)this->hList,0x182,0xffffffff,0);
    }
    else {
      Redraw(this);
    }
  }
  return;
}
