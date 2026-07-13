/*
 * Entry: 004dd331
 * Name: Net::GetStartLocation
 * Namespace: Net
 * Signature: VECTOR_3D * GetStartLocation(Net * this, VECTOR_3D * __return_storage_ptr__)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __thiscall Net::GetStartLocation(Net *this,VECTOR_3D *__return_storage_ptr__)

{
  __return_storage_ptr__->x = (this->start_location).x;
  __return_storage_ptr__->y = (this->start_location).y;
  __return_storage_ptr__->z = (this->start_location).z;
  return __return_storage_ptr__;
}
