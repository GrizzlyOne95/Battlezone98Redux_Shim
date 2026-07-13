/*
 * Entry: 0044dcb7
 * Name: OffensiveProcess::CleanSubAttack
 * Namespace: OffensiveProcess
 * Signature: void CleanSubAttack(OffensiveProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall OffensiveProcess::CleanSubAttack(OffensiveProcess *this)

{
  if ((undefined4 *)this->_padding_ != (undefined4 *)0x0) {
    (*(code *)**(undefined4 **)this->_padding_)(1);
  }
  this->_padding_ = 0;
  return;
}
