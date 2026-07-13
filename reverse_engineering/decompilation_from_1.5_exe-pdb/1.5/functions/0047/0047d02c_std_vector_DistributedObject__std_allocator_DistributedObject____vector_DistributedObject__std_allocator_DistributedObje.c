/*
 * Entry: 0047d02c
 * Name: std::vector<DistributedObject_*,std::allocator<DistributedObject_*>_>::vector<DistributedObject_*,std::allocator<DistributedObject_*>_>
 * Namespace: std::vector<DistributedObject_*,std::allocator<DistributedObject_*>_>
 * Signature: vector<DistributedObject_*,std::allocator<DistributedObject_*>_> * vector<DistributedObject_*,std::allocator<DistributedObject_*>_>(vector<DistributedObject_*,std::allocator<DistributedObject_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

vector<DistributedObject_*,std::allocator<DistributedObject_*>_> * __thiscall
std::vector<DistributedObject_*,std::allocator<DistributedObject_*>_>::
vector<DistributedObject_*,std::allocator<DistributedObject_*>_>
          (vector<DistributedObject_*,std::allocator<DistributedObject_*>_> *this)

{
  _Vector_val<DistributedObject_*,std::allocator<DistributedObject_*>_>::
  _Vector_val<DistributedObject_*,std::allocator<DistributedObject_*>_>
            ((_Vector_val<DistributedObject_*,std::allocator<DistributedObject_*>_> *)this,
             SUB41(this,0));
  _Buy(this,0);
  return this;
}
