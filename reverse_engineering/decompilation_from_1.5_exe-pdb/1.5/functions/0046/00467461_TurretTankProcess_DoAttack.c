/*
 * Entry: 00467461
 * Name: TurretTankProcess::DoAttack
 * Namespace: TurretTankProcess
 * Signature: void DoAttack(TurretTankProcess * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TurretTankProcess::DoAttack(TurretTankProcess *this)

{
  char cVar1;
  
  cVar1 = (**(code **)(*(int *)this->_padding_ + 0x18))();
  if (cVar1 != '\0') {
    Say((Craft *)this->_padding_,KILLED_MSG,this->_padding_);
    if ((((GameObject *)this->_padding_)->curCmd).what == CMD_ATTACK) {
      GameObject::ClearCommand((GameObject *)this->_padding_);
    }
    this->_padding_ = 3;
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x004674a0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)this->_padding_ + 0x1c))();
  return;
}
