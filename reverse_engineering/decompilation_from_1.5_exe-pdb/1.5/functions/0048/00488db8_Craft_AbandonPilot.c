/*
 * Entry: 00488db8
 * Name: Craft::AbandonPilot
 * Namespace: Craft
 * Signature: void AbandonPilot(Craft * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Craft::AbandonPilot(Craft *this)

{
  float fVar1;
  undefined4 *puVar2;
  Craft *this_00;
  _OBJ76 *p_Var3;
  int iVar4;
  VHCL_CONTROL *pVVar5;
  GAS_CTRL *pGVar6;
  VECTOR_3D local_14;
  GameObjectClass *local_8;
  
  local_8 = (GameObjectClass *)this->_padding_;
  if ((local_8 != (GameObjectClass *)0x0) && (*(int *)(this->_padding_ + 0xac) != 4)) {
    this->_padding_ = 0;
    puVar2 = (undefined4 *)this->_padding_;
    if (puVar2 != (undefined4 *)0x0) {
      (**(code **)*puVar2)(1);
      this->_padding_ = 0;
    }
    pVVar5 = &this->vhcl->control;
    for (iVar4 = 9; iVar4 != 0; iVar4 = iVar4 + -1) {
      pVVar5->steer = 0.0;
      pVVar5 = (VHCL_CONTROL *)&pVVar5->pitch;
    }
    if ((Carrier *)this->_padding_ != (Carrier *)0x0) {
      Carrier::UnTriggerAll((Carrier *)this->_padding_);
    }
    this_00 = BuildPilot(this,local_8);
    fVar1 = *(float *)(this->_padding_ + 0x14);
    iVar4 = this->_padding_;
    fVar1 = fVar1 + fVar1;
    local_14.x = *(float *)(iVar4 + 0x38) * fVar1 + *(float *)(iVar4 + 0x2c) * 5.0 +
                 (float)this->_padding_;
    local_14.y = *(float *)(iVar4 + 0x30) * 5.0 + *(float *)(iVar4 + 0x3c) * fVar1 +
                 (float)this->_padding_;
    local_14.z = *(float *)(iVar4 + 0x34) * 5.0 + *(float *)(iVar4 + 0x40) * fVar1 +
                 (float)this->_padding_;
    GameObject::SetVelocity((GameObject *)this_00,&local_14);
    iVar4 = GameObject::GetHandle((GameObject *)this);
    this_00->abandoned = iVar4;
    GameObject::SetPerceivedTeam((GameObject *)this,0);
    pGVar6 = (GAS_CTRL *)0x0;
    p_Var3 = (_OBJ76 *)(**(code **)(this_00->_padding_ + 0x30))();
    DoAudioNew("jump.wav",p_Var3,pGVar6);
  }
  return;
}
