/*
 * Entry: 004acd1e
 * Name: Recycler::Recycler
 * Namespace: Recycler
 * Signature: Recycler * Recycler(Recycler * this, _OBJ76 * param_1, RecyclerClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Recycler * __thiscall Recycler::Recycler(Recycler *this,_OBJ76 *param_1,RecyclerClass *param_2)

{
  Producer::Producer((Producer *)this,param_1,(ProducerClass *)param_2);
  this->scrapDropoff = -1;
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  return this;
}
