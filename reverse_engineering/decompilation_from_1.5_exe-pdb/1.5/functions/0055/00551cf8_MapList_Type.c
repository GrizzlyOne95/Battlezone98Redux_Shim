/*
 * Entry: 00551cf8
 * Name: MapList::Type
 * Namespace: MapList
 * Signature: char Type(MapList * this, ulong param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char __thiscall MapList::Type(MapList *this,ulong param_1)

{
  char cVar1;
  
  if (param_1 < this->s) {
    cVar1 = (char)this[1].hPlayerList[param_1 * 5 + 4].unused;
  }
  else {
    cVar1 = '?';
  }
  return cVar1;
}
