/*
 * Entry: 0045dc37
 * Name: ScavengerProcess::Execute
 * Namespace: ScavengerProcess
 * Signature: void Execute(ScavengerProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ScavengerProcess::Execute(ScavengerProcess *this)

{
  bool bVar1;
  
  Verify_Or_Request_Escorts(this);
  if (this->nextState != NO_STATE) {
    CleanState(this);
    this->curState = this->nextState;
    this->nextState = NO_STATE;
    InitState(this);
  }
  bVar1 = ChangesState(this,this->craft->_padding_);
  if (bVar1) {
    CleanState(this);
    GameObject::GetWhat((GameObject *)this->craft);
    ChangeState(this);
    this->curState = this->nextState;
    this->nextState = NO_STATE;
    InitState(this);
    if (this->nextState != NO_STATE) {
      return;
    }
  }
  DoState(this);
  return;
}
