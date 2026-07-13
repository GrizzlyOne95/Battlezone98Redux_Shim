/*
 * Entry: 004f0941
 * Name: Camera_Audio_Info
 * Namespace: Global
 * Signature: void Camera_Audio_Info(CAMERA * param_1, _OBJ76 * param_2, float * param_3, float * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Camera_Audio_Info(CAMERA *param_1,_OBJ76 *param_2,float *param_3,float *param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  VECTOR_3D VVar4;
  VECTOR_3D VVar5;
  MAT_3D *pMVar6;
  VECTOR_3D *pVVar7;
  int iVar8;
  float *pfVar9;
  float fVar10;
  MAT_3D local_b4;
  float local_74 [10];
  double local_4c;
  double local_44;
  double local_3c;
  VECTOR_3D local_34;
  float local_28;
  float local_24;
  float local_20;
  VECTOR_3D local_1c;
  float local_10;
  float local_c;
  float local_8;
  
  pMVar6 = obj_rel_parent_matrix(&local_b4,param_2,(_OBJ76 *)0x0);
  pfVar9 = local_74;
  for (iVar8 = 0x10; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pfVar9 = pMVar6->right_x;
    pMVar6 = (MAT_3D *)&pMVar6->right_y;
    pfVar9 = pfVar9 + 1;
  }
  local_10 = (float)local_4c;
  local_c = (float)local_44;
  local_8 = (float)local_3c;
  pVVar7 = Camera_Get_Position(&local_1c,param_1);
  local_1c.x = local_10 - pVVar7->x;
  local_1c.y = local_c - pVVar7->y;
  local_1c.z = local_8 - pVVar7->z;
  local_28 = (param_1->Matrix).right_x;
  local_24 = (param_1->Matrix).up_x;
  local_20 = (param_1->Matrix).front_x;
  local_10 = (param_1->Matrix).right_y;
  local_c = (param_1->Matrix).up_y;
  local_8 = (param_1->Matrix).front_y;
  VVar4.y = local_1c.y;
  VVar4.x = local_1c.x;
  VVar4.z = local_1c.z;
  VVar5.y = local_c;
  VVar5.x = local_10;
  VVar5.z = local_8;
  pVVar7 = AddMultVectors(&local_34,VVar4,
                          -(local_1c.x * local_10 + local_1c.y * local_c + local_1c.z * local_8),
                          VVar5);
  local_10 = pVVar7->x;
  local_c = pVVar7->y;
  local_8 = pVVar7->z;
  VVar4 = *pVVar7;
  *param_3 = local_1c.x * local_1c.x + local_1c.y * local_1c.y + local_1c.z * local_1c.z;
  fVar1 = local_8 * local_20;
  fVar3 = local_c * local_24;
  fVar2 = local_10 * local_28;
  fVar10 = VecLen(VVar4);
  *param_4 = (fVar2 + fVar3 + fVar1) / fVar10;
  return;
}
