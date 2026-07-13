/*
 * Entry: 0048a248
 * Name: DistributedObject::IsLocal
 * Namespace: DistributedObject
 * Signature: bool IsLocal(DistributedObject * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall DistributedObject::IsLocal(DistributedObject *this)

{
  return this->object_type == '\x01';
}
