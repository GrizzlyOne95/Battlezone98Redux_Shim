/*
 * Entry: 00410d0b
 * Name: DefendTask::DoWander
 * Namespace: DefendTask
 * Signature: void DoWander(DefendTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall DefendTask::DoWander(DefendTask *this)

{
  int iVar1;
  float fVar2;
  VECTOR_3D VVar3;
  VECTOR_3D VVar4;
  float *pfVar5;
  VECTOR_3D *pVVar6;
  double dVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  VECTOR_3D local_40;
  VECTOR_3D local_34;
  VECTOR_3D local_28;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  pfVar5 = (float *)(**(code **)(*(int *)(*(int *)&this->field_0x14 + 0x20) + 0xc))();
  local_28.x = *pfVar5;
  local_28.y = pfVar5[1];
  local_28.z = pfVar5[2];
  local_1c = *(float *)&this->field_0x2c;
  local_18 = *(float *)&this->field_0x30;
  local_14 = *(float *)&this->field_0x34;
  fVar8 = local_1c - local_28.x;
  fVar9 = local_18 - local_28.y;
  fVar10 = local_14 - local_28.z;
  fVar2 = fVar9 * fVar9 + fVar8 * fVar8 + fVar10 * fVar10;
  local_34.x = fVar8;
  local_34.y = fVar9;
  local_34.z = fVar10;
  local_10 = fVar8;
  local_c = fVar9;
  local_8 = fVar10;
  if (25.0 <= fVar2) {
    dVar7 = rsqrt((double)fVar2);
    VVar3.y = fVar9;
    VVar3.x = fVar8;
    VVar3.z = fVar10;
    pVVar6 = ScaleVector(&local_28,(float)dVar7,VVar3);
  }
  else {
    pVVar6 = (VECTOR_3D *)(*(int *)(*(int *)&this->field_0x14 + 0xe8) + 0x38);
  }
  local_40.x = pVVar6->x;
  local_40.y = pVVar6->y;
  local_40.z = pVVar6->z;
  VVar4.x = *(float *)&this->field_0x2c;
  VVar4.y = *(float *)&this->field_0x30;
  VVar4.z = *(float *)&this->field_0x34;
  FindPotentialField(*(GameObject **)&this->field_0x14,*(GameObject **)&this->field_0x84,40.0,VVar4,
                     &local_34,false);
  AddCliffForce(*(GameObject **)&this->field_0x14,(VECTOR_3D *)&this->field_0x2c,40.0,&local_34);
  UnitTask::LookInDir((UnitTask *)this,&local_40);
  UnitTask::ApplyForce((UnitTask *)this,&local_34);
  iVar1 = *(int *)(*(int *)&this->field_0x14 + 0x228);
  if (*(float *)(iVar1 + 0xd0) == 1.0) {
    *(undefined4 *)(iVar1 + 0xd4) = 1;
  }
  return;
}
