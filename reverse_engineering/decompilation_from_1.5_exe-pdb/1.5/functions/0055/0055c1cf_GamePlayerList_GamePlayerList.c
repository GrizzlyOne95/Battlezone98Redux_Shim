/*
 * Entry: 0055c1cf
 * Name: GamePlayerList::GamePlayerList
 * Namespace: GamePlayerList
 * Signature: GamePlayerList * GamePlayerList(GamePlayerList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GamePlayerList * __thiscall GamePlayerList::GamePlayerList(GamePlayerList *this)

{
  PlayerList::PlayerList((PlayerList *)this);
  *(undefined ***)this = &_vftable_;
  return this;
}
