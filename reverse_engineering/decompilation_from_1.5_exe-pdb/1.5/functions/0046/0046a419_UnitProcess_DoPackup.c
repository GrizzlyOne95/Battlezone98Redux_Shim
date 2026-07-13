/*
 * Entry: 0046a419
 * Name: UnitProcess::DoPackup
 * Namespace: UnitProcess
 * Signature: void DoPackup(UnitProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitProcess::DoPackup(UnitProcess *this)

{
  int iVar1;
  char cVar2;
  
  cVar2 = (**(code **)(this->me->_padding_ + 0x68))();
  if ((cVar2 != '\0') && (this->me->_padding_ == CMD_PICKUP)) {
    GameObject::ClearCommand((GameObject *)this->me);
  }
  iVar1 = this->me->_padding_;
  (**(code **)(this->me->_padding_ + 0x88))
            (*(undefined4 *)(iVar1 + 0x38),*(undefined4 *)(iVar1 + 0x40));
  (**(code **)(this->me->_padding_ + 0x84))(0);
  return;
}
