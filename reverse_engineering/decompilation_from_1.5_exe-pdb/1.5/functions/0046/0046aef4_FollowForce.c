/*
 * Entry: 0046aef4
 * Name: FollowForce
 * Namespace: Global
 * Signature: VECTOR_3D * FollowForce(VECTOR_3D * __return_storage_ptr__, GameObject * param_1, VECTOR_3D * param_2, GameObject * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __cdecl
FollowForce(VECTOR_3D *__return_storage_ptr__,GameObject *param_1,VECTOR_3D *param_2,
           GameObject *param_3)

{
  float fVar1;
  VECTOR_3D VVar2;
  VECTOR_3D VVar3;
  float *pfVar4;
  VECTOR_3D *pVVar5;
  double dVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  VECTOR_3D local_2c;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  pfVar4 = (float *)(**(code **)(param_1->_padding_ + 0xc))();
  local_2c.x = *pfVar4;
  local_2c.y = pfVar4[1];
  local_2c.z = pfVar4[2];
  local_20 = param_2->x;
  local_1c = param_2->y;
  local_18 = param_2->z;
  fVar7 = param_2->x - local_2c.x;
  local_14 = fVar7;
  fVar8 = param_2->y - local_2c.y;
  local_10 = fVar8;
  fVar9 = param_2->z - local_2c.z;
  local_c = fVar9;
  fVar1 = fVar7 * fVar7 + fVar8 * fVar8 + fVar9 * fVar9 + 0.0001;
  if (fVar1 <= 0.0) {
    pVVar5 = &local_2c;
    local_8 = 0.0;
    local_2c.x = 0.0;
    local_2c.y = 0.0;
    local_2c.z = 0.0;
  }
  else {
    local_8 = SQRT(fVar1);
    dVar6 = rsqrt((double)fVar1);
    VVar2.y = fVar8;
    VVar2.x = fVar7;
    VVar2.z = fVar9;
    pVVar5 = ScaleVector(&local_2c,(float)dVar6,VVar2);
    pVVar5 = ScaleVector(&local_2c,local_8,*pVVar5);
  }
  __return_storage_ptr__->x = pVVar5->x;
  __return_storage_ptr__->y = pVVar5->y;
  __return_storage_ptr__->z = pVVar5->z;
  if (param_3 != (GameObject *)0x0) {
    pfVar4 = (float *)(**(code **)(param_3->_padding_ + 0xc))();
    local_20 = *pfVar4;
    local_1c = pfVar4[1];
    local_18 = pfVar4[2];
    pfVar4 = (float *)(**(code **)(param_1->_padding_ + 0xc))();
    local_2c.x = *pfVar4;
    local_2c.y = pfVar4[1];
    local_2c.z = pfVar4[2];
    fVar7 = local_2c.x - local_20;
    fVar8 = local_2c.y - local_1c;
    fVar9 = local_2c.z - local_18;
    fVar1 = fVar7 * fVar7 + fVar8 * fVar8 + fVar9 * fVar9;
    local_14 = fVar7;
    local_10 = fVar8;
    local_c = fVar9;
    if ((0.0 < fVar1) && (fVar1 < 2500.0)) {
      dVar6 = rsqrt((double)fVar1);
      VVar3.y = fVar8;
      VVar3.x = fVar7;
      VVar3.z = fVar9;
      pVVar5 = ScaleVector(&local_2c,(float)dVar6,VVar3);
      pVVar5 = AddMultVectors(&local_2c,*__return_storage_ptr__,1.0 / (fVar1 * 5e-05),*pVVar5);
      __return_storage_ptr__->x = pVVar5->x;
      __return_storage_ptr__->y = pVVar5->y;
      __return_storage_ptr__->z = pVVar5->z;
    }
  }
  AddCliffForce(param_1,param_2,local_8,__return_storage_ptr__);
  return __return_storage_ptr__;
}
