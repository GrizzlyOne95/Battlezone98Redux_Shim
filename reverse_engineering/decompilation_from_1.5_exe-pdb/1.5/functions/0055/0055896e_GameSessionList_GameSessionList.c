/*
 * Entry: 0055896e
 * Name: GameSessionList::GameSessionList
 * Namespace: GameSessionList
 * Signature: GameSessionList * GameSessionList(GameSessionList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameSessionList * __thiscall GameSessionList::GameSessionList(GameSessionList *this)

{
  SessionList::SessionList((SessionList *)this);
  *(undefined ***)this = &_vftable_;
  return this;
}
