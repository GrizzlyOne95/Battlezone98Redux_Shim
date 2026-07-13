/*
 * Entry: 004674a3
 * Name: TurretTankProcess::CleanSubAttack
 * Namespace: TurretTankProcess
 * Signature: void CleanSubAttack(TurretTankProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TurretTankProcess::CleanSubAttack(TurretTankProcess *this)

{
  if ((undefined4 *)this->_padding_ != (undefined4 *)0x0) {
    (*(code *)**(undefined4 **)this->_padding_)(1);
  }
  this->_padding_ = 0;
  return;
}
