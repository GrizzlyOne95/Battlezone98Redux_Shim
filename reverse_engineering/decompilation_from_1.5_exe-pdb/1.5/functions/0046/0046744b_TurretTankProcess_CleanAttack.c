/*
 * Entry: 0046744b
 * Name: TurretTankProcess::CleanAttack
 * Namespace: TurretTankProcess
 * Signature: void CleanAttack(TurretTankProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TurretTankProcess::CleanAttack(TurretTankProcess *this)

{
  if ((undefined4 *)this->_padding_ != (undefined4 *)0x0) {
    (*(code *)**(undefined4 **)this->_padding_)(1);
  }
  this->_padding_ = 0;
  return;
}
