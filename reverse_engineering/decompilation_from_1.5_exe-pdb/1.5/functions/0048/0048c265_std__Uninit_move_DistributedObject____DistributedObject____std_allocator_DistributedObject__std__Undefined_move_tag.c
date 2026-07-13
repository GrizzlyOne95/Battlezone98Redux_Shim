/*
 * Entry: 0048c265
 * Name: std::_Uninit_move<DistributedObject_*_*,DistributedObject_*_*,std::allocator<DistributedObject_*>,std::_Undefined_move_tag>
 * Namespace: std
 * Signature: DistributedObject * * _Uninit_move<DistributedObject_*_*,DistributedObject_*_*,std::allocator<DistributedObject_*>,std::_Undefined_move_tag>(DistributedObject * * param_1, DistributedObject * * param_2, DistributedObject * * param_3, allocator<DistributedObject_*> * param_4, _Undefined_move_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

DistributedObject ** __cdecl
std::
_Uninit_move<DistributedObject_*_*,DistributedObject_*_*,std::allocator<DistributedObject_*>,std::_Undefined_move_tag>
          (DistributedObject **param_1,DistributedObject **param_2,DistributedObject **param_3,
          allocator<DistributedObject_*> *param_4,_Undefined_move_tag param_5,
          _Range_checked_iterator_tag param_6)

{
  DistributedObject **ppDVar1;
  
  ppDVar1 = stdext::
            unchecked_uninitialized_copy<DistributedObject_*_*,DistributedObject_*_*,std::allocator<DistributedObject_*>_>
                      (param_1,param_2,param_3,param_4);
  return ppDVar1;
}
