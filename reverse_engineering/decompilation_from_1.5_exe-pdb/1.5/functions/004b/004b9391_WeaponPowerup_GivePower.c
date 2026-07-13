/*
 * Entry: 004b9391
 * Name: WeaponPowerup::GivePower
 * Namespace: WeaponPowerup
 * Signature: bool GivePower(WeaponPowerup * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall WeaponPowerup::GivePower(WeaponPowerup *this,GameObject *param_1)

{
  bool bVar1;
  _OBJ76 *p_Var2;
  GAS_CTRL *pGVar3;
  
  bVar1 = GiveWeapon(param_1,*(WeaponClass **)(*(int *)&this->field_0xec + 0x170));
  pGVar3 = (GAS_CTRL *)0x0;
  if (!bVar1) {
    DoAudioNew((char *)(*(int *)&this->field_0xec + 0x160),*(_OBJ76 **)&this->field_0xe8,
               (GAS_CTRL *)0x0);
  }
  else {
    p_Var2 = (_OBJ76 *)(**(code **)(param_1->_padding_ + 0x30))();
    DoAudioNew((char *)(*(int *)&this->field_0xec + 0x150),p_Var2,pGVar3);
    obj_set_flag(*(_OBJ76 **)&this->field_0xe8,0x200);
  }
  return bVar1;
}
