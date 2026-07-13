/*
 * Entry: 0048c0d2
 * Name: stdext::unchecked_copy<DistributedObject_*_*,DistributedObject_*_*>
 * Namespace: stdext
 * Signature: DistributedObject * * unchecked_copy<DistributedObject_*_*,DistributedObject_*_*>(DistributedObject * * param_1, DistributedObject * * param_2, DistributedObject * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

DistributedObject ** __cdecl
stdext::unchecked_copy<DistributedObject_*_*,DistributedObject_*_*>
          (DistributedObject **param_1,DistributedObject **param_2,DistributedObject **param_3)

{
  DistributedObject **ppDVar1;
  
  ppDVar1 = std::
            _Copy_opt<DistributedObject_*_*,DistributedObject_*_*,std::random_access_iterator_tag>
                      (param_1,param_2,param_3,SUB41(param_2,0),
                       (_Scalar_ptr_iterator_tag)SUB41(param_2,0),(_Range_checked_iterator_tag)0x0);
  return ppDVar1;
}
