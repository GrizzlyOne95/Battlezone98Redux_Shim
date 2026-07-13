/*
 * Entry: 00550582
 * Name: ServerList::ServerSelected
 * Namespace: ServerList
 * Signature: bool ServerSelected(ServerList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall ServerList::ServerSelected(ServerList *this)

{
  LRESULT LVar1;
  
  LVar1 = SendMessageA((HWND)this->hList,0x188,0,0);
  return LVar1 != -1;
}
