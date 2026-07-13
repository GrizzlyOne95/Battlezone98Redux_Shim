/*
 * Entry: 00490328
 * Name: DistributedObject::Remove
 * Namespace: DistributedObject
 * Signature: void Remove(DistributedObject * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall DistributedObject::Remove(DistributedObject *this)

{
  if (this->object_type == '\x02') {
    if (0xffff < this->dwLocalID) {
      return;
    }
  }
  else if (this->object_type != '\x01') {
    return;
  }
  Destroy(this);
  return;
}
