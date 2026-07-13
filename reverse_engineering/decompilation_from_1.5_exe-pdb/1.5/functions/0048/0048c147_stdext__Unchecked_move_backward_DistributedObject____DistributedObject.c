/*
 * Entry: 0048c147
 * Name: stdext::_Unchecked_move_backward<DistributedObject_*_*,DistributedObject_*_*>
 * Namespace: stdext
 * Signature: DistributedObject * * _Unchecked_move_backward<DistributedObject_*_*,DistributedObject_*_*>(DistributedObject * * param_1, DistributedObject * * param_2, DistributedObject * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

DistributedObject ** __cdecl
stdext::_Unchecked_move_backward<DistributedObject_*_*,DistributedObject_*_*>
          (DistributedObject **param_1,DistributedObject **param_2,DistributedObject **param_3)

{
  DistributedObject **ppDVar1;
  
  ppDVar1 = std::
            _Move_backward_opt<DistributedObject_*_*,DistributedObject_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>
                      (param_1,param_2,param_3,SUB41(param_2,0),
                       (_Undefined_move_tag)SUB41(param_2,0),(_Range_checked_iterator_tag)0x0);
  return ppDVar1;
}
