/*
 * Entry: 0046f103
 * Name: UnitTask::DoFlee
 * Namespace: UnitTask
 * Signature: void DoFlee(UnitTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitTask::DoFlee(UnitTask *this)

{
  VEHICLE *pVVar1;
  VECTOR_3D VVar2;
  VECTOR_3D VVar3;
  VECTOR_3D *pVVar4;
  float *pfVar5;
  VECTOR_3D *unaff_ESI;
  float unaff_EDI;
  float fVar6;
  float fVar7;
  float fVar8;
  VECTOR_3D local_48;
  VECTOR_3D local_3c;
  VECTOR_3D local_30;
  float local_24;
  float local_20;
  float local_1c;
  VECTOR_3D local_18;
  UnitTask *local_c;
  float local_8;
  
  local_c = this;
  pVVar4 = ScaleVector(&local_30,this->skill * 0.5 - 0.5,this->targetVel);
  local_3c.x = pVVar4->x;
  local_3c.y = pVVar4->y;
  local_3c.z = pVVar4->z;
  LookAtLocalPos(this,&this->targetDiff,&local_3c);
  pfVar5 = (float *)(**(code **)(this->him->_padding_ + 0xc))();
  local_30.x = *pfVar5;
  local_30.y = pfVar5[1];
  local_30.z = pfVar5[2];
  pfVar5 = (float *)(**(code **)(this->me->_padding_ + 0xc))();
  local_24 = *pfVar5;
  local_20 = pfVar5[1];
  local_1c = pfVar5[2];
  local_3c.x = local_24 - local_30.x;
  local_3c.y = local_20 - local_30.y;
  local_3c.z = local_1c - local_30.z;
  fVar6 = this->skill;
  local_18.x = local_3c.x;
  local_18.y = local_3c.y;
  local_18.z = local_3c.z;
  if (!NAN(fVar6) && 2.0 < fVar6 != (fVar6 == 2.0)) {
    EvadeRandomForce((GameObject *)0x41200000,unaff_EDI,unaff_ESI);
    local_3c.x = 0.0;
    local_3c.y = 0.0;
    local_3c.z = 0.0;
    local_24 = 0.0;
    local_20 = 0.0;
    local_1c = 0.0;
    if (this->him != (GameObject *)0x0) {
      pVVar4 = EvadeLineOfFireForce
                         (&local_30,(GameObject *)this->me,
                          (GameObject *)(((this->skill - 2.0) + 1.0) * 5.0),unaff_EDI);
      local_30.x = pVVar4->x;
      local_30.y = pVVar4->y;
      local_30.z = pVVar4->z;
      this = local_c;
      local_24 = local_30.x;
      local_20 = local_30.y;
      local_1c = local_30.z;
    }
    fVar6 = this->skill;
    local_3c.x = local_24;
    local_3c.y = local_20;
    local_3c.z = local_1c;
    if (!NAN(fVar6) && 4.0 < fVar6 != (fVar6 == 4.0)) {
      pVVar4 = EvadeOrdnanceForce(&local_30,(GameObject *)this->me,this->threatOrd,&this->threatOrd)
      ;
      local_3c.x = pVVar4->x;
      local_3c.y = pVVar4->y;
      local_3c.z = pVVar4->z;
      local_30.x = local_24 + local_3c.x;
      local_30.y = local_20 + local_3c.y;
      local_30.z = local_1c + local_3c.z;
      local_24 = local_30.x;
      local_20 = local_30.y;
      local_1c = local_30.z;
    }
    fVar6 = TimeStep();
    local_3c.x = (this->evadeForce).x;
    local_3c.y = (this->evadeForce).y;
    local_3c.z = (this->evadeForce).z;
    local_30.x = local_24 - local_3c.x;
    local_30.y = local_20 - local_3c.y;
    local_30.z = local_1c - local_3c.z;
    VVar3.y = local_30.y;
    VVar3.x = local_30.x;
    VVar3.z = local_30.z;
    pVVar4 = AddMultVectors(&local_3c,this->evadeForce,fVar6 * 5.0,VVar3);
    local_24 = pVVar4->x;
    local_20 = pVVar4->y;
    local_1c = pVVar4->z;
    local_18.x = local_18.x + local_24;
    (this->evadeForce).x = local_24;
    local_18.y = local_18.y + local_20;
    (this->evadeForce).y = local_20;
    local_18.z = local_18.z + local_1c;
    (this->evadeForce).z = local_1c;
  }
  local_3c.x = local_18.x;
  local_3c.y = local_18.y;
  local_3c.z = local_18.z;
  pVVar4 = Normalize_Vector(&local_3c,&local_18);
  pVVar4 = ScaleVector(&local_30,40.0,*pVVar4);
  local_18.x = pVVar4->x;
  local_18.y = pVVar4->y;
  local_18.z = pVVar4->z;
  local_3c.x = pVVar4->x;
  local_3c.y = pVVar4->y;
  local_3c.z = pVVar4->z;
  pfVar5 = (float *)(**(code **)(this->me->_padding_ + 0xc))();
  local_30.x = *pfVar5;
  local_30.y = pfVar5[1];
  local_30.z = pfVar5[2];
  local_48.x = local_3c.x + local_30.x;
  local_48.y = local_3c.y + local_30.y;
  local_48.z = local_3c.z + local_30.z;
  VVar2.y = local_48.y;
  VVar2.x = local_48.x;
  VVar2.z = local_48.z;
  local_24 = local_48.x;
  local_20 = local_48.y;
  local_1c = local_48.z;
  FindPotentialField((GameObject *)this->me,this->skipObj,40.0,VVar2,&local_18,false);
  AddCliffForce((GameObject *)this->me,&local_48,40.0,&local_18);
  pVVar1 = this->me->vhcl;
  ApplyForce(this,&local_18);
  if ((pVVar1->control).braccel == 1.0) {
    (pVVar1->control).turbo = 1;
  }
  if (this->skill < 4.0) {
    local_8 = Get_Time();
    local_8 = local_8 * 0.5;
    local_c = (UnitTask *)(0.3 - this->skill * 0.075);
    fVar8 = 1.0;
    fVar7 = -1.0;
    fVar6 = Noise1D(local_8);
    fVar6 = Clamp(fVar6 * (float)local_c + (pVVar1->control).pitch,fVar7,fVar8);
    (pVVar1->control).pitch = fVar6;
    fVar8 = 1.0;
    fVar7 = -1.0;
    fVar6 = Noise1D(local_8 + 25.734);
    fVar6 = Clamp(fVar6 * (float)local_c + (pVVar1->control).steer,fVar7,fVar8);
    (pVVar1->control).steer = fVar6;
  }
  return;
}
