/*
 * Entry: 00488a98
 * Name: Craft::ExplodePilot
 * Namespace: Craft
 * Signature: void ExplodePilot(Craft * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Craft::ExplodePilot(Craft *this)

{
  float fVar1;
  undefined4 *puVar2;
  VECTOR_3D VVar3;
  VECTOR_3D VVar4;
  int iVar5;
  VECTOR_3D *pVVar6;
  float *pfVar7;
  VHCL_CONTROL *pVVar8;
  MAT_3D *pMVar9;
  MAT_3D local_60;
  VECTOR_3D local_20;
  float local_14;
  float local_10;
  float local_c;
  int local_8;
  
  if (this->_padding_ != 0) {
    if (((this == (Craft *)GameObject::userObject) &&
        (iVar5 = UserPref_unlimitedArmor(), iVar5 != 0)) && (iVar5 = Net_IsNetGame(), iVar5 == 0)) {
      return;
    }
    BettyVoice::VehicleLost(&bettyVoice,(GameObject *)this);
    puVar2 = (undefined4 *)this->_padding_;
    this->_padding_ = 0;
    if (puVar2 != (undefined4 *)0x0) {
      (**(code **)*puVar2)(1);
      this->_padding_ = 0;
    }
    pVVar8 = &this->vhcl->control;
    for (iVar5 = 9; iVar5 != 0; iVar5 = iVar5 + -1) {
      pVVar8->steer = 0.0;
      pVVar8 = (VHCL_CONTROL *)&pVVar8->pitch;
    }
    if ((Carrier *)this->_padding_ != (Carrier *)0x0) {
      Carrier::UnTriggerAll((Carrier *)this->_padding_);
    }
    if (this == (Craft *)GameObject::userObject) {
      DisableInputs();
      Push_Camera();
      Set_View((tagENTITY *)this->_padding_,GK_FREE_EYE_VIEW);
      eye_controls.track_yaw = 1;
      iVar5 = Net_IsNetGame();
      if (iVar5 != 0) {
        Net_KillPlayer();
      }
    }
    pVVar6 = obj_get_world_position(&local_20,this->vhcl->eyepoint);
    fVar1 = pVVar6->x;
    local_10 = pVVar6->y;
    local_c = pVVar6->z;
    pfVar7 = (float *)(this->_padding_ + 0x20);
    pMVar9 = &local_60;
    local_14 = fVar1;
    for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
      pMVar9->right_x = *pfVar7;
      pfVar7 = pfVar7 + 1;
      pMVar9 = (MAT_3D *)&pMVar9->right_y;
    }
    local_60.posit_x = (double)fVar1;
    local_60.posit_y = (double)local_10;
    local_60.posit_z = (double)local_c;
    ExplosionClass::Build(xplSecondary,&local_60,(_OBJ76 *)0x0);
    local_8 = 10;
    do {
      local_8 = local_8 + -1;
      VVar4.x = (float)this->_padding_;
      VVar4.y = (float)this->_padding_;
      VVar4.z = (float)this->_padding_;
      VVar3.y = local_10;
      VVar3.x = local_14;
      VVar3.z = local_c;
      ChunkEffect::CreateChunklet(&chunkEffect,VVar3,VVar4,false);
    } while (local_8 != 0);
    GameObject::SetPerceivedTeam((GameObject *)this,0);
    DoAudioNew("squish.wav",this->vhcl->eyepoint,(GAS_CTRL *)0x0);
  }
  return;
}
