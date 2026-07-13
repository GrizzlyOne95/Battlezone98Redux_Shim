/*
 * Entry: 00457c6b
 * Name: PersonProcess::InitAttack
 * Namespace: PersonProcess
 * Signature: void InitAttack(PersonProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PersonProcess::InitAttack(PersonProcess *this)

{
  GameObject *pGVar1;
  PersonAttack *pPVar2;
  
  pGVar1 = GameObjectHandle::GetObj(this->_padding_);
  pPVar2 = operator_new(0x138);
  if (pPVar2 == (PersonAttack *)0x0) {
    pPVar2 = (PersonAttack *)0x0;
  }
  else {
    pPVar2 = PersonAttack::PersonAttack(pPVar2,(Craft *)this->_padding_,pGVar1);
  }
  this->_padding_ = (int)pPVar2;
  return;
}
