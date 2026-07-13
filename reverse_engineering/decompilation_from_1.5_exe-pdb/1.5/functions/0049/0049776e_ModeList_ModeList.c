/*
 * Entry: 0049776e
 * Name: ModeList::ModeList
 * Namespace: ModeList
 * Signature: ModeList * ModeList(ModeList * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ModeList * __thiscall ModeList::ModeList(ModeList *this)

{
  RemoveAllModes(this);
  this->activeSlot = -1;
  return this;
}
