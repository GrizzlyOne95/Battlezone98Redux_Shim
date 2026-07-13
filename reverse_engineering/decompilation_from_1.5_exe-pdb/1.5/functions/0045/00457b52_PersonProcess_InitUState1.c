/*
 * Entry: 00457b52
 * Name: PersonProcess::InitUState1
 * Namespace: PersonProcess
 * Signature: void InitUState1(PersonProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PersonProcess::InitUState1(PersonProcess *this)

{
  GameObject *pGVar1;
  PersonRetreat *pPVar2;
  GameObject *unaff_ESI;
  
  pGVar1 = FindBase(unaff_ESI);
  this->base = pGVar1;
  pPVar2 = operator_new(0x150);
  if (pPVar2 == (PersonRetreat *)0x0) {
    pPVar2 = (PersonRetreat *)0x0;
  }
  else {
    pPVar2 = PersonRetreat::PersonRetreat(pPVar2,(Craft *)this->_padding_,this->base);
  }
  this->_padding_ = (int)pPVar2;
  this->getIn = false;
  return;
}
