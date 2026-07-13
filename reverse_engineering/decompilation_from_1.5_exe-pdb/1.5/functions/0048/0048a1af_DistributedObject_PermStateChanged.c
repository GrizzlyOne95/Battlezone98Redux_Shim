/*
 * Entry: 0048a1af
 * Name: DistributedObject::PermStateChanged
 * Namespace: DistributedObject
 * Signature: bool PermStateChanged(DistributedObject * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall DistributedObject::PermStateChanged(DistributedObject *this,float param_1)

{
  bool bVar1;
  
  if (param_1 < this->last_send_time) {
    this->last_send_time = param_1;
  }
  if ((this->dirty != false) || (this->last_send_time + 60.0 < param_1)) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  return bVar1;
}
