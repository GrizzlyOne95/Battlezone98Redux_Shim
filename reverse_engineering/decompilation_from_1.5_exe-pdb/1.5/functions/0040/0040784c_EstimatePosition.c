/*
 * Entry: 0040784c
 * Name: EstimatePosition
 * Namespace: Global
 * Signature: VECTOR_3D * EstimatePosition(VECTOR_3D * __return_storage_ptr__, GameObject * param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __cdecl
EstimatePosition(VECTOR_3D *__return_storage_ptr__,GameObject *param_1,float param_2)

{
  float10 fVar1;
  VECTOR_3D VVar2;
  VECTOR_3D VVar3;
  VECTOR_3D VVar4;
  _OBJ76 *p_Var5;
  int iVar6;
  VECTOR_3D *pVVar7;
  VEHICLE *pVVar8;
  MAT_3D *pMVar9;
  MAT_3D *pMVar10;
  float10 fVar11;
  float10 fVar12;
  float10 fVar13;
  float10 fVar14;
  MAT_3D local_80;
  VECTOR_3D local_40;
  VECTOR_3D local_34;
  VECTOR_3D local_28;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  p_Var5 = (_OBJ76 *)(**(code **)(param_1->_padding_ + 0x30))();
  iVar6 = is_vhcl(p_Var5);
  if (iVar6 == 0) {
    pVVar7 = (VECTOR_3D *)(**(code **)(param_1->_padding_ + 0xc))();
  }
  else {
    pVVar8 = get_obj_vhcl(p_Var5);
    fVar11 = (float10)(pVVar8->euler).omega.y;
    pMVar9 = &p_Var5->transform;
    pMVar10 = &local_80;
    for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
      pMVar10->right_x = pMVar9->right_x;
      pMVar9 = (MAT_3D *)&pMVar9->right_y;
      pMVar10 = (MAT_3D *)&pMVar10->right_y;
    }
    local_10 = (float)local_80.posit_x;
    local_c = (float)local_80.posit_y;
    local_8 = (float)local_80.posit_z;
    if ((float10)0.05 <= ABS(fVar11)) {
      fVar1 = (float10)0;
      if (fVar11 <= fVar1) {
        fVar12 = (float10)1;
      }
      else {
        fVar12 = (float10)-1.0;
      }
      fVar14 = (float10)(param_1->euler).v_mag / ABS(fVar11);
      fVar13 = fVar12 * fVar11 * (float10)param_2 - fVar12 * (float10)1.5707964;
      fVar11 = (float10)fsin(fVar13);
      local_28.x = (float)(fVar11 * fVar14);
      local_28.y = (float)fVar1;
      fVar11 = (float10)fcos(fVar13);
      local_28.z = (float)(fVar11 * fVar14);
      local_1c = local_80.right_x;
      local_18 = local_80.right_y;
      local_14 = local_80.right_z;
      local_34.x = local_80.right_x;
      local_34.z = local_80.right_z;
      local_34.y = (float)fVar1;
      VVar3.y = local_c;
      VVar3.x = local_10;
      VVar3.z = local_8;
      VVar4.y = local_34.y;
      VVar4.x = local_80.right_x;
      VVar4.z = local_80.right_z;
      pVVar7 = AddMultVectors(&local_34,VVar3,(float)(fVar12 * fVar14),VVar4);
      local_1c = pVVar7->x;
      local_18 = pVVar7->y;
      local_14 = pVVar7->z;
      local_80.posit_x = (double)local_1c;
      local_80.posit_y = (double)local_18;
      local_80.posit_z = (double)local_14;
      Vector_Transform(&local_40,&local_28,1,&local_80);
    }
    else {
      VVar2.y = local_c;
      VVar2.x = local_10;
      VVar2.z = local_8;
      pVVar7 = AddMultVectors(&local_34,VVar2,param_2,(param_1->euler).v);
      local_40.x = pVVar7->x;
      local_40.y = pVVar7->y;
      local_40.z = pVVar7->z;
    }
    pVVar7 = &local_40;
  }
  __return_storage_ptr__->x = pVVar7->x;
  __return_storage_ptr__->y = pVVar7->y;
  __return_storage_ptr__->z = pVVar7->z;
  return __return_storage_ptr__;
}
