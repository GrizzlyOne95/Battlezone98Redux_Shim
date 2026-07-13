/*
 * Entry: 0046b0b8
 * Name: EvadeLineOfFireForce
 * Namespace: Global
 * Signature: VECTOR_3D * EvadeLineOfFireForce(VECTOR_3D * __return_storage_ptr__, GameObject * param_1, GameObject * param_2, float param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __cdecl
EvadeLineOfFireForce
          (VECTOR_3D *__return_storage_ptr__,GameObject *param_1,GameObject *param_2,float param_3)

{
  int iVar1;
  VECTOR_3D VVar2;
  GameObject *pGVar3;
  float *pfVar4;
  SPHERE *pSVar5;
  VECTOR_3D *pVVar6;
  int unaff_EBX;
  float fVar7;
  VECTOR_3D local_24;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  pGVar3 = param_1;
  pfVar4 = (float *)(**(code **)(*(int *)(unaff_EBX + 0x20) + 0xc))();
  local_24.x = *pfVar4;
  local_24.y = pfVar4[1];
  local_24.z = pfVar4[2];
  pfVar4 = (float *)(**(code **)(param_1->_padding_ + 0xc))();
  iVar1 = *(int *)(unaff_EBX + 0xe8);
  local_18 = *(float *)(iVar1 + 0x20);
  local_14 = *(float *)(iVar1 + 0x24);
  local_10 = *(float *)(iVar1 + 0x28);
  local_c = (pfVar4[2] - local_24.z) * local_10 + (pfVar4[1] - local_24.y) * local_14 +
            local_18 * (*pfVar4 - local_24.x);
  local_8 = ABS(local_c);
  pSVar5 = GameObject::GetSphere(param_1);
  fVar7 = pSVar5->radius;
  if (fVar7 + fVar7 <= local_8) {
    pVVar6 = &local_24;
    local_24.x = 0.0;
    local_24.y = 0.0;
    local_24.z = 0.0;
  }
  else {
    param_1 = (GameObject *)Min(1.0 - (local_8 / pSVar5->radius) * 0.5,0.5);
    if (local_c < 0.0) {
      param_1 = (GameObject *)-(float)param_1;
    }
    fVar7 = Get_TimeLocal();
    local_c = (float)pGVar3->indexNo;
    fVar7 = Noise1D(fVar7 * 0.75 + (float)(int)local_c + 72.86);
    VVar2.y = local_14;
    VVar2.x = local_18;
    VVar2.z = local_10;
    pVVar6 = ScaleVector(&local_24,(fVar7 + (float)param_1) * (float)param_2,VVar2);
  }
  __return_storage_ptr__->x = pVVar6->x;
  __return_storage_ptr__->y = pVVar6->y;
  __return_storage_ptr__->z = pVVar6->z;
  return __return_storage_ptr__;
}
