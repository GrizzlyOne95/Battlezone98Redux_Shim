/*
 * Entry: 0048c998
 * Name: std::_Uninit_fill_n<DistributedObject_*_*,unsigned_int,DistributedObject_*,std::allocator<DistributedObject_*>_>
 * Namespace: std
 * Signature: void _Uninit_fill_n<DistributedObject_*_*,unsigned_int,DistributedObject_*,std::allocator<DistributedObject_*>_>(DistributedObject * * param_1, uint param_2, DistributedObject * * param_3, allocator<DistributedObject_*> * param_4, _Scalar_ptr_iterator_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::
_Uninit_fill_n<DistributedObject_*_*,unsigned_int,DistributedObject_*,std::allocator<DistributedObject_*>_>
          (DistributedObject **param_1,uint param_2,DistributedObject **param_3,
          allocator<DistributedObject_*> *param_4,_Scalar_ptr_iterator_tag param_5,
          _Range_checked_iterator_tag param_6)

{
  stdext::unchecked_fill_n<DistributedObject_*_*,unsigned_int,DistributedObject_*>
            (param_1,param_2,param_3);
  return;
}
