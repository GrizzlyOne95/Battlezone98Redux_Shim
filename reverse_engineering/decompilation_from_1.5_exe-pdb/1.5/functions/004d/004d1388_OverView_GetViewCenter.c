/*
 * Entry: 004d1388
 * Name: OverView::GetViewCenter
 * Namespace: OverView
 * Signature: VECTOR_3D * GetViewCenter(OverView * this, VECTOR_3D * __return_storage_ptr__)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __thiscall OverView::GetViewCenter(OverView *this,VECTOR_3D *__return_storage_ptr__)

{
  __return_storage_ptr__->x = (this->viewCenter).y;
  __return_storage_ptr__->y = (this->viewCenter).z;
  __return_storage_ptr__->z = (this->viewUp).x;
  return __return_storage_ptr__;
}
