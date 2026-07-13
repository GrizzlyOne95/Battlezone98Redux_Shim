/*
 * Entry: 00408b6a
 * Name: MightCollide
 * Namespace: Global
 * Signature: bool MightCollide(GameObject * param_1, GameObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl MightCollide(GameObject *param_1,GameObject *param_2)

{
  float fVar1;
  VECTOR_3D VVar2;
  VECTOR_3D VVar3;
  bool bVar4;
  undefined4 *puVar5;
  SPHERE *pSVar6;
  SPHERE *pSVar7;
  VECTOR_3D *pVVar8;
  float fVar9;
  VECTOR_3D local_20;
  float local_14;
  float fStack_10;
  float fStack_c;
  VECTOR_3D *local_8;
  
  puVar5 = (undefined4 *)(**(code **)(param_1->_padding_ + 0xc))();
  local_14 = (float)*puVar5;
  fStack_10 = (float)puVar5[1];
  fStack_c = (float)puVar5[2];
  local_8 = (VECTOR_3D *)(**(code **)(param_2->_padding_ + 0xc))();
  pSVar6 = GameObject::GetSphere(param_1);
  pSVar7 = GameObject::GetSphere(param_2);
  fVar1 = pSVar6->radius + pSVar7->radius + 2.5;
  fVar1 = fVar1 * fVar1;
  VVar3.y = fStack_10;
  VVar3.x = local_14;
  VVar3.z = fStack_c;
  fVar9 = Dist3D_Squared(*local_8,VVar3);
  if (fVar1 <= fVar9) {
    local_8 = (VECTOR_3D *)ClosestApproach(param_1,param_2);
    if ((NAN((float)local_8) || 0.0 < (float)local_8 == ((float)local_8 == 0.0)) ||
       (3.0 <= (float)local_8)) {
      bVar4 = false;
    }
    else {
      pVVar8 = EstimatePosition(&local_20,param_2,(float)local_8);
      local_14 = pVVar8->x;
      fStack_10 = pVVar8->y;
      fStack_c = pVVar8->z;
      pVVar8 = EstimatePosition(&local_20,param_1,(float)local_8);
      VVar2.y = fStack_10;
      VVar2.x = local_14;
      VVar2.z = fStack_c;
      fVar9 = Dist3D_Squared(VVar2,*pVVar8);
      if (fVar1 <= fVar9) {
        bVar4 = false;
      }
      else {
        bVar4 = true;
      }
    }
  }
  else {
    bVar4 = true;
  }
  return bVar4;
}
