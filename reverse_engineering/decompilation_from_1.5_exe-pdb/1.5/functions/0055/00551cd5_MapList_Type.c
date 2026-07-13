/*
 * Entry: 00551cd5
 * Name: MapList::Type
 * Namespace: MapList
 * Signature: char Type(MapList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char __thiscall MapList::Type(MapList *this)

{
  int iVar1;
  
  iVar1 = this->count;
  if ((-1 < iVar1) && (iVar1 < (int)this->s)) {
    return (char)this[1].hPlayerList[iVar1 * 5 + 4].unused;
  }
  return 'D';
}
