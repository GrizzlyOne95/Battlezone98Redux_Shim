/*
 * Entry: 0048a252
 * Name: DistributedObject::GetID
 * Namespace: DistributedObject
 * Signature: ulong GetID(DistributedObject * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ulong __thiscall DistributedObject::GetID(DistributedObject *this)

{
  return this->dwLocalID;
}
