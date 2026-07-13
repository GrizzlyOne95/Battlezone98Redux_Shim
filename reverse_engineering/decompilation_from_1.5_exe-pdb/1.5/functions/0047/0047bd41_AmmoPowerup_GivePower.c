/*
 * Entry: 0047bd41
 * Name: AmmoPowerup::GivePower
 * Namespace: AmmoPowerup
 * Signature: bool GivePower(AmmoPowerup * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall AmmoPowerup::GivePower(AmmoPowerup *this,GameObject *param_1)

{
  int iVar1;
  bool bVar2;
  _OBJ76 *p_Var3;
  GAS_CTRL *pGVar4;
  
  if (((int)(param_1->curAmmo ^ 0x33333333U) < (int)(param_1->maxAmmo ^ 0x33333333U)) &&
     (param_1->carrier != (Carrier *)0x0)) {
    iVar1 = *(int *)&this->field_0xec;
    (**(code **)(param_1->_padding_ + 0x18))(*(undefined4 *)(iVar1 + 0x170));
    pGVar4 = (GAS_CTRL *)0x0;
    p_Var3 = (_OBJ76 *)(**(code **)(param_1->_padding_ + 0x30))();
    DoAudioNew((char *)(iVar1 + 0x150),p_Var3,pGVar4);
    obj_set_flag(*(_OBJ76 **)&this->field_0xe8,0x200);
    bVar2 = true;
  }
  else {
    DoAudioNew((char *)(*(int *)&this->field_0xec + 0x160),*(_OBJ76 **)&this->field_0xe8,
               (GAS_CTRL *)0x0);
    bVar2 = false;
  }
  return bVar2;
}
