/*
 * Entry: 0046e239
 * Name: UnitTask::GotoForce
 * Namespace: UnitTask
 * Signature: VECTOR_3D * GotoForce(UnitTask * this, VECTOR_3D * __return_storage_ptr__, bool param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __thiscall
UnitTask::GotoForce(UnitTask *this,VECTOR_3D *__return_storage_ptr__,bool param_1)

{
  VECTOR_2D *pVVar1;
  int iVar2;
  Craft *pCVar3;
  VECTOR_3D VVar4;
  VECTOR_3D VVar5;
  VECTOR_3D VVar6;
  VECTOR_3D VVar7;
  float *pfVar8;
  VECTOR_3D *pVVar9;
  float fVar10;
  double dVar11;
  float fVar12;
  undefined4 uVar13;
  float fVar14;
  VECTOR_3D local_44;
  VECTOR_3D local_38;
  VECTOR_3D local_2c;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  bool local_5;
  
  pfVar8 = (float *)(**(code **)(this->me->_padding_ + 0xc))();
  pVVar1 = this->plan->points;
  iVar2 = this->planPoint;
  local_44.x = pVVar1[iVar2].x;
  local_44.z = pVVar1[iVar2].z;
  local_10 = local_44.x;
  fVar10 = *pfVar8 - (this->gotoPoint).x;
  local_44.y = 0.0;
  fVar12 = pfVar8[2] - (this->gotoPoint).z;
  local_5 = iVar2 == this->plan->pointCount + -1;
  local_14 = fVar12 * fVar12 + fVar10 * fVar10;
  if (local_14 <= 400.0) {
    local_14 = SQRT(local_14);
  }
  else {
    local_14 = 20.0;
  }
  fVar12 = local_44.x - *pfVar8;
  local_2c.y = 0.0;
  fVar14 = local_44.z - pfVar8[2];
  local_20 = fVar12;
  local_18 = fVar14;
  local_1c = 0.0;
  fVar10 = fVar12 * fVar12 + fVar14 * fVar14;
  if (fVar10 <= 0.0) {
    pVVar9 = &local_2c;
    local_c = 0.0;
    local_2c.x = 0.0;
    local_2c.y = 0.0;
    local_2c.z = 0.0;
  }
  else {
    local_c = SQRT(fVar10);
    uVar13 = 0;
    local_2c.x = fVar12;
    local_2c.z = fVar14;
    dVar11 = rsqrt((double)fVar10);
    VVar5.y = (float)uVar13;
    VVar5.x = fVar12;
    VVar5.z = fVar14;
    pVVar9 = ScaleVector(&local_38,(float)dVar11,VVar5);
    fVar10 = ATTRACTIVE_COEFFICIENT * local_14;
    if (local_5 != false) {
      fVar10 = fVar10 * EXTRA_GOAL_ATTRACTION;
    }
    pVVar9 = ScaleVector(&local_38,fVar10,*pVVar9);
  }
  __return_storage_ptr__->x = pVVar9->x;
  __return_storage_ptr__->y = pVVar9->y;
  __return_storage_ptr__->z = pVVar9->z;
  fVar10 = DEFAULT_REPULSION_CUTOFF;
  if (local_c < DEFAULT_REPULSION_CUTOFF) {
    fVar10 = local_c;
  }
  VVar4.y = local_44.y;
  VVar4.x = local_44.x;
  VVar4.z = local_44.z;
  FindPotentialField((GameObject *)this->me,this->skipObj,fVar10,VVar4,__return_storage_ptr__,false)
  ;
  fVar10 = this->skill;
  if (!NAN(fVar10) && 4.0 < fVar10 != (fVar10 == 4.0)) {
    pVVar9 = EvadeOrdnanceForce(&local_38,(GameObject *)this->me,this->threatOrd,&this->threatOrd);
    local_2c.x = pVVar9->x;
    local_2c.y = pVVar9->y;
    local_2c.z = pVVar9->z;
    fVar10 = TimeStep();
    local_20 = (this->evadeForce).x;
    local_1c = (this->evadeForce).y;
    local_18 = (this->evadeForce).z;
    local_38.x = local_2c.x - local_20;
    local_38.y = local_2c.y - local_1c;
    local_38.z = local_2c.z - local_18;
    VVar6.y = local_38.y;
    VVar6.x = local_38.x;
    VVar6.z = local_38.z;
    pVVar9 = AddMultVectors(&local_38,this->evadeForce,fVar10 + fVar10,VVar6);
    local_20 = pVVar9->x;
    local_1c = pVVar9->y;
    local_18 = pVVar9->z;
    (this->evadeForce).x = local_20;
    (this->evadeForce).y = local_1c;
    (this->evadeForce).z = local_18;
    local_38.x = __return_storage_ptr__->x;
    local_38.y = __return_storage_ptr__->y;
    local_38.z = __return_storage_ptr__->z;
    local_2c.x = local_20 + local_38.x;
    local_2c.y = local_1c + local_38.y;
    local_2c.z = local_18 + local_38.z;
    __return_storage_ptr__->x = local_2c.x;
    __return_storage_ptr__->y = local_2c.y;
    __return_storage_ptr__->z = local_2c.z;
  }
  if (!param_1) {
    AddCliffForce((GameObject *)this->me,&local_44,local_c,__return_storage_ptr__);
  }
  if (local_5 != false) {
    pCVar3 = this->me;
    VVar7.x = (float)pCVar3->_padding_;
    VVar7.y = (float)pCVar3->_padding_;
    VVar7.z = (float)pCVar3->_padding_;
    pVVar9 = AddMultVectors(&local_38,*__return_storage_ptr__,-0.2,VVar7);
    __return_storage_ptr__->x = pVVar9->x;
    __return_storage_ptr__->y = pVVar9->y;
    __return_storage_ptr__->z = pVVar9->z;
  }
  return __return_storage_ptr__;
}
