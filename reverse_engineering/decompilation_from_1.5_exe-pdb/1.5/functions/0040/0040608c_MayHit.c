/*
 * Entry: 0040608c
 * Name: MayHit
 * Namespace: Global
 * Signature: bool MayHit(GameObject * param_1, GameObject * param_2, float param_3, float param_4, float param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl
MayHit(GameObject *param_1,GameObject *param_2,float param_3,float param_4,float param_5)

{
  float fVar1;
  float fVar2;
  float *pfVar3;
  VECTOR_3D *pVVar4;
  SPHERE *pSVar5;
  VECTOR_3D local_28;
  float local_1c;
  float local_18;
  float local_14;
  VECTOR_3D local_10;
  
  pfVar3 = (float *)(**(code **)(param_1->_padding_ + 0xc))();
  local_1c = *pfVar3;
  local_18 = pfVar3[1];
  local_14 = pfVar3[2];
  pfVar3 = (float *)(**(code **)(param_2->_padding_ + 0xc))();
  local_28.x = *pfVar3 - local_1c;
  local_28.y = pfVar3[1] - local_18;
  local_28.z = pfVar3[2] - local_14;
  local_10.x = local_28.x;
  local_10.y = local_28.y;
  local_10.z = local_28.z;
  pVVar4 = Vector_Unrotate(&local_28,&local_10,&param_1->obj->transform);
  local_10.x = pVVar4->x;
  local_10.y = pVVar4->y;
  local_10.z = pVVar4->z;
  if ((0.0 <= local_10.z) && (local_10.z <= param_3)) {
    pSVar5 = GameObject::GetSphere(param_2);
    fVar1 = pSVar5->radius * param_5;
    fVar2 = local_10.x * local_10.x + local_10.y * local_10.y;
    if ((fVar2 < fVar1 * fVar1) || (fVar2 < (local_10.z * local_10.z + fVar2) * param_4 * param_4))
    {
      return true;
    }
  }
  return false;
}
