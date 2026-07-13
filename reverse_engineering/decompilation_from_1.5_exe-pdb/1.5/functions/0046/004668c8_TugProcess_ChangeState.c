/*
 * Entry: 004668c8
 * Name: TugProcess::ChangeState
 * Namespace: TugProcess
 * Signature: void ChangeState(TugProcess * this, AiCommand param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TugProcess::ChangeState(TugProcess *this,AiCommand param_1)

{
  State SVar1;
  GameObject *this_00;
  int iVar2;
  
  SVar1 = this->nextState;
  if (SVar1 == GOTO) {
LAB_004668fc:
    (this->where).y = -1e+30;
  }
  else {
    if ((int)SVar1 < 3) {
      return;
    }
    if (4 < (int)SVar1) {
      if (SVar1 == DROPOFF) goto LAB_004668fc;
      if (SVar1 != RESCUE) {
        return;
      }
    }
    this_00 = GameObject::GetWho((GameObject *)this->craft);
    iVar2 = 0;
    if (this_00 != (GameObject *)0x0) {
      iVar2 = GameObject::GetHandle(this_00);
    }
    this->whoHandle = iVar2;
  }
  return;
}
