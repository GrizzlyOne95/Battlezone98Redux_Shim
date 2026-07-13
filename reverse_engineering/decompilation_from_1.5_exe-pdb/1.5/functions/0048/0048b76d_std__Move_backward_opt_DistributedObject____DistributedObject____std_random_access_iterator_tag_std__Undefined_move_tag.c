/*
 * Entry: 0048b76d
 * Name: std::_Move_backward_opt<DistributedObject_*_*,DistributedObject_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>
 * Namespace: std
 * Signature: DistributedObject * * _Move_backward_opt<DistributedObject_*_*,DistributedObject_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>(DistributedObject * * param_1, DistributedObject * * param_2, DistributedObject * * param_3, random_access_iterator_tag param_4, _Undefined_move_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

DistributedObject ** __cdecl
std::
_Move_backward_opt<DistributedObject_*_*,DistributedObject_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>
          (DistributedObject **param_1,DistributedObject **param_2,DistributedObject **param_3,
          random_access_iterator_tag param_4,_Undefined_move_tag param_5,
          _Range_checked_iterator_tag param_6)

{
  DistributedObject **ppDVar1;
  
  ppDVar1 = _Copy_backward_opt<DistributedObject_*_*,DistributedObject_*_*,std::random_access_iterator_tag>
                      (param_1,param_2,param_3,param_4,(_Scalar_ptr_iterator_tag)0x0,
                       (_Range_checked_iterator_tag)0x0);
  return ppDVar1;
}
