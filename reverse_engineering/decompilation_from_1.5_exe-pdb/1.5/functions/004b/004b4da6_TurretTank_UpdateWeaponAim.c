/*
 * Entry: 004b4da6
 * Name: TurretTank::UpdateWeaponAim
 * Namespace: TurretTank
 * Signature: void UpdateWeaponAim(TurretTank * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TurretTank::UpdateWeaponAim(TurretTank *this,float param_1)

{
  _OBJ76 *p_Var1;
  double dVar2;
  MAT_3D *pMVar3;
  Weapon *pWVar4;
  int iVar5;
  MAT_3D *unaff_EDI;
  float *pfVar6;
  MAT_3D *pMVar7;
  MAT_3D local_160;
  float local_120 [16];
  MAT_3D local_e0;
  MAT_3D local_a0;
  MAT_3D local_60;
  double local_20;
  double local_18;
  double local_10;
  TurretTank *local_8;
  
  local_8 = this;
  if ((this->turretXCount < 1) || (this->_padding_ == 0)) {
    HoverCraft::UpdateWeaponAim((HoverCraft *)this,param_1);
  }
  else {
    pMVar3 = Build_Pitch_Matrix(&local_e0,-(float)this->_padding_);
    param_1 = 0.0;
    pMVar7 = &local_160;
    for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
      pMVar7->right_x = pMVar3->right_x;
      pMVar3 = (MAT_3D *)&pMVar3->right_y;
      pMVar7 = (MAT_3D *)&pMVar7->right_y;
    }
    do {
      pWVar4 = Carrier::GetWeapon((Carrier *)this->_padding_,(int)param_1);
      if (pWVar4 != (Weapon *)0x0) {
        pMVar3 = obj_rel_parent_matrix(&local_a0,pWVar4->hard,(_OBJ76 *)local_8->_padding_);
        pfVar6 = local_120;
        for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
          *pfVar6 = pMVar3->right_x;
          pMVar3 = (MAT_3D *)&pMVar3->right_y;
          pfVar6 = pfVar6 + 1;
        }
        pMVar3 = Matrix_Inverse(&local_a0,unaff_EDI);
        p_Var1 = pWVar4->obj;
        pMVar7 = &local_60;
        for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
          pMVar7->right_x = pMVar3->right_x;
          pMVar3 = (MAT_3D *)&pMVar3->right_y;
          pMVar7 = (MAT_3D *)&pMVar7->right_y;
        }
        local_60.posit_z = 0.0;
        local_60.posit_y = 0.0;
        local_60.posit_x = 0.0;
        local_20 = (p_Var1->transform).posit_x;
        local_18 = (p_Var1->transform).posit_y;
        local_10 = (p_Var1->transform).posit_z;
        pMVar3 = Matrix_Multiply(&local_a0,&local_60,&local_160);
        dVar2 = local_20;
        pMVar7 = &local_e0;
        for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
          pMVar7->right_x = pMVar3->right_x;
          pMVar3 = (MAT_3D *)&pMVar3->right_y;
          pMVar7 = (MAT_3D *)&pMVar7->right_y;
        }
        pMVar3 = &local_e0;
        pMVar7 = &pWVar4->obj->transform;
        for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
          pMVar7->right_x = pMVar3->right_x;
          pMVar3 = (MAT_3D *)&pMVar3->right_y;
          pMVar7 = (MAT_3D *)&pMVar7->right_y;
        }
        p_Var1 = pWVar4->obj;
        (p_Var1->transform).posit_x = dVar2;
        (p_Var1->transform).posit_y = local_18;
        (p_Var1->transform).posit_z = local_10;
      }
      param_1 = (float)((int)param_1 + 1);
      this = local_8;
    } while ((int)param_1 < 5);
  }
  return;
}
