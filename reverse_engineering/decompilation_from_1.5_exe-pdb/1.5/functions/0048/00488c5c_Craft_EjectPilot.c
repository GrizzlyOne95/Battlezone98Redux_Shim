/*
 * Entry: 00488c5c
 * Name: Craft::EjectPilot
 * Namespace: Craft
 * Signature: void EjectPilot(Craft * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Craft::EjectPilot(Craft *this)

{
  undefined4 *puVar1;
  VECTOR_3D VVar2;
  Craft *pCVar3;
  bool bVar4;
  VECTOR_3D *pVVar5;
  _OBJ76 *p_Var6;
  int iVar7;
  uint uVar8;
  VHCL_CONTROL *pVVar9;
  float fVar10;
  GAS_CTRL *pGVar11;
  VECTOR_3D local_24;
  VECTOR_3D local_18;
  uint local_c;
  Craft *local_8;
  
  local_8 = (Craft *)this->_padding_;
  if ((local_8 == (Craft *)0x0) || (*(int *)(this->_padding_ + 0xac) == 4)) {
    if ((undefined4 *)this->_padding_ != (undefined4 *)0x0) {
      (*(code *)**(undefined4 **)this->_padding_)(1);
    }
  }
  else {
    uVar8 = *(uint *)(this->_padding_ + 0x14);
    this->_padding_ = 0;
    puVar1 = (undefined4 *)this->_padding_;
    uVar8 = uVar8 & 0x10;
    local_c = uVar8;
    if (puVar1 != (undefined4 *)0x0) {
      (**(code **)*puVar1)(1);
      this->_padding_ = 0;
    }
    pVVar9 = &this->vhcl->control;
    for (iVar7 = 9; iVar7 != 0; iVar7 = iVar7 + -1) {
      pVVar9->steer = 0.0;
      pVVar9 = (VHCL_CONTROL *)&pVVar9->pitch;
    }
    if ((Carrier *)this->_padding_ != (Carrier *)0x0) {
      Carrier::UnTriggerAll((Carrier *)this->_padding_);
    }
    bVar4 = DistributedObject::IsRemote((DistributedObject *)&this->_padding_);
    if (!bVar4) {
      if ((uVar8 == 0) &&
         (fVar10 = Random(), (this->fPersonEjectRatio + this->fPersonEjectRatio) - 1.0 < fVar10)) {
        return;
      }
      local_8 = BuildPilot(this,(GameObjectClass *)local_8);
      iVar7 = this->_padding_;
      local_18.x = ((VECTOR_3D *)(iVar7 + 0x2c))->x;
      local_18.y = *(float *)(iVar7 + 0x30);
      local_18.z = *(float *)(iVar7 + 0x34);
      VVar2.x = (float)this->_padding_;
      VVar2.y = (float)this->_padding_;
      VVar2.z = (float)this->_padding_;
      pVVar5 = AddMultVectors(&local_24,VVar2,50.0,*(VECTOR_3D *)(iVar7 + 0x2c));
      pCVar3 = local_8;
      local_18.x = pVVar5->x;
      local_18.y = pVVar5->y;
      local_18.z = pVVar5->z;
      GameObject::SetVelocity((GameObject *)local_8,&local_18);
      if ((local_c != 0) && (iVar7 = Net_IsNetGame(), iVar7 != 0)) {
        *(undefined1 *)&pCVar3->_padding_ = 1;
      }
      pGVar11 = (GAS_CTRL *)0x0;
      p_Var6 = (_OBJ76 *)(**(code **)(pCVar3->_padding_ + 0x30))();
      DoAudioNew(bailSample,p_Var6,pGVar11);
    }
  }
  return;
}
