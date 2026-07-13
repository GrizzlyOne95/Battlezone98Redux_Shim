/*
 * Entry: 0055af81
 * Name: SessionList::Banned
 * Namespace: SessionList
 * Signature: void Banned(SessionList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SessionList::Banned(SessionList *this)

{
  WPARAM wParam;
  LRESULT LVar1;
  Session *pSVar2;
  
  wParam = SendMessageA((HWND)this->hList,0x188,0,0);
  this->l = wParam;
  if (wParam != 0xffffffff) {
    LVar1 = SendMessageA((HWND)this->hList,0x199,wParam,0);
    this->l = LVar1;
    pSVar2 = FindSession(this,(short)LVar1);
    if (pSVar2 != (Session *)0x0) {
      pSVar2->bBanned = true;
    }
  }
  return;
}
