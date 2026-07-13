/*
 * Entry: 00457267
 * Name: PersonProcess::CleanSubAttack
 * Namespace: PersonProcess
 * Signature: void CleanSubAttack(PersonProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PersonProcess::CleanSubAttack(PersonProcess *this)

{
  if ((undefined4 *)this->_padding_ != (undefined4 *)0x0) {
    (*(code *)**(undefined4 **)this->_padding_)(1);
  }
  this->_padding_ = 0;
  return;
}
