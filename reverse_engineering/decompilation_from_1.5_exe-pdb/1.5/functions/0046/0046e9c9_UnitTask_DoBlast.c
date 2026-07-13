/*
 * Entry: 0046e9c9
 * Name: UnitTask::DoBlast
 * Namespace: UnitTask
 * Signature: void DoBlast(UnitTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitTask::DoBlast(UnitTask *this)

{
  VECTOR_3D VVar1;
  VECTOR_3D VVar2;
  VHCL_CONTROL *pVVar3;
  VECTOR_3D *pVVar4;
  SPHERE *pSVar5;
  float *pfVar6;
  VECTOR_3D *unaff_ESI;
  float unaff_EDI;
  float fVar7;
  float fVar8;
  float fVar9;
  VECTOR_3D local_50;
  VECTOR_3D local_44;
  VECTOR_3D local_38;
  float local_2c;
  float local_28;
  float local_24;
  VECTOR_3D local_20;
  UnitTask *local_14;
  float local_10;
  VHCL_CONTROL *local_c;
  MAT_3D *local_8;
  
  local_c = &this->me->vhcl->control;
  local_8 = (MAT_3D *)(this->me->_padding_ + 0x20);
  local_14 = this;
  pVVar4 = ScaleVector(&local_38,this->skill * 0.5 - 0.5,this->targetVel);
  local_44.x = pVVar4->x;
  local_44.y = pVVar4->y;
  local_44.z = pVVar4->z;
  LookAtLocalPos(this,&this->targetDiff,&local_44);
  pVVar4 = Vector_Rotate(&local_44,&this->targetDir,local_8);
  if (this->him == (GameObject *)0x0) {
    local_8 = (MAT_3D *)0x0;
  }
  else {
    pSVar5 = GameObject::GetSphere(this->him);
    local_8 = (MAT_3D *)pSVar5->radius;
  }
  local_10 = SQRT(this->targetDistSq);
  fVar7 = SQRT(this->rangeSq);
  fVar8 = SQRT(this->closeSq);
  pSVar5 = GameObject::GetSphere((GameObject *)this->me);
  fVar7 = Clamp(pSVar5->radius + this->blastDist + (float)local_8,fVar8,fVar7);
  fVar7 = local_10 - fVar7;
  if (this->targetDistSq < this->closeSq) {
    fVar7 = fVar7 - (1.0 - this->targetDistSq / this->closeSq) * 40.0;
  }
  pVVar4 = ScaleVector(&local_44,fVar7,*pVVar4);
  fVar7 = this->skill;
  local_20.x = pVVar4->x;
  local_20.y = pVVar4->y;
  local_20.z = pVVar4->z;
  if (!NAN(fVar7) && 2.0 < fVar7 != (fVar7 == 2.0)) {
    local_10 = (float)this->me->_padding_;
    fVar7 = Get_Time();
    if (fVar7 - local_10 < 10.0) {
      EvadeRandomForce((GameObject *)(this->skill * 5.0),unaff_EDI,unaff_ESI);
    }
  }
  fVar7 = this->skill;
  if (!NAN(fVar7) && 3.0 < fVar7 != (fVar7 == 3.0)) {
    local_38.x = 0.0;
    local_38.y = 0.0;
    local_38.z = 0.0;
    local_2c = 0.0;
    local_28 = 0.0;
    local_24 = 0.0;
    if (this->him != (GameObject *)0x0) {
      pVVar4 = EvadeLineOfFireForce
                         (&local_44,(GameObject *)this->me,
                          (GameObject *)(((this->skill - 3.0) + 1.0) * 5.0),unaff_EDI);
      local_44.x = pVVar4->x;
      local_44.y = pVVar4->y;
      local_44.z = pVVar4->z;
      this = local_14;
      local_2c = local_44.x;
      local_28 = local_44.y;
      local_24 = local_44.z;
    }
    fVar7 = this->skill;
    if (!NAN(fVar7) && 4.0 < fVar7 != (fVar7 == 4.0)) {
      local_38.x = local_2c;
      local_38.y = local_28;
      local_38.z = local_24;
      pVVar4 = EvadeOrdnanceForce(&local_38,(GameObject *)this->me,this->threatOrd,&this->threatOrd)
      ;
      local_44.x = pVVar4->x;
      local_44.y = pVVar4->y;
      local_44.z = pVVar4->z;
      local_2c = local_2c + local_44.x;
      local_28 = local_28 + local_44.y;
      local_24 = local_24 + local_44.z;
    }
    local_38.x = local_2c;
    local_38.y = local_28;
    local_38.z = local_24;
    fVar7 = TimeStep();
    local_44.x = (this->evadeForce).x;
    local_44.y = (this->evadeForce).y;
    local_44.z = (this->evadeForce).z;
    local_38.x = local_2c - local_44.x;
    local_38.y = local_28 - local_44.y;
    local_38.z = local_24 - local_44.z;
    VVar2.y = local_38.y;
    VVar2.x = local_38.x;
    VVar2.z = local_38.z;
    pVVar4 = AddMultVectors(&local_44,this->evadeForce,fVar7 * 3.0,VVar2);
    local_2c = pVVar4->x;
    local_28 = pVVar4->y;
    local_24 = pVVar4->z;
    local_20.x = local_20.x + local_2c;
    (this->evadeForce).x = local_2c;
    local_20.y = local_20.y + local_28;
    (this->evadeForce).y = local_28;
    local_20.z = local_20.z + local_24;
    (this->evadeForce).z = local_24;
  }
  local_44.x = local_20.x;
  local_44.y = local_20.y;
  local_44.z = local_20.z;
  pfVar6 = (float *)(**(code **)(this->me->_padding_ + 0xc))();
  local_38.x = *pfVar6;
  local_38.y = pfVar6[1];
  local_38.z = pfVar6[2];
  local_50.x = local_44.x + local_38.x;
  local_50.y = local_44.y + local_38.y;
  local_50.z = local_44.z + local_38.z;
  VVar1.y = local_50.y;
  VVar1.x = local_50.x;
  VVar1.z = local_50.z;
  local_2c = local_50.x;
  local_28 = local_50.y;
  local_24 = local_50.z;
  FindPotentialField((GameObject *)this->me,this->skipObj,40.0,VVar1,&local_20,false);
  AddCliffForce((GameObject *)this->me,&local_50,40.0,&local_20);
  ApplyForce(this,&local_20);
  fVar7 = VecLen(this->gotoForce);
  pVVar3 = local_c;
  if (fVar7 < 1.0) {
    local_c->braccel = 0.0;
    local_c->strafe = 0.0;
  }
  if (local_c->braccel == 1.0) {
    local_c->turbo = 1;
  }
  if (this->skill < 4.0) {
    fVar7 = Get_Time();
    local_c = (VHCL_CONTROL *)(fVar7 * 0.5);
    local_8 = (MAT_3D *)(0.2 - this->skill * 0.05);
    fVar9 = 1.0;
    fVar8 = -1.0;
    fVar7 = Noise1D((float)local_c);
    fVar7 = Clamp(fVar7 * (float)local_8 + pVVar3->pitch,fVar8,fVar9);
    pVVar3->pitch = fVar7;
    fVar9 = 1.0;
    fVar8 = -1.0;
    fVar7 = Noise1D((float)local_c + 25.734);
    fVar7 = Clamp(fVar7 * (float)local_8 + pVVar3->steer,fVar8,fVar9);
    pVVar3->steer = fVar7;
  }
  return;
}
