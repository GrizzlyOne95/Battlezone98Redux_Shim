/*
 * Entry: 0046e668
 * Name: UnitTask::DoStand
 * Namespace: UnitTask
 * Signature: void DoStand(UnitTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitTask::DoStand(UnitTask *this)

{
  Craft *pCVar1;
  VEHICLE *pVVar2;
  VECTOR_3D VVar3;
  VECTOR_3D VVar4;
  VECTOR_3D VVar5;
  float *pfVar6;
  VECTOR_3D *pVVar7;
  VHCL_CONTROL *pVVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  VECTOR_3D local_48;
  VECTOR_3D local_3c;
  VECTOR_3D local_30;
  float local_24;
  float local_20;
  float local_1c;
  VECTOR_3D local_18;
  float local_c;
  VHCL_CONTROL *local_8;
  
  pCVar1 = this->me;
  pVVar2 = pCVar1->vhcl;
  pVVar8 = &pVVar2->control;
  local_8 = pVVar8;
  if (pCVar1->state == UNDEPLOYED) {
    pfVar6 = (float *)(**(code **)(pCVar1->_padding_ + 0xc))();
    local_24 = 0.0;
    local_20 = 0.0;
    local_48.x = *pfVar6;
    local_1c = 0.0;
    local_48.y = pfVar6[1];
    local_48.z = pfVar6[2];
    local_18.x = 0.0;
    local_18.y = 0.0;
    local_18.z = 0.0;
    if (this->targetDistSq < this->closeSq) {
      pVVar7 = Vector_Rotate(&local_3c,&this->targetDir,(MAT_3D *)(this->me->_padding_ + 0x20));
      VVar3.y = local_20;
      VVar3.x = local_24;
      VVar3.z = local_1c;
      pVVar7 = AddMultVectors(&local_3c,VVar3,(1.0 - this->targetDistSq / this->closeSq) * -40.0,
                              *pVVar7);
      local_18.x = pVVar7->x;
      local_18.y = pVVar7->y;
      local_18.z = pVVar7->z;
    }
    VVar4.y = local_48.y;
    VVar4.x = local_48.x;
    VVar4.z = local_48.z;
    FindPotentialField((GameObject *)this->me,this->skipObj,40.0,VVar4,&local_18,false);
    AddCliffForce((GameObject *)this->me,&local_48,40.0,&local_18);
    fVar9 = this->skill;
    if (!NAN(fVar9) && 4.0 < fVar9 != (fVar9 == 4.0)) {
      pVVar7 = EvadeOrdnanceForce(&local_3c,(GameObject *)this->me,this->threatOrd,&this->threatOrd)
      ;
      local_24 = pVVar7->x;
      local_20 = pVVar7->y;
      local_1c = pVVar7->z;
      fVar9 = TimeStep();
      local_30.x = (this->evadeForce).x;
      local_30.y = (this->evadeForce).y;
      local_30.z = (this->evadeForce).z;
      local_3c.x = local_24 - local_30.x;
      local_3c.y = local_20 - local_30.y;
      local_3c.z = local_1c - local_30.z;
      VVar5.y = local_3c.y;
      VVar5.x = local_3c.x;
      VVar5.z = local_3c.z;
      pVVar7 = AddMultVectors(&local_3c,this->evadeForce,fVar9 + fVar9,VVar5);
      local_24 = pVVar7->x;
      local_20 = pVVar7->y;
      local_1c = pVVar7->z;
      local_3c.x = local_18.x + local_24;
      (this->evadeForce).x = local_24;
      local_3c.y = local_18.y + local_20;
      (this->evadeForce).y = local_20;
      local_3c.z = local_18.z + local_1c;
      (this->evadeForce).z = local_1c;
      local_18.x = local_3c.x;
      local_18.y = local_3c.y;
      local_18.z = local_3c.z;
    }
    pVVar7 = ScaleVector(&local_30,this->skill * 0.5 - 0.5,this->targetVel);
    local_3c.x = pVVar7->x;
    local_3c.y = pVVar7->y;
    local_3c.z = pVVar7->z;
    LookAtLocalPos(this,&this->targetDiff,&local_3c);
    ApplyForce(this,&local_18);
    fVar9 = VecLen(this->gotoForce);
    pVVar8 = local_8;
    if (fVar9 < 5.0) {
      local_8->braccel = 0.0;
      local_8->strafe = 0.0;
    }
  }
  else {
    (pVVar2->control).turbo = 0;
    (pVVar2->control).braccel = 0.0;
    (pVVar2->control).strafe = 0.0;
    fVar9 = Clamp(-((this->targetDir).x * this->steerFactor),-1.0,1.0);
    pVVar8->steer = fVar9;
    fVar11 = 1.0;
    fVar10 = -1.0;
    fVar9 = TimeStep();
    fVar9 = Clamp(fVar9 * (this->targetDir).y * 4.0 + this->pitch,fVar10,fVar11);
    this->pitch = fVar9;
    (pVVar2->control).pitch = fVar9;
  }
  if (this->skill < 4.0) {
    fVar9 = Get_Time();
    local_8 = (VHCL_CONTROL *)(fVar9 * 0.5);
    local_c = 0.1 - this->skill * 0.025;
    fVar11 = 1.0;
    fVar10 = -1.0;
    fVar9 = Noise1D((float)local_8);
    fVar9 = Clamp(fVar9 * local_c + pVVar8->pitch,fVar10,fVar11);
    pVVar8->pitch = fVar9;
    fVar11 = 1.0;
    fVar10 = -1.0;
    fVar9 = Noise1D((float)local_8 + 25.734);
    fVar9 = Clamp(fVar9 * local_c + pVVar8->steer,fVar10,fVar11);
    pVVar8->steer = fVar9;
  }
  return;
}
