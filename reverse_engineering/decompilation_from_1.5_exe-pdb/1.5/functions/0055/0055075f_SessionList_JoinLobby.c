/*
 * Entry: 0055075f
 * Name: SessionList::JoinLobby
 * Namespace: SessionList
 * Signature: void JoinLobby(SessionList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SessionList::JoinLobby(SessionList *this)

{
  this->countWait = (&defaultFontSize3)[nTransportMode];
  chat_state = 0;
  this->dp_karma_selected = 0;
  this->dp_karma_found = 0;
  this->optFoundNumber = 0x7fff;
  this->bWaitSes = false;
  return;
}
