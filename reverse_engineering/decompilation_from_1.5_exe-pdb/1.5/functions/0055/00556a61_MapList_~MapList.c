/*
 * Entry: 00556a61
 * Name: MapList::~MapList
 * Namespace: MapList
 * Signature: void ~MapList(MapList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall MapList::~MapList(MapList *this)

{
  StopAnim(this);
  Init(this);
  return;
}
