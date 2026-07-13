/*
 * Entry: 004690fc
 * Name: UnitProcess::DoPatrol
 * Namespace: UnitProcess
 * Signature: void DoPatrol(UnitProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitProcess::DoPatrol(UnitProcess *this)

{
  char cVar1;
  int iVar2;
  
  cVar1 = (**(code **)(this->task->_padding_ + 0x18))();
  if ((cVar1 != '\0') && ((PatrolTask *)this->task != (PatrolTask *)0x0)) {
    iVar2 = PatrolTask::Patrol_New_Spot((PatrolTask *)this->task);
    if (iVar2 == 0) {
      if (this->release != false) {
        AiPath::Release(this->where);
      }
      if (this->me->_padding_ == CMD_GO) {
        GameObject::ClearCommand((GameObject *)this->me);
      }
      this->nextState = WAIT;
      return;
    }
  }
                    /* WARNING: Could not recover jumptable at 0x00469149. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(this->task->_padding_ + 0x1c))();
  return;
}
