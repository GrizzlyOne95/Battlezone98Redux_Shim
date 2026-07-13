/*
 * Entry: 0053dfa6
 * Name: Weapon::Control
 * Namespace: Weapon
 * Signature: void Control(Weapon * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Weapon::Control(Weapon *this,float param_1)

{
  MAT_3D *pMVar1;
  int iVar2;
  float *pfVar3;
  MAT_3D *unaff_EDI;
  MAT_3D local_84;
  float local_44 [16];
  
  pMVar1 = obj_rel_parent_matrix(&local_84,this->hard,(_OBJ76 *)0x0);
  pfVar3 = local_44;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *pfVar3 = pMVar1->right_x;
    pMVar1 = (MAT_3D *)&pMVar1->right_y;
    pfVar3 = pfVar3 + 1;
  }
  pfVar3 = local_44;
  pMVar1 = &this->M;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    pMVar1->right_x = *pfVar3;
    pfVar3 = pfVar3 + 1;
    pMVar1 = (MAT_3D *)&pMVar1->right_y;
  }
  pMVar1 = Matrix_Inverse(&local_84,unaff_EDI);
  pfVar3 = local_44;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *pfVar3 = pMVar1->right_x;
    pMVar1 = (MAT_3D *)&pMVar1->right_y;
    pfVar3 = pfVar3 + 1;
  }
  pfVar3 = local_44;
  pMVar1 = &this->I;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    pMVar1->right_x = *pfVar3;
    pfVar3 = pfVar3 + 1;
    pMVar1 = (MAT_3D *)&pMVar1->right_y;
  }
  return;
}
