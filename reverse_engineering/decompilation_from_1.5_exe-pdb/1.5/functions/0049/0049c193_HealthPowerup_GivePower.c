/*
 * Entry: 0049c193
 * Name: HealthPowerup::GivePower
 * Namespace: HealthPowerup
 * Signature: bool GivePower(HealthPowerup * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall HealthPowerup::GivePower(HealthPowerup *this,GameObject *param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  _OBJ76 *p_Var4;
  GAS_CTRL *pGVar5;
  
  fVar1 = param_1->maxHealth;
  fVar2 = param_1->curHealth;
  if (fVar1 <= fVar2) {
    DoAudioNew((char *)(*(int *)&this->field_0xec + 0x160),*(_OBJ76 **)&this->field_0xe8,
               (GAS_CTRL *)0x0);
  }
  else {
    iVar3 = *(int *)&this->field_0xec;
    (**(code **)(param_1->_padding_ + 0x28))((float)*(int *)(iVar3 + 0x170));
    pGVar5 = (GAS_CTRL *)0x0;
    p_Var4 = (_OBJ76 *)(**(code **)(param_1->_padding_ + 0x30))();
    DoAudioNew((char *)(iVar3 + 0x150),p_Var4,pGVar5);
    obj_set_flag(*(_OBJ76 **)&this->field_0xe8,0x200);
  }
  return fVar2 < fVar1;
}
