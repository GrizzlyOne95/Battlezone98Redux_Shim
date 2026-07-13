/*
 * Entry: 0055cfa0
 * Name: SyncGamePlayerList::Timer
 * Namespace: SyncGamePlayerList
 * Signature: void Timer(SyncGamePlayerList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SyncGamePlayerList::Timer(SyncGamePlayerList *this)

{
  PlayerList::Timer((PlayerList *)this);
  if ((char)this->_padding_ == '\0') {
    PlayerList::StartEnum((PlayerList *)this);
    dp_result = dpEnumPlayersEx(this->_padding_,&dp_session_game,dpEnumGamePlayersCallback,0,0);
    if (dp_result != 0) {
      PlayerList::EndEnum((PlayerList *)this);
      return;
    }
  }
  return;
}
