/*
 * Entry: 004b410b
 * Name: TurretCraft::UpdateWeaponAim
 * Namespace: TurretCraft
 * Signature: void UpdateWeaponAim(TurretCraft * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TurretCraft::UpdateWeaponAim(TurretCraft *this,float param_1)

{
  double dVar1;
  double dVar2;
  double dVar3;
  _OBJ76 *p_Var4;
  Weapon *pWVar5;
  MAT_3D *pMVar6;
  int iVar7;
  MAT_3D *unaff_EDI;
  float *pfVar8;
  MAT_3D *pMVar9;
  MAT_3D local_164;
  MAT_3D local_124;
  MAT_3D local_e4;
  MAT_3D local_a4;
  float local_64 [10];
  undefined8 local_3c;
  undefined8 local_34;
  undefined8 local_2c;
  double local_24;
  double local_1c;
  double local_14;
  TurretCraft *local_c;
  int local_8;
  
  local_c = this;
  if (this->turretXCount < 1) {
    pMVar6 = Build_Pitch_Matrix(&local_e4,-(float)this->_padding_);
    local_8 = 0;
    pMVar9 = &local_164;
    for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
      pMVar9->right_x = pMVar6->right_x;
      pMVar6 = (MAT_3D *)&pMVar6->right_y;
      pMVar9 = (MAT_3D *)&pMVar9->right_y;
    }
    do {
      pWVar5 = Carrier::GetWeapon((Carrier *)this->_padding_,local_8);
      if (pWVar5 != (Weapon *)0x0) {
        pMVar6 = obj_rel_parent_matrix(&local_a4,pWVar5->hard,(_OBJ76 *)local_c->_padding_);
        pfVar8 = local_64;
        for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
          *pfVar8 = pMVar6->right_x;
          pMVar6 = (MAT_3D *)&pMVar6->right_y;
          pfVar8 = pfVar8 + 1;
        }
        local_2c = 0;
        local_34 = 0;
        local_3c = 0;
        pMVar6 = Matrix_Inverse(&local_a4,unaff_EDI);
        p_Var4 = pWVar5->obj;
        pMVar9 = &local_124;
        for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
          pMVar9->right_x = pMVar6->right_x;
          pMVar6 = (MAT_3D *)&pMVar6->right_y;
          pMVar9 = (MAT_3D *)&pMVar9->right_y;
        }
        local_24 = (p_Var4->transform).posit_x;
        local_1c = (p_Var4->transform).posit_y;
        local_14 = (p_Var4->transform).posit_z;
        pMVar6 = Matrix_Multiply(&local_a4,&local_124,&local_164);
        dVar1 = local_24;
        pMVar9 = &local_e4;
        for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
          pMVar9->right_x = pMVar6->right_x;
          pMVar6 = (MAT_3D *)&pMVar6->right_y;
          pMVar9 = (MAT_3D *)&pMVar9->right_y;
        }
        pMVar6 = &local_e4;
        pMVar9 = &pWVar5->obj->transform;
        for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
          pMVar9->right_x = pMVar6->right_x;
          pMVar6 = (MAT_3D *)&pMVar6->right_y;
          pMVar9 = (MAT_3D *)&pMVar9->right_y;
        }
        p_Var4 = pWVar5->obj;
        (p_Var4->transform).posit_x = dVar1;
        (p_Var4->transform).posit_y = local_1c;
        (p_Var4->transform).posit_z = local_14;
      }
      local_8 = local_8 + 1;
      this = local_c;
    } while (local_8 < 5);
  }
  else {
    local_8 = 0;
    do {
      pWVar5 = Carrier::GetWeapon((Carrier *)this->_padding_,local_8);
      if (pWVar5 != (Weapon *)0x0) {
        p_Var4 = pWVar5->obj;
        dVar1 = (p_Var4->transform).posit_x;
        dVar2 = (p_Var4->transform).posit_y;
        dVar3 = (p_Var4->transform).posit_z;
        pMVar6 = &Identity_Matrix;
        pMVar9 = &p_Var4->transform;
        for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
          pMVar9->right_x = pMVar6->right_x;
          pMVar6 = (MAT_3D *)&pMVar6->right_y;
          pMVar9 = (MAT_3D *)&pMVar9->right_y;
        }
        p_Var4 = pWVar5->obj;
        (p_Var4->transform).posit_x = dVar1;
        (p_Var4->transform).posit_y = dVar2;
        (p_Var4->transform).posit_z = dVar3;
      }
      local_8 = local_8 + 1;
    } while (local_8 < 5);
  }
  return;
}
