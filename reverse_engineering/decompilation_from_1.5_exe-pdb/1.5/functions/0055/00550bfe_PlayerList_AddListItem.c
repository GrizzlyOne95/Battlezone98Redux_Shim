/*
 * Entry: 00550bfe
 * Name: PlayerList::AddListItem
 * Namespace: PlayerList
 * Signature: void AddListItem(PlayerList * this, dp_playerId_t * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PlayerList::AddListItem(PlayerList *this,dp_playerId_t *param_1)

{
  WPARAM wParam;
  LRESULT LVar1;
  
  if ((HWND)this->hList != (HWND)0x0) {
    wParam = SendMessageA((HWND)this->hList,0x180,0,(LPARAM)param_1->name);
    this->l = wParam;
    if ((wParam != 0xffffffff) && (wParam != 0xfffffffe)) {
      LVar1 = SendMessageA((HWND)this->hList,0x19a,wParam,(uint)(param_1->field0_0x0).id);
      this->l = LVar1;
      Redraw(this);
    }
  }
  return;
}
