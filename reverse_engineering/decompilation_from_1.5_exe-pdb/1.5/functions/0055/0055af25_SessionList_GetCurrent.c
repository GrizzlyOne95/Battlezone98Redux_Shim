/*
 * Entry: 0055af25
 * Name: SessionList::GetCurrent
 * Namespace: SessionList
 * Signature: dp_session_t * GetCurrent(SessionList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

dp_session_t * __thiscall SessionList::GetCurrent(SessionList *this)

{
  LRESULT LVar1;
  Session *pSVar2;
  
  LVar1 = SendMessageA((HWND)this->hList,0x188,0,0);
  this->l = LVar1;
  if (LVar1 == -1) {
    LVar1 = SendMessageA((HWND)this->hList,0x186,0,0);
    this->l = LVar1;
  }
  if (this->l != 0xffffffff) {
    LVar1 = SendMessageA((HWND)this->hList,0x199,this->l,0);
    this->l = LVar1;
    pSVar2 = FindSession(this,(short)LVar1);
    if (pSVar2 != (Session *)0x0) {
      return &pSVar2->dp_session;
    }
  }
  return (dp_session_t *)0x0;
}
