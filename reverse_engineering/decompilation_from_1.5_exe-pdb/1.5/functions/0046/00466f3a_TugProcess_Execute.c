/*
 * Entry: 00466f3a
 * Name: TugProcess::Execute
 * Namespace: TugProcess
 * Signature: void Execute(TugProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TugProcess::Execute(TugProcess *this)

{
  bool bVar1;
  AiCommand AVar2;
  
  if (this->nextState != this->curState) {
    CleanState(this);
    this->curState = this->nextState;
    InitState(this);
  }
  bVar1 = ChangesState(this,this->craft->_padding_);
  if (bVar1) {
    CleanState(this);
    AVar2 = GameObject::GetWhat((GameObject *)this->craft);
    ChangeState(this,AVar2);
    this->curState = this->nextState;
    InitState(this);
  }
  DoState(this);
  return;
}
