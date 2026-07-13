/*
 * Entry: 00555e31
 * Name: PlayerList::Count
 * Namespace: PlayerList
 * Signature: int Count(PlayerList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall PlayerList::Count(PlayerList *this)

{
  return (int)(this->playerV)._Mylast - (int)(this->playerV)._Myfirst >> 2;
}
