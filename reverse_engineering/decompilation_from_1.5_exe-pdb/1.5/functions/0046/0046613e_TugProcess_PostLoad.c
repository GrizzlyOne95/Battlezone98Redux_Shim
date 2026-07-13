/*
 * Entry: 0046613e
 * Name: TugProcess::PostLoad
 * Namespace: TugProcess
 * Signature: bool PostLoad(TugProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall TugProcess::PostLoad(TugProcess *this)

{
  bool bVar1;
  int iVar2;
  GameObject *pGVar3;
  _OBJ76 *p_Var4;
  
  iVar2 = ConvertHandle(this->whoHandle);
  this->whoHandle = iVar2;
  bVar1 = SObject::PostLoad((SObject *)this);
  if (this->curState == PICKUP) {
    pGVar3 = GameObjectHandle::GetObj(this->whoHandle);
    p_Var4 = (_OBJ76 *)(**(code **)(this->craft->_padding_ + 0x28))();
    this->hitchTug = p_Var4;
    if (pGVar3 == (GameObject *)0x0) {
      this->hitchCargo = (_OBJ76 *)0x0;
    }
    else {
      p_Var4 = (_OBJ76 *)(**(code **)(pGVar3->_padding_ + 0x28))();
      this->hitchCargo = p_Var4;
    }
  }
  return bVar1;
}
