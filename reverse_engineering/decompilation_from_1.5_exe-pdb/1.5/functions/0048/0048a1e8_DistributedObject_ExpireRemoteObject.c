/*
 * Entry: 0048a1e8
 * Name: DistributedObject::ExpireRemoteObject
 * Namespace: DistributedObject
 * Signature: bool ExpireRemoteObject(DistributedObject * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall DistributedObject::ExpireRemoteObject(DistributedObject *this,float param_1)

{
  return this->flast_received_time + 30.0 < param_1;
}
