/*
 * Entry: 00457b89
 * Name: PersonProcess::CleanUState1
 * Namespace: PersonProcess
 * Signature: void CleanUState1(PersonProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PersonProcess::CleanUState1(PersonProcess *this)

{
  byte bVar1;
  GameObject *pGVar2;
  
  if (this->getIn != false) {
    this->getIn = false;
    pGVar2 = GameObjectHandle::GetObj(*(int *)(this->_padding_ + 0x18));
    if (pGVar2 != (GameObject *)0x0) {
      bVar1 = (**(code **)(*(int *)(this->_padding_ + 0x20) + 4))();
      pGVar2->locked = pGVar2->locked & ~(1 << (bVar1 & 0x1f));
    }
  }
  if ((undefined4 *)this->_padding_ != (undefined4 *)0x0) {
    (*(code *)**(undefined4 **)this->_padding_)(1);
  }
  this->_padding_ = 0;
  return;
}
