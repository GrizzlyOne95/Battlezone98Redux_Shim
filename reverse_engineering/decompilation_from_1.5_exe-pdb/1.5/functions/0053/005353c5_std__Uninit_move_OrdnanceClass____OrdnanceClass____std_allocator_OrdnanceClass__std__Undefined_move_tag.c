/*
 * Entry: 005353c5
 * Name: std::_Uninit_move<OrdnanceClass_*_*,OrdnanceClass_*_*,std::allocator<OrdnanceClass_*>,std::_Undefined_move_tag>
 * Namespace: std
 * Signature: OrdnanceClass * * _Uninit_move<OrdnanceClass_*_*,OrdnanceClass_*_*,std::allocator<OrdnanceClass_*>,std::_Undefined_move_tag>(OrdnanceClass * * param_1, OrdnanceClass * * param_2, OrdnanceClass * * param_3, allocator<OrdnanceClass_*> * param_4, _Undefined_move_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

OrdnanceClass ** __cdecl
std::
_Uninit_move<OrdnanceClass_*_*,OrdnanceClass_*_*,std::allocator<OrdnanceClass_*>,std::_Undefined_move_tag>
          (OrdnanceClass **param_1,OrdnanceClass **param_2,OrdnanceClass **param_3,
          allocator<OrdnanceClass_*> *param_4,_Undefined_move_tag param_5,
          _Range_checked_iterator_tag param_6)

{
  OrdnanceClass **ppOVar1;
  
  ppOVar1 = stdext::
            unchecked_uninitialized_copy<OrdnanceClass_*_*,OrdnanceClass_*_*,std::allocator<OrdnanceClass_*>_>
                      (param_1,param_2,param_3,param_4);
  return ppOVar1;
}
