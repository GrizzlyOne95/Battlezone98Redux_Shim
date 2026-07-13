/*
 * Entry: 0048a23e
 * Name: DistributedObject::IsRemote
 * Namespace: DistributedObject
 * Signature: bool IsRemote(DistributedObject * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall DistributedObject::IsRemote(DistributedObject *this)

{
  return this->object_type == '\x02';
}
