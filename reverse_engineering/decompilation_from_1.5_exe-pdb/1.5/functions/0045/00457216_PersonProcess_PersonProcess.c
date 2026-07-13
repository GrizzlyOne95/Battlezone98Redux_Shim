/*
 * Entry: 00457216
 * Name: PersonProcess::PersonProcess
 * Namespace: PersonProcess
 * Signature: PersonProcess * PersonProcess(PersonProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PersonProcess * __thiscall PersonProcess::PersonProcess(PersonProcess *this)

{
  OffensiveProcess::OffensiveProcess((OffensiveProcess *)this);
  this->base = (GameObject *)0x0;
  this->_padding_ = (int)&_vftable_;
  this->_padding_ = 3;
  this->getIn = false;
  return this;
}
