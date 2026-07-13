/*
 * Entry: 0045a39e
 * Name: RecycleTask::DoGotoRecycler
 * Namespace: RecycleTask
 * Signature: void DoGotoRecycler(RecycleTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RecycleTask::DoGotoRecycler(RecycleTask *this)

{
  char cVar1;
  GameObject *pGVar2;
  
  pGVar2 = GameObjectHandle::GetObj(this->dropHandle);
  if (pGVar2 == (GameObject *)0x0) {
    this->nextState = 3;
    return;
  }
  cVar1 = (**(code **)(this->subtask->_padding_ + 0x18))();
  if (cVar1 != '\0') {
    this->nextState = 4;
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x0045a3d2. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(this->subtask->_padding_ + 0x1c))();
  return;
}
