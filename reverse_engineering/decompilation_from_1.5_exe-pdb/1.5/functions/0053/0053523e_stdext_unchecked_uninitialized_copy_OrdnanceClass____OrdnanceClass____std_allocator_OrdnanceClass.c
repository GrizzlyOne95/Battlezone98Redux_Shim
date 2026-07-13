/*
 * Entry: 0053523e
 * Name: stdext::unchecked_uninitialized_copy<OrdnanceClass_*_*,OrdnanceClass_*_*,std::allocator<OrdnanceClass_*>_>
 * Namespace: stdext
 * Signature: OrdnanceClass * * unchecked_uninitialized_copy<OrdnanceClass_*_*,OrdnanceClass_*_*,std::allocator<OrdnanceClass_*>_>(OrdnanceClass * * param_1, OrdnanceClass * * param_2, OrdnanceClass * * param_3, allocator<OrdnanceClass_*> * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

OrdnanceClass ** __cdecl
stdext::
unchecked_uninitialized_copy<OrdnanceClass_*_*,OrdnanceClass_*_*,std::allocator<OrdnanceClass_*>_>
          (OrdnanceClass **param_1,OrdnanceClass **param_2,OrdnanceClass **param_3,
          allocator<OrdnanceClass_*> *param_4)

{
  OrdnanceClass **ppOVar1;
  
  ppOVar1 = std::_Uninit_copy<OrdnanceClass_*_*,OrdnanceClass_*_*,std::allocator<OrdnanceClass_*>_>
                      (param_1,param_2,param_3,param_4,SUB41(param_2,0),
                       (_Range_checked_iterator_tag)0x0);
  return ppOVar1;
}
