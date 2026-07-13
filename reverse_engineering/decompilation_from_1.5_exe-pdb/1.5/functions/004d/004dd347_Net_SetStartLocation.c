/*
 * Entry: 004dd347
 * Name: Net::SetStartLocation
 * Namespace: Net
 * Signature: void SetStartLocation(Net * this, VECTOR_3D * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Net::SetStartLocation(Net *this,VECTOR_3D *param_1)

{
  (this->start_location).x = param_1->x;
  (this->start_location).y = param_1->y;
  (this->start_location).z = param_1->z;
  return;
}
