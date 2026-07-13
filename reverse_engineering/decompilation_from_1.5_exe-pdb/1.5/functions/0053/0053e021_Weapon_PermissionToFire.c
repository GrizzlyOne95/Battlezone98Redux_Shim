/*
 * Entry: 0053e021
 * Name: Weapon::PermissionToFire
 * Namespace: Weapon
 * Signature: bool PermissionToFire(Weapon * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Weapon::PermissionToFire(Weapon *this)

{
  MAT_3D *pMVar1;
  int iVar2;
  float *pfVar3;
  MAT_3D local_94;
  float local_54 [10];
  double local_2c;
  double local_24;
  double local_1c;
  VECTOR_3D local_14;
  float local_8;
  
  pMVar1 = Matrix_Multiply(&local_94,&this->obj->transform,&this->M);
  pfVar3 = local_54;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *pfVar3 = pMVar1->right_x;
    pMVar1 = (MAT_3D *)&pMVar1->right_y;
    pfVar3 = pfVar3 + 1;
  }
  Terrain_GetHeightAndNormal(local_2c,local_1c,&local_8,&local_14);
  if (local_8 + 0.1 < (float)local_24) {
    return true;
  }
  return false;
}
