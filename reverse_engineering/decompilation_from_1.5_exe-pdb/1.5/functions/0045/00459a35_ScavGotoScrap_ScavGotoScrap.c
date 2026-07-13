/*
 * Entry: 00459a35
 * Name: ScavGotoScrap::ScavGotoScrap
 * Namespace: ScavGotoScrap
 * Signature: ScavGotoScrap * ScavGotoScrap(ScavGotoScrap * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ScavGotoScrap * __thiscall ScavGotoScrap::ScavGotoScrap(ScavGotoScrap *this)

{
  GotoTask::GotoTask((GotoTask *)this);
  *(undefined ***)this = &_vftable_;
  return this;
}
