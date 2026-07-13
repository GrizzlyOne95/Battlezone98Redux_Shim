/*
 * Entry: 00550746
 * Name: SessionList::WaitLobby
 * Namespace: SessionList
 * Signature: void WaitLobby(SessionList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SessionList::WaitLobby(SessionList *this)

{
  this->countWait = 1;
  this->dp_karma_found = 0;
  this->optFoundNumber = 0x7fff;
  this->bWaitSes = true;
  return;
}
