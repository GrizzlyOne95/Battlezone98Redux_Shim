/*
 * Entry: 0055ce99
 * Name: SessionList::CreateRoom
 * Namespace: SessionList
 * Signature: void CreateRoom(SessionList * this, dp_session_t * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SessionList::CreateRoom(SessionList *this,dp_session_t *param_1)

{
  WPARAM wParam;
  
  wParam = AddModify(this,param_1);
  SendMessageA((HWND)this->hList,0x186,wParam,0);
  this->dp_karma_selected = (short)param_1->field4_0xf;
  Chat::Clear((Chat *)&chatRoom);
  return;
}
