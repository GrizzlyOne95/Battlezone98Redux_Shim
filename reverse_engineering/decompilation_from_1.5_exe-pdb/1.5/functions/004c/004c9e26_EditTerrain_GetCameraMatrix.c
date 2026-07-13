/*
 * Entry: 004c9e26
 * Name: EditTerrain::GetCameraMatrix
 * Namespace: EditTerrain
 * Signature: MAT_3D * GetCameraMatrix(EditTerrain * this, MAT_3D * __return_storage_ptr__)
 * Symbol source: IMPORTED
 * Export status: ok
 */

MAT_3D * __thiscall EditTerrain::GetCameraMatrix(EditTerrain *this,MAT_3D *__return_storage_ptr__)

{
  float fVar1;
  MAT_3D *pMVar2;
  int iVar3;
  MAT_3D *pMVar4;
  SINCOS SVar5;
  float fVar6;
  MAT_3D local_90;
  MAT_3D local_50;
  SINCOS local_c;
  
  local_c.Cos = TimeStepLocal();
  fVar6 = (float)eye_controls.track_pitch * local_c.Cos * 0.5 + this->Pitch;
  this->Pitch = fVar6;
  if (fVar6 < 0.5235988) {
    this->Pitch = 0.5235988;
  }
  if (1.5707963 < this->Pitch) {
    this->Pitch = 1.5707963;
  }
  fVar6 = (float)eye_controls.track_yaw * local_c.Cos * 0.5 + this->Yaw;
  this->Yaw = fVar6;
  if (fVar6 <= 3.1415927) {
    if (-3.1415927 <= fVar6) goto LAB_004c9ed7;
    this->Yaw = fVar6 + 6.2831855;
    fVar6 = this->Yaw0 + 6.2831855;
  }
  else {
    this->Yaw = fVar6 - 6.2831855;
    fVar6 = this->Yaw0 - 6.2831855;
  }
  this->Yaw0 = fVar6;
LAB_004c9ed7:
  local_c.Cos = local_c.Cos * 5.0;
  fVar6 = lpfilter(this->Pitch0,this->Pitch,local_c.Cos);
  this->Pitch0 = fVar6;
  fVar6 = lpfilter(this->Yaw0,this->Yaw,local_c.Cos);
  this->Yaw0 = fVar6;
  pMVar2 = &Identity_Matrix;
  pMVar4 = __return_storage_ptr__;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    pMVar4->right_x = pMVar2->right_x;
    pMVar2 = (MAT_3D *)&pMVar2->right_y;
    pMVar4 = (MAT_3D *)&pMVar4->right_y;
  }
  __return_storage_ptr__->posit_z = -250.0;
  fVar6 = this->Pitch0;
  pMVar2 = &Identity_Matrix;
  pMVar4 = &local_50;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    pMVar4->right_x = pMVar2->right_x;
    pMVar2 = (MAT_3D *)&pMVar2->right_y;
    pMVar4 = (MAT_3D *)&pMVar4->right_y;
  }
  SVar5 = SinCos(fVar6);
  local_50.up_y = local_c.Cos;
  local_c.Cos = SVar5.Cos;
  local_50.front_z = local_c.Cos;
  local_c.Sin = SVar5.Sin;
  local_50.up_z = local_c.Sin;
  local_50.front_y = -local_c.Sin;
  local_c = SVar5;
  pMVar2 = Matrix_Multiply(&local_90,__return_storage_ptr__,&local_50);
  pMVar4 = __return_storage_ptr__;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    pMVar4->right_x = pMVar2->right_x;
    pMVar2 = (MAT_3D *)&pMVar2->right_y;
    pMVar4 = (MAT_3D *)&pMVar4->right_y;
  }
  fVar6 = this->Yaw0;
  pMVar2 = &Identity_Matrix;
  pMVar4 = &local_50;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    pMVar4->right_x = pMVar2->right_x;
    pMVar2 = (MAT_3D *)&pMVar2->right_y;
    pMVar4 = (MAT_3D *)&pMVar4->right_y;
  }
  SVar5 = SinCos(fVar6);
  local_50.right_x = local_c.Cos;
  local_c.Cos = SVar5.Cos;
  local_50.front_z = local_c.Cos;
  local_c.Sin = SVar5.Sin;
  local_50.right_z = local_c.Sin;
  local_50.front_x = -local_c.Sin;
  local_c = SVar5;
  pMVar2 = Matrix_Multiply(&local_90,__return_storage_ptr__,&local_50);
  pMVar4 = __return_storage_ptr__;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    pMVar4->right_x = pMVar2->right_x;
    pMVar2 = (MAT_3D *)&pMVar2->right_y;
    pMVar4 = (MAT_3D *)&pMVar4->right_y;
  }
  __return_storage_ptr__->posit_x =
       (double)((this->viewCenter).x + (float)__return_storage_ptr__->posit_x);
  __return_storage_ptr__->posit_y =
       (double)((this->viewCenter).y + (float)__return_storage_ptr__->posit_y);
  __return_storage_ptr__->posit_z =
       (double)((this->viewCenter).z + (float)__return_storage_ptr__->posit_z);
  fVar6 = __return_storage_ptr__->up_y;
  fVar1 = __return_storage_ptr__->up_z;
  (this->viewUp).x = __return_storage_ptr__->up_x;
  (this->viewUp).y = fVar6;
  (this->viewUp).z = fVar1;
  return __return_storage_ptr__;
}
