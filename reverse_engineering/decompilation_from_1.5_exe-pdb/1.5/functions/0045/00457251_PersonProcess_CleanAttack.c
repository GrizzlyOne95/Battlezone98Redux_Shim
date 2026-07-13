/*
 * Entry: 00457251
 * Name: PersonProcess::CleanAttack
 * Namespace: PersonProcess
 * Signature: void CleanAttack(PersonProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PersonProcess::CleanAttack(PersonProcess *this)

{
  if ((undefined4 *)this->_padding_ != (undefined4 *)0x0) {
    (*(code *)**(undefined4 **)this->_padding_)(1);
  }
  this->_padding_ = 0;
  return;
}
