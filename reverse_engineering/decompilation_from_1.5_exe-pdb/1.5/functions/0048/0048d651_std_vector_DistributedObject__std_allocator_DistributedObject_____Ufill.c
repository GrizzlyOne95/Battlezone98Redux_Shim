/*
 * Entry: 0048d651
 * Name: std::vector<DistributedObject_*,std::allocator<DistributedObject_*>_>::_Ufill
 * Namespace: std::vector<DistributedObject_*,std::allocator<DistributedObject_*>_>
 * Signature: DistributedObject * * _Ufill(vector<DistributedObject_*,std::allocator<DistributedObject_*>_> * this, DistributedObject * * param_1, uint param_2, DistributedObject * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

DistributedObject ** __thiscall
std::vector<DistributedObject_*,std::allocator<DistributedObject_*>_>::_Ufill
          (vector<DistributedObject_*,std::allocator<DistributedObject_*>_> *this,
          DistributedObject **param_1,uint param_2,DistributedObject **param_3)

{
  stdext::unchecked_fill_n<DistributedObject_*_*,unsigned_int,DistributedObject_*>
            (param_1,param_2,param_3);
  return param_1 + param_2;
}
