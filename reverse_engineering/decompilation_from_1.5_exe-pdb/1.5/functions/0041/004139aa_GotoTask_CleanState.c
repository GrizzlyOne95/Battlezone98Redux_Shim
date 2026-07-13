/*
 * Entry: 004139aa
 * Name: GotoTask::CleanState
 * Namespace: GotoTask
 * Signature: void CleanState(GotoTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GotoTask::CleanState(GotoTask *this)

{
  int iVar1;
  
  if (this->_padding_ != 0xd) {
    iVar1 = *(int *)(this->_padding_ + 0x228);
    *(undefined4 *)(iVar1 + 0xcc) = 0;
    *(undefined4 *)(iVar1 + 0xd4) = 0;
    if (this->_padding_ == 2) {
      UnitTask::CleanGoto((UnitTask *)this);
      return;
    }
    if (this->_padding_ == 3) {
      UnitTask::CleanStuck((UnitTask *)this);
      return;
    }
  }
  return;
}
