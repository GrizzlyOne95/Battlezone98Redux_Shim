/*
 * Entry: 00462ea5
 * Name: SoldierReturn::SoldierReturn
 * Namespace: SoldierReturn
 * Signature: SoldierReturn * SoldierReturn(SoldierReturn * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SoldierReturn * __thiscall SoldierReturn::SoldierReturn(SoldierReturn *this)

{
  GotoTask::GotoTask((GotoTask *)this);
  *(undefined ***)this = &_vftable_;
  return this;
}
