/*
 * Entry: 0040c2c0
 * Name: est_pos
 * Namespace: Global
 * Signature: void est_pos(_OBJ76 * param_1, float param_2, VECTOR_3D * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl est_pos(_OBJ76 *param_1,float param_2,VECTOR_3D *param_3)

{
  VECTOR_3D VVar1;
  VECTOR_3D VVar2;
  VECTOR_3D VVar3;
  VECTOR_3D VVar4;
  int iVar5;
  VEHICLE *pVVar6;
  VECTOR_3D *pVVar7;
  MAT_3D *pMVar8;
  MAT_3D *pMVar9;
  float10 fVar10;
  float10 fVar11;
  float10 fVar12;
  float10 fVar13;
  VECTOR_3D local_88;
  MAT_3D local_7c;
  VECTOR_3D local_3c;
  float local_30;
  float local_2c;
  float local_28;
  VECTOR_3D local_24;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  iVar5 = is_vhcl(param_1);
  if (iVar5 != 0) {
    pVVar6 = get_obj_vhcl(param_1);
    local_8 = (pVVar6->euler).omega.y;
    pMVar8 = &param_1->transform;
    pMVar9 = &local_7c;
    for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
      pMVar9->right_x = pMVar8->right_x;
      pMVar8 = (MAT_3D *)&pMVar8->right_y;
      pMVar9 = (MAT_3D *)&pMVar9->right_y;
    }
    local_30 = (float)local_7c.posit_x;
    local_2c = (float)local_7c.posit_y;
    local_28 = (float)local_7c.posit_z;
    ClassGetVelocity(param_1,&local_88,&local_18);
    if ((float10)0.05 <= ABS((float10)local_8)) {
      if (local_8 <= 0.0) {
        fVar10 = (float10)1;
      }
      else {
        fVar10 = (float10)-1.0;
      }
      fVar13 = (float10)local_18 / ABS((float10)local_8);
      fVar12 = (float10)local_8 * fVar10 * (float10)param_2 - fVar10 * (float10)1.5707964;
      fVar11 = (float10)fsin(fVar12);
      local_3c.x = (float)(fVar11 * fVar13);
      local_3c.y = 0.0;
      fVar11 = (float10)fcos(fVar12);
      local_3c.z = (float)(fVar11 * fVar13);
      local_14 = local_7c.right_x;
      local_10 = local_7c.right_y;
      local_c = local_7c.right_z;
      local_24.x = local_7c.right_x;
      local_24.z = local_7c.right_z;
      local_24.y = 0.0;
      VVar2.y = local_2c;
      VVar2.x = local_30;
      VVar2.z = local_28;
      VVar4.y = 0.0;
      VVar4.x = local_7c.right_x;
      VVar4.z = local_7c.right_z;
      pVVar7 = AddMultVectors(&local_24,VVar2,(float)(fVar10 * fVar13),VVar4);
      local_14 = pVVar7->x;
      local_10 = pVVar7->y;
      local_c = pVVar7->z;
      local_7c.posit_x = (double)local_14;
      local_7c.posit_y = (double)local_10;
      local_7c.posit_z = (double)local_c;
      Vector_Transform(param_3,&local_3c,1,&local_7c);
    }
    else {
      VVar1.y = local_2c;
      VVar1.x = local_30;
      VVar1.z = local_28;
      VVar3.y = local_88.y;
      VVar3.x = local_88.x;
      VVar3.z = local_88.z;
      pVVar7 = AddMultVectors(&local_24,VVar1,param_2,VVar3);
      param_3->x = pVVar7->x;
      param_3->y = pVVar7->y;
      param_3->z = pVVar7->z;
    }
  }
  return;
}
