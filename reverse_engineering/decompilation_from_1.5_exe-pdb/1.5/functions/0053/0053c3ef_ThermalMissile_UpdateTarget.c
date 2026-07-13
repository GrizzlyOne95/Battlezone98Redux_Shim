/*
 * Entry: 0053c3ef
 * Name: ThermalMissile::UpdateTarget
 * Namespace: ThermalMissile
 * Signature: GameObject * UpdateTarget(ThermalMissile * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall ThermalMissile::UpdateTarget(ThermalMissile *this)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  bool bVar5;
  GameObject *pGVar6;
  float *pfVar7;
  MAT_3D *pMVar8;
  SPHERE *pSVar9;
  int iVar10;
  int iVar11;
  VECTOR_3D *unaff_EBX;
  VECTOR_3D *unaff_ESI;
  MAT_3D *unaff_EDI;
  MAT_3D *pMVar12;
  MAT_3D local_148;
  MAT_3D local_108;
  Range_Search_Results local_c8;
  float local_9c [10];
  double local_74;
  double local_64;
  float local_5c;
  float fStack_58;
  float fStack_54;
  float local_50;
  float fStack_4c;
  float fStack_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  int *local_1c;
  GameObject *local_18;
  GameObject *local_14;
  VECTOR_3D local_10;
  
  pGVar6 = GameObject::GetObj(this->_padding_);
  if (pGVar6 == (GameObject *)0x0) {
    pMVar8 = (MAT_3D *)(this->_padding_ + 0x20);
  }
  else {
    iVar10 = this->_padding_;
    local_5c = (float)*(double *)(iVar10 + 0x48);
    fStack_58 = (float)*(double *)(iVar10 + 0x50);
    fStack_54 = (float)*(double *)(iVar10 + 0x58);
    local_10.x = local_5c;
    local_10.y = fStack_58;
    local_10.z = fStack_54;
    pfVar7 = (float *)(**(code **)(pGVar6->_padding_ + 0xc))();
    local_38 = *pfVar7;
    local_34 = pfVar7[1];
    local_30 = pfVar7[2];
    local_50 = local_38 - local_10.x;
    unaff_EDI = &local_148;
    fStack_4c = local_34 - local_10.y;
    fStack_48 = local_30 - local_10.z;
    local_44 = local_50;
    local_40 = fStack_4c;
    local_3c = fStack_48;
    pMVar8 = Build_Directinal_Matrix(unaff_EDI,unaff_ESI,unaff_EBX);
  }
  pfVar7 = local_9c;
  for (iVar10 = 0x10; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pfVar7 = pMVar8->right_x;
    pMVar8 = (MAT_3D *)&pMVar8->right_y;
    pfVar7 = pfVar7 + 1;
  }
  pMVar8 = Matrix_Inverse(&local_148,unaff_EDI);
  local_14 = (GameObject *)0x0;
  local_20 = 0.0;
  iVar10 = this->_padding_;
  pMVar12 = &local_108;
  for (iVar11 = 0x10; iVar11 != 0; iVar11 = iVar11 + -1) {
    pMVar12->right_x = pMVar8->right_x;
    pMVar8 = (MAT_3D *)&pMVar8->right_y;
    pMVar12 = (MAT_3D *)&pMVar12->right_y;
  }
  local_28 = *(float *)(iVar10 + 0x50) * *(float *)(iVar10 + 0x4c);
  local_2c = local_28 * local_28;
  Range::Search(GameObject::objectRange,local_74,local_64,(double)local_28,&local_c8);
  bVar5 = Range_Search_Results::Get_Next_Object(&local_c8,&local_1c);
  if (bVar5) {
    do {
      local_18 = GameObject::GetObj(*local_1c);
      if ((local_18 != (GameObject *)0x0) && ((local_18->obj->flags & 0x400) == 0)) {
        pfVar7 = (float *)(**(code **)(local_18->_padding_ + 0xc))();
        local_10.x = *pfVar7;
        local_10.y = pfVar7[1];
        local_10.z = pfVar7[2];
        Vector_Transform(&local_10,&local_10,1,&local_108);
        pGVar6 = local_18;
        if ((0.0 <= local_10.z) && (local_10.z <= local_28)) {
          pSVar9 = GameObject::GetSphere(local_18);
          fVar1 = pSVar9->radius * 0.75;
          fVar4 = local_10.x * local_10.x + local_10.y * local_10.y;
          fVar3 = local_10.z * local_10.z;
          fVar2 = fVar3 + fVar4;
          if ((fVar4 <= fVar1 * fVar1) || (this->coneCosSq * fVar2 <= fVar3)) {
            local_18 = (GameObject *)(1.0 / fVar2);
            local_24 = fVar3 * (float)local_18 * fVar3 * (float)local_18;
            local_24 = local_24 * local_24;
            local_24 = local_24 * local_24;
            local_24 = local_24 * local_24;
            iVar10 = (**(code **)pGVar6->_padding_)();
            fVar1 = local_24 * local_24 * *(float *)(iVar10 + 0xe8) * (float)local_18 * local_2c;
            if (local_20 < fVar1) {
              local_14 = pGVar6;
              local_20 = fVar1;
            }
          }
        }
      }
      bVar5 = Range_Search_Results::Get_Next_Object(&local_c8,&local_1c);
    } while (bVar5);
    if (local_14 != (GameObject *)0x0) {
      iVar10 = GameObject::GetHandle(local_14);
      this->_padding_ = iVar10;
      return local_14;
    }
  }
  this->_padding_ = 0;
  return local_14;
}
