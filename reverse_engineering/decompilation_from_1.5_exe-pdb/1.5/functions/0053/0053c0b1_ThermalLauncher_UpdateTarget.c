/*
 * Entry: 0053c0b1
 * Name: ThermalLauncher::UpdateTarget
 * Namespace: ThermalLauncher
 * Signature: GameObject * UpdateTarget(ThermalLauncher * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall ThermalLauncher::UpdateTarget(ThermalLauncher *this,float param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  GameObject *pGVar4;
  bool bVar5;
  MAT_3D *pMVar6;
  float *pfVar7;
  SPHERE *pSVar8;
  int iVar9;
  int iVar10;
  MAT_3D *unaff_EDI;
  MAT_3D *pMVar11;
  MAT_3D local_118;
  MAT_3D local_d8;
  float local_98 [10];
  double local_70;
  double local_60;
  Range_Search_Results local_58;
  float local_2c;
  float local_28;
  float local_24;
  int *local_20;
  GameObject *local_1c;
  float local_18;
  VECTOR_3D local_14;
  GameObject *local_8;
  
  pMVar6 = Matrix_Multiply(&local_118,(MAT_3D *)(*(int *)&this->field_0x10 + 0x20),
                           (MAT_3D *)&this->field_0x20);
  pfVar7 = local_98;
  for (iVar9 = 0x10; iVar9 != 0; iVar9 = iVar9 + -1) {
    *pfVar7 = pMVar6->right_x;
    pMVar6 = (MAT_3D *)&pMVar6->right_y;
    pfVar7 = pfVar7 + 1;
  }
  pMVar6 = Matrix_Inverse(&local_118,unaff_EDI);
  local_1c = (GameObject *)0x0;
  iVar9 = *(int *)&this->field_0x8;
  pMVar11 = &local_d8;
  for (iVar10 = 0x10; iVar10 != 0; iVar10 = iVar10 + -1) {
    pMVar11->right_x = pMVar6->right_x;
    pMVar6 = (MAT_3D *)&pMVar6->right_y;
    pMVar11 = (MAT_3D *)&pMVar11->right_y;
  }
  local_28 = *(float *)(iVar9 + 0x7c);
  local_2c = local_28 * local_28;
  local_18 = 0.0;
  Range::Search(GameObject::objectRange,local_70,local_60,(double)local_28,&local_58);
  while (bVar5 = Range_Search_Results::Get_Next_Object(&local_58,&local_20), bVar5) {
    local_8 = GameObject::GetObj(*local_20);
    if (((local_8 != (GameObject *)0x0) && (local_8 != *(GameObject **)&this->field_0xc0)) &&
       ((local_8->obj->flags & 0x400) == 0)) {
      pfVar7 = (float *)(**(code **)(local_8->_padding_ + 0xc))();
      local_14.x = *pfVar7;
      local_14.y = pfVar7[1];
      local_14.z = pfVar7[2];
      Vector_Transform(&local_14,&local_14,1,&local_d8);
      pGVar4 = local_8;
      if ((0.0 <= local_14.z) && (local_14.z <= local_28)) {
        pSVar8 = GameObject::GetSphere(local_8);
        fVar1 = pSVar8->radius * 0.75;
        fVar3 = local_14.x * local_14.x + local_14.y * local_14.y;
        fVar2 = local_14.z * local_14.z + fVar3;
        if ((fVar3 <= fVar1 * fVar1) || (fVar3 <= *(float *)&this->field_0xb4 * fVar2)) {
          local_8 = (GameObject *)(1.0 / fVar2);
          local_24 = 1.0 - fVar3 * (float)local_8;
          local_24 = local_24 * local_24;
          local_24 = local_24 * local_24;
          local_24 = local_24 * local_24;
          local_24 = local_24 * local_24;
          iVar9 = (**(code **)pGVar4->_padding_)();
          fVar1 = local_24 * local_24 * *(float *)(iVar9 + 0xe8) * (float)local_8 * local_2c;
          if (local_18 < fVar1) {
            local_1c = pGVar4;
            local_18 = fVar1;
          }
        }
      }
    }
  }
  return local_1c;
}
