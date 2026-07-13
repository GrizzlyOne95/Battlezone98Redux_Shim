/*
 * Entry: 0049d7b0
 * Name: HoverCraft::UpdateWeaponAim
 * Namespace: HoverCraft
 * Signature: void UpdateWeaponAim(HoverCraft * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall HoverCraft::UpdateWeaponAim(HoverCraft *this,float param_1)

{
  _OBJ76 *p_Var1;
  double dVar2;
  MAT_3D *pMVar3;
  Weapon *pWVar4;
  int iVar5;
  MAT_3D *unaff_EDI;
  float *pfVar6;
  MAT_3D *pMVar7;
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
  HoverCraft *local_c;
  int local_8;
  
  local_c = this;
  pMVar3 = Build_Pitch_Matrix(&local_e4,-(float)this->_padding_);
  local_8 = 0;
  pMVar7 = &local_164;
  for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
    pMVar7->right_x = pMVar3->right_x;
    pMVar3 = (MAT_3D *)&pMVar3->right_y;
    pMVar7 = (MAT_3D *)&pMVar7->right_y;
  }
  do {
    pWVar4 = Carrier::GetWeapon((Carrier *)this->_padding_,local_8);
    if (pWVar4 != (Weapon *)0x0) {
      pMVar3 = obj_rel_parent_matrix(&local_a4,pWVar4->hard,(_OBJ76 *)local_c->_padding_);
      pfVar6 = local_64;
      for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
        *pfVar6 = pMVar3->right_x;
        pMVar3 = (MAT_3D *)&pMVar3->right_y;
        pfVar6 = pfVar6 + 1;
      }
      local_2c = 0;
      local_34 = 0;
      local_3c = 0;
      pMVar3 = Matrix_Inverse(&local_a4,unaff_EDI);
      p_Var1 = pWVar4->obj;
      pMVar7 = &local_124;
      for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
        pMVar7->right_x = pMVar3->right_x;
        pMVar3 = (MAT_3D *)&pMVar3->right_y;
        pMVar7 = (MAT_3D *)&pMVar7->right_y;
      }
      local_24 = (p_Var1->transform).posit_x;
      local_1c = (p_Var1->transform).posit_y;
      local_14 = (p_Var1->transform).posit_z;
      pMVar3 = Matrix_Multiply(&local_a4,&local_124,&local_164);
      dVar2 = local_24;
      pMVar7 = &local_e4;
      for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
        pMVar7->right_x = pMVar3->right_x;
        pMVar3 = (MAT_3D *)&pMVar3->right_y;
        pMVar7 = (MAT_3D *)&pMVar7->right_y;
      }
      pMVar3 = &local_e4;
      pMVar7 = &pWVar4->obj->transform;
      for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
        pMVar7->right_x = pMVar3->right_x;
        pMVar3 = (MAT_3D *)&pMVar3->right_y;
        pMVar7 = (MAT_3D *)&pMVar7->right_y;
      }
      p_Var1 = pWVar4->obj;
      (p_Var1->transform).posit_x = dVar2;
      (p_Var1->transform).posit_y = local_1c;
      (p_Var1->transform).posit_z = local_14;
    }
    local_8 = local_8 + 1;
    this = local_c;
  } while (local_8 < 5);
  return;
}
