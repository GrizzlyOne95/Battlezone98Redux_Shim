/*
 * Entry: 004c3e88
 * Name: ModeList::IsActive
 * Namespace: ModeList
 * Signature: bool IsActive(ModeList * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall ModeList::IsActive(ModeList *this,int param_1)

{
  return param_1 == this->activeSlot;
}
