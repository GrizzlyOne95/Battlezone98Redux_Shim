/*
 * Entry: 0046ee2d
 * Name: UnitTask::GoHeading
 * Namespace: UnitTask
 * Signature: void GoHeading(UnitTask * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitTask::GoHeading(UnitTask *this,float param_1)

{
  int iVar1;
  VECTOR_3D VVar2;
  VECTOR_3D VVar3;
  VECTOR_3D *pVVar4;
  float *pfVar5;
  float fVar6;
  VECTOR_3D local_4c;
  VECTOR_3D local_40;
  VECTOR_3D local_34;
  VECTOR_3D local_28;
  VECTOR_3D local_1c;
  float local_10;
  SINCOS local_c;
  
  local_c = SinCos(param_1);
  iVar1 = this->me->_padding_;
  local_28.x = ((VECTOR_3D *)(iVar1 + 0x20))->x;
  local_28.y = *(float *)(iVar1 + 0x24);
  local_28.z = *(float *)(iVar1 + 0x28);
  local_34.x = ((VECTOR_3D *)(iVar1 + 0x38))->x;
  local_34.y = *(float *)(iVar1 + 0x3c);
  local_34.z = *(float *)(iVar1 + 0x40);
  pVVar4 = CombineVectors(&local_34,local_c.Cos,*(VECTOR_3D *)(iVar1 + 0x38),local_c.Sin,
                          *(VECTOR_3D *)(iVar1 + 0x20));
  local_4c.x = pVVar4->x;
  local_4c.y = pVVar4->y;
  local_4c.z = pVVar4->z;
  pVVar4 = ScaleVector(&local_28,40.0,*pVVar4);
  local_1c.x = pVVar4->x;
  local_1c.y = pVVar4->y;
  local_1c.z = pVVar4->z;
  local_34.x = pVVar4->x;
  local_34.y = pVVar4->y;
  local_34.z = pVVar4->z;
  pfVar5 = (float *)(**(code **)(this->me->_padding_ + 0xc))();
  local_28.x = *pfVar5;
  local_28.y = pfVar5[1];
  local_28.z = pfVar5[2];
  local_40.x = local_34.x + local_28.x;
  local_40.y = local_34.y + local_28.y;
  local_40.z = local_34.z + local_28.z;
  VVar2.y = local_40.y;
  VVar2.x = local_40.x;
  VVar2.z = local_40.z;
  local_10 = local_40.x;
  local_c.Sin = local_40.y;
  local_c.Cos = local_40.z;
  FindPotentialField((GameObject *)this->me,this->skipObj,40.0,VVar2,&local_1c,false);
  AddCliffForce((GameObject *)this->me,&local_40,40.0,&local_1c);
  fVar6 = this->skill;
  if (!NAN(fVar6) && 4.0 < fVar6 != (fVar6 == 4.0)) {
    pVVar4 = EvadeOrdnanceForce(&local_28,(GameObject *)this->me,this->threatOrd,&this->threatOrd);
    local_34.x = pVVar4->x;
    local_34.y = pVVar4->y;
    local_34.z = pVVar4->z;
    fVar6 = TimeStep();
    local_28.x = (this->evadeForce).x;
    local_28.y = (this->evadeForce).y;
    local_28.z = (this->evadeForce).z;
    local_10 = local_34.x - local_28.x;
    local_c.Sin = local_34.y - local_28.y;
    local_c.Cos = local_34.z - local_28.z;
    VVar3.y = local_c.Sin;
    VVar3.x = local_10;
    VVar3.z = local_c.Cos;
    pVVar4 = AddMultVectors(&local_34,this->evadeForce,fVar6 + fVar6,VVar3);
    local_10 = pVVar4->x;
    local_c.Sin = pVVar4->y;
    local_c.Cos = pVVar4->z;
    local_34.x = local_1c.x + local_10;
    (this->evadeForce).x = local_10;
    local_34.y = local_1c.y + local_c.Sin;
    (this->evadeForce).y = local_c.Sin;
    local_34.z = local_1c.z + local_c.Cos;
    (this->evadeForce).z = local_c.Cos;
    local_1c.x = local_34.x;
    local_1c.y = local_34.y;
    local_1c.z = local_34.z;
  }
  LookInDir(this,&local_4c);
  ApplyForce(this,&local_1c);
  return;
}
