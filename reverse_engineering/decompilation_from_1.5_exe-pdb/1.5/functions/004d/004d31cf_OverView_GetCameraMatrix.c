/*
 * Entry: 004d31cf
 * Name: OverView::GetCameraMatrix
 * Namespace: OverView
 * Signature: MAT_3D * GetCameraMatrix(OverView * this, MAT_3D * __return_storage_ptr__)
 * Symbol source: IMPORTED
 * Export status: ok
 */

MAT_3D * __thiscall OverView::GetCameraMatrix(OverView *this,MAT_3D *__return_storage_ptr__)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  SINCOS SVar5;
  
  fVar1 = (this->viewUp).y;
  fVar2 = (float)this[1]._padding_;
  SVar5 = SinCos(0.87266463);
  fVar4 = SVar5.Cos;
  fVar3 = SVar5.Sin;
  __return_storage_ptr__->right_x = fVar2;
  __return_storage_ptr__->right_y = 0.0;
  __return_storage_ptr__->right_z = -fVar1;
  __return_storage_ptr__->up_x = fVar3 * fVar1;
  __return_storage_ptr__->up_y = fVar4;
  __return_storage_ptr__->up_z = fVar3 * fVar2;
  __return_storage_ptr__->front_x = fVar4 * fVar1;
  __return_storage_ptr__->front_y = -fVar3;
  __return_storage_ptr__->front_z = fVar4 * fVar2;
  __return_storage_ptr__->posit_x = (double)((this->viewCenter).y - fVar4 * fVar1 * 500.0);
  __return_storage_ptr__->posit_y = (double)((this->viewCenter).z - -fVar3 * 500.0);
  __return_storage_ptr__->posit_z = (double)((this->viewUp).x - fVar4 * fVar2 * 500.0);
  return __return_storage_ptr__;
}
