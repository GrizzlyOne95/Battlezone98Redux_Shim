/*
 * Entry: 004b865d
 * Name: Walker::UpdateWeaponAim
 * Namespace: Walker
 * Signature: void UpdateWeaponAim(Walker * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Walker::UpdateWeaponAim(Walker *this,float param_1)

{
  _OBJ76 *p_Var1;
  double dVar2;
  MAT_3D *pMVar3;
  Weapon *pWVar4;
  GameObject *pGVar5;
  VECTOR_3D *pVVar6;
  VECTOR_3D *pVVar7;
  int iVar8;
  VECTOR_3D *unaff_EBX;
  VECTOR_3D *unaff_ESI;
  float *pfVar9;
  MAT_3D *unaff_EDI;
  MAT_3D *pMVar10;
  MAT_3D local_208;
  MAT_3D local_1c8;
  float local_188 [16];
  MAT_3D local_148;
  float local_108 [10];
  double local_e0;
  double local_d0;
  MAT_3D local_c8;
  MAT_3D local_88;
  undefined4 local_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  double local_3c;
  double local_34;
  double local_2c;
  float local_24;
  undefined4 local_20;
  float local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  int local_c;
  Walker *local_8;
  
  local_8 = this;
  pMVar3 = Build_Pitch_Matrix(&local_148,-(float)this->_padding_);
  local_c = 0;
  pMVar10 = &local_1c8;
  for (iVar8 = 0x10; iVar8 != 0; iVar8 = iVar8 + -1) {
    pMVar10->right_x = pMVar3->right_x;
    pMVar3 = (MAT_3D *)&pMVar3->right_y;
    pMVar10 = (MAT_3D *)&pMVar10->right_y;
  }
  do {
    pWVar4 = Carrier::GetWeapon((Carrier *)this->_padding_,local_c);
    if (pWVar4 != (Weapon *)0x0) {
      pMVar3 = obj_rel_parent_matrix(&local_c8,pWVar4->hard,(_OBJ76 *)local_8->_padding_);
      pfVar9 = local_108;
      for (iVar8 = 0x10; iVar8 != 0; iVar8 = iVar8 + -1) {
        *pfVar9 = pMVar3->right_x;
        pMVar3 = (MAT_3D *)&pMVar3->right_y;
        pfVar9 = pfVar9 + 1;
      }
      pMVar3 = Matrix_Inverse(&local_c8,unaff_EDI);
      p_Var1 = pWVar4->obj;
      pMVar10 = &local_88;
      for (iVar8 = 0x10; iVar8 != 0; iVar8 = iVar8 + -1) {
        pMVar10->right_x = pMVar3->right_x;
        pMVar3 = (MAT_3D *)&pMVar3->right_y;
        pMVar10 = (MAT_3D *)&pMVar10->right_y;
      }
      local_88.posit_z = 0.0;
      local_88.posit_y = 0.0;
      local_88.posit_x = 0.0;
      local_3c = (p_Var1->transform).posit_x;
      local_34 = (p_Var1->transform).posit_y;
      local_2c = (p_Var1->transform).posit_z;
      pMVar3 = Matrix_Multiply(&local_c8,&local_88,&local_1c8);
      dVar2 = local_3c;
      pfVar9 = local_188;
      for (iVar8 = 0x10; iVar8 != 0; iVar8 = iVar8 + -1) {
        *pfVar9 = pMVar3->right_x;
        pMVar3 = (MAT_3D *)&pMVar3->right_y;
        pfVar9 = pfVar9 + 1;
      }
      pfVar9 = local_188;
      pMVar3 = &pWVar4->obj->transform;
      for (iVar8 = 0x10; iVar8 != 0; iVar8 = iVar8 + -1) {
        pMVar3->right_x = *pfVar9;
        pfVar9 = pfVar9 + 1;
        pMVar3 = (MAT_3D *)&pMVar3->right_y;
      }
      p_Var1 = pWVar4->obj;
      (p_Var1->transform).posit_x = dVar2;
      (p_Var1->transform).posit_y = local_34;
      (p_Var1->transform).posit_z = local_2c;
      pGVar5 = GameObject::GetObj(local_8->_padding_);
      if (pGVar5 != (GameObject *)0x0) {
        local_18 = 0;
        local_14 = 0;
        local_10 = 0;
        local_48 = 0;
        local_24 = -(float)local_e0;
        uStack_44 = 0;
        local_20 = 0;
        uStack_40 = 0;
        pVVar6 = (VECTOR_3D *)(**(code **)(pGVar5->_padding_ + 0xc))();
        pVVar7 = (VECTOR_3D *)(**(code **)(local_8->_padding_ + 0xc))();
        local_1c = Dist3D(*pVVar7,*pVVar6);
        local_1c = local_1c - (float)local_d0;
        unaff_EDI = &local_208;
        pMVar3 = Build_Directinal_Matrix(unaff_EDI,unaff_ESI,unaff_EBX);
        p_Var1 = pWVar4->obj;
        pMVar10 = &local_c8;
        for (iVar8 = 0x10; iVar8 != 0; iVar8 = iVar8 + -1) {
          pMVar10->right_x = pMVar3->right_x;
          pMVar3 = (MAT_3D *)&pMVar3->right_y;
          pMVar10 = (MAT_3D *)&pMVar10->right_y;
        }
        pMVar3 = Matrix_Multiply(&local_208,&local_c8,&p_Var1->transform);
        pMVar10 = &local_148;
        for (iVar8 = 0x10; iVar8 != 0; iVar8 = iVar8 + -1) {
          pMVar10->right_x = pMVar3->right_x;
          pMVar3 = (MAT_3D *)&pMVar3->right_y;
          pMVar10 = (MAT_3D *)&pMVar10->right_y;
        }
        pMVar3 = &local_148;
        pMVar10 = &pWVar4->obj->transform;
        for (iVar8 = 0x10; iVar8 != 0; iVar8 = iVar8 + -1) {
          pMVar10->right_x = pMVar3->right_x;
          pMVar3 = (MAT_3D *)&pMVar3->right_y;
          pMVar10 = (MAT_3D *)&pMVar10->right_y;
        }
      }
    }
    local_c = local_c + 1;
    this = local_8;
  } while (local_c < 5);
  return;
}
