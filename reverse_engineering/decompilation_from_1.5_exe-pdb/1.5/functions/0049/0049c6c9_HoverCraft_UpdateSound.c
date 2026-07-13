/*
 * Entry: 0049c6c9
 * Name: HoverCraft::UpdateSound
 * Namespace: HoverCraft
 * Signature: void UpdateSound(HoverCraft * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall HoverCraft::UpdateSound(HoverCraft *this,float param_1)

{
  ulong *puVar1;
  char *pcVar2;
  float fVar3;
  int iVar4;
  _gas_object *p_Var5;
  GAS_PREP_INFO local_84;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  undefined8 local_3c;
  GAS_CTRL local_34;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  local_60 = turboPitchBase;
  local_68 = turboPitchRange;
  iVar4 = this->_padding_;
  local_48 = turboVolumeBaseUser;
  local_40 = turboVolumeRangeUser;
  local_5c = turboVolumeBaseUser * aiEngineFactor;
  local_54 = turboVolumeRangeUser * aiEngineFactor;
  local_3c = (double)CONCAT44(thrustPitchBase,(long)local_3c);
  local_64 = thrustPitchRange;
  local_44 = thrustVolumeBaseUser;
  local_4c = thrustVolumeRangeUser;
  local_58 = thrustVolumeBaseUser * aiEngineFactor;
  local_50 = aiEngineFactor * thrustVolumeRangeUser;
  fVar3 = (this->throttle - this->lastThrot) * param_1;
  this->lastThrot = fVar3 + fVar3 + this->lastThrot;
  if (*(char *)(iVar4 + 0x36c) != '\0') {
    if (this->soundThrust == (_gas_object *)0x0) {
      InitGASCtrl(&local_34);
      local_34.flags = 0x2001;
      InitGASPrep(&local_84);
      local_84.loopMode = 1;
      local_84.pri = (-(uint)((((_OBJ76 *)this->_padding_)->flags & 0x10) != 0) & 0x14) + 0x2d;
      p_Var5 = StartGASEvent((char *)(iVar4 + 0x36c),(_OBJ76 *)this->_padding_,&local_34,&local_84);
      this->soundThrust = p_Var5;
    }
    if (this->soundThrust != (_gas_object *)0x0) {
      local_3c._0_4_ =
           SUB84((double)(local_64 * this->lastThrot + local_3c._4_4_ + (float)Float2Int),0);
      (this->soundThrust->gpi).sampleRate = (long)local_3c;
      if ((*(byte *)(this->_padding_ + 0x14) & 0x10) == 0) {
        fVar3 = local_50 * this->lastThrot + local_58;
      }
      else {
        fVar3 = local_4c * this->lastThrot + local_44;
      }
      local_3c = (double)(fVar3 + (float)Float2Int);
      (this->soundThrust->gpi).volume = (long)local_3c;
      puVar1 = &(this->soundThrust->gc).flags;
      *puVar1 = *puVar1 | 0x60;
    }
  }
  if ((((_OBJ76 *)this->_padding_)->flags & 0x10) != 0) {
    pcVar2 = (char *)(iVar4 + 0x37c);
    if (*pcVar2 != '\0') {
      fVar3 = this->lastThrot;
      if (NAN(fVar3) || 1.0 < fVar3 == (fVar3 == 1.0)) {
        if (this->soundTurbo != (_gas_object *)0x0) {
          p_Var5 = FindGASObject(pcVar2,(_OBJ76 *)this->_padding_);
          StopGASEvent(p_Var5);
          this->soundTurbo = (_gas_object *)0x0;
        }
      }
      else {
        if (this->soundTurbo == (_gas_object *)0x0) {
          InitGASCtrl(&local_34);
          local_34.flags = 0x2001;
          InitGASPrep(&local_84);
          local_84.loopMode = 1;
          local_84.pri = (-(uint)((((_OBJ76 *)this->_padding_)->flags & 0x10) != 0) & 0x14) + 0x2d;
          p_Var5 = StartGASEvent(pcVar2,(_OBJ76 *)this->_padding_,&local_34,&local_84);
          this->soundTurbo = p_Var5;
        }
        if (this->soundTurbo != (_gas_object *)0x0) {
          local_3c._0_4_ =
               SUB84((double)(local_68 * this->lastThrot + local_60 + (float)Float2Int),0);
          (this->soundTurbo->gpi).sampleRate = (long)local_3c;
          if ((*(byte *)(this->_padding_ + 0x14) & 0x10) == 0) {
            fVar3 = local_54 * this->lastThrot + local_5c;
          }
          else {
            fVar3 = local_40 * this->lastThrot + local_48;
          }
          local_3c = (double)(fVar3 + (float)Float2Int);
          (this->soundTurbo->gpi).volume = (long)local_3c;
          puVar1 = &(this->soundTurbo->gc).flags;
          *puVar1 = *puVar1 | 0x60;
        }
      }
    }
    if (*(char *)(iVar4 + 0x38c) != '\0') {
      fVar3 = (this->airBorne - this->lastFly) * param_1;
      fVar3 = fVar3 + fVar3 + this->lastFly;
      this->lastFly = fVar3;
      if (fVar3 <= 0.05) {
        p_Var5 = this->soundFly;
        if (p_Var5 != (_gas_object *)0x0) {
          StopGASEvent(p_Var5);
          this->soundFly = (_gas_object *)0x0;
        }
      }
      else {
        if (this->soundFly == (_gas_object *)0x0) {
          InitGASCtrl(&local_34);
          local_34.flags = 0x2001;
          InitGASPrep(&local_84);
          local_84.loopMode = 1;
          local_84.pri = (-(uint)((((_OBJ76 *)this->_padding_)->flags & 0x10) != 0) & 0x14) + 0x2d;
          p_Var5 = StartGASEvent((char *)(iVar4 + 0x38c),(_OBJ76 *)this->_padding_,&local_34,
                                 &local_84);
          this->soundFly = p_Var5;
        }
        if (this->soundFly != (_gas_object *)0x0) {
          local_3c._0_4_ = SUB84((double)(this->lastFly * 10.0 + (float)Float2Int),0);
          (this->soundFly->gpi).volume = (long)local_3c;
          puVar1 = &(this->soundFly->gc).flags;
          *puVar1 = *puVar1 | 0x40;
        }
      }
    }
  }
  return;
}
