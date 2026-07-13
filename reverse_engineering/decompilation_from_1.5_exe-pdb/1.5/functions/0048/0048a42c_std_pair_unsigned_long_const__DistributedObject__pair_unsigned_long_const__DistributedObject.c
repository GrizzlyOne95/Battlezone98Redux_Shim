/*
 * Entry: 0048a42c
 * Name: std::pair<unsigned_long_const_,DistributedObject_*>::pair<unsigned_long_const_,DistributedObject_*>
 * Namespace: std::pair<unsigned_long_const_,DistributedObject_*>
 * Signature: pair<unsigned_long_const_,DistributedObject_*> * pair<unsigned_long_const_,DistributedObject_*>(pair<unsigned_long_const_,DistributedObject_*> * this, ulong * param_1, DistributedObject * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

pair<unsigned_long_const_,DistributedObject_*> * __thiscall
std::pair<unsigned_long_const_,DistributedObject_*>::pair<unsigned_long_const_,DistributedObject_*>
          (pair<unsigned_long_const_,DistributedObject_*> *this,ulong *param_1,
          DistributedObject **param_2)

{
  this->first = *param_1;
  this->second = *param_2;
  return this;
}
