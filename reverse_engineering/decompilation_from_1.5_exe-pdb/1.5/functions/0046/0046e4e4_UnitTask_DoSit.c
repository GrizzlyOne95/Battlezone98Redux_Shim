/*
 * Entry: 0046e4e4
 * Name: UnitTask::DoSit
 * Namespace: UnitTask
 * Signature: void DoSit(UnitTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitTask::DoSit(UnitTask *this)

{
  VECTOR_3D VVar1;
  VECTOR_3D VVar2;
  VECTOR_3D VVar3;
  char cVar4;
  VECTOR_3D *pVVar5;
  Craft *pCVar6;
  VHCL_CONTROL *pVVar7;
  float fVar8;
  VECTOR_3D local_3c;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  VECTOR_3D local_18;
  VHCL_CONTROL *local_c;
  Craft *local_8;
  
  local_18.x = 0.0;
  local_18.y = 0.0;
  pCVar6 = this->me;
  local_18.z = 0.0;
  fVar8 = this->skill;
  pVVar7 = &pCVar6->vhcl->control;
  local_c = pVVar7;
  local_8 = pCVar6;
  if (!NAN(fVar8) && 4.0 < fVar8 != (fVar8 == 4.0)) {
    cVar4 = (**(code **)(pCVar6->_padding_ + 0x68))();
    if (cVar4 != '\0') {
      pVVar5 = EvadeOrdnanceForce(&local_3c,(GameObject *)this->me,this->threatOrd,&this->threatOrd)
      ;
      local_24 = pVVar5->x;
      local_20 = pVVar5->y;
      local_1c = pVVar5->z;
      fVar8 = TimeStep();
      local_30 = (this->evadeForce).x;
      local_2c = (this->evadeForce).y;
      local_28 = (this->evadeForce).z;
      local_3c.x = local_24 - local_30;
      local_3c.y = local_20 - local_2c;
      local_3c.z = local_1c - local_28;
      VVar2.y = local_3c.y;
      VVar2.x = local_3c.x;
      VVar2.z = local_3c.z;
      pVVar5 = AddMultVectors(&local_3c,this->evadeForce,fVar8 + fVar8,VVar2);
      local_3c.x = pVVar5->x;
      local_3c.y = pVVar5->y;
      local_3c.z = pVVar5->z;
      (this->evadeForce).x = local_3c.x;
      (this->evadeForce).y = local_3c.y;
      (this->evadeForce).z = local_3c.z;
      pCVar6 = local_8;
      pVVar7 = local_c;
      local_24 = local_3c.x;
      local_20 = local_3c.y;
      local_1c = local_3c.z;
      local_18.x = local_3c.x;
      local_18.y = local_3c.y;
      local_18.z = local_3c.z;
    }
  }
  if (0.01 < (float)pCVar6->_padding_) {
    VVar3.x = (float)pCVar6->_padding_;
    VVar3.y = (float)pCVar6->_padding_;
    VVar3.z = (float)pCVar6->_padding_;
    VVar1.y = local_18.y;
    VVar1.x = local_18.x;
    VVar1.z = local_18.z;
    pVVar5 = AddMultVectors(&local_3c,VVar1,-4.0,VVar3);
    local_18.x = pVVar5->x;
    local_18.y = pVVar5->y;
    local_18.z = pVVar5->z;
    pCVar6 = local_8;
    pVVar7 = local_c;
  }
  ApplyForce(this,&local_18);
  fVar8 = Clamp(-(float)pCVar6->_padding_,-1.0,1.0);
  pVVar7->steer = fVar8;
  pVVar7->turbo = 0;
  return;
}
