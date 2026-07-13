/*
 * Entry: 00469c65
 * Name: UnitProcess::DoStage
 * Namespace: UnitProcess
 * Signature: void DoStage(UnitProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitProcess::DoStage(UnitProcess *this)

{
  GameObject *pGVar1;
  float fVar2;
  
  fVar2 = Get_Time();
  if ((float)this->me->_padding_ <= fVar2) {
    if (this->release != false) {
      AiPath::Release(this->where);
    }
    if (this->me->_padding_ == CMD_GO) {
      GameObject::ClearCommand((GameObject *)this->me);
    }
    this->nextState = WAIT;
    pGVar1 = GameObjectHandle::GetObj(this->whoHandle);
    if (pGVar1 != (GameObject *)0x0) {
      GameObject::SetCommand((GameObject *)this->me,CMD_ATTACK,pGVar1);
    }
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x00469cc4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(this->task->_padding_ + 0x1c))();
  return;
}
