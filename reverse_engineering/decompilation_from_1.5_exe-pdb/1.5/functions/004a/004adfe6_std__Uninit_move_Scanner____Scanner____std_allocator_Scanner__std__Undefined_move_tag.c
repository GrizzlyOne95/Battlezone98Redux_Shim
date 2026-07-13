/*
 * Entry: 004adfe6
 * Name: std::_Uninit_move<Scanner_*_*,Scanner_*_*,std::allocator<Scanner_*>,std::_Undefined_move_tag>
 * Namespace: std
 * Signature: Scanner * * _Uninit_move<Scanner_*_*,Scanner_*_*,std::allocator<Scanner_*>,std::_Undefined_move_tag>(Scanner * * param_1, Scanner * * param_2, Scanner * * param_3, allocator<Scanner_*> * param_4, _Undefined_move_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Scanner ** __cdecl
std::_Uninit_move<Scanner_*_*,Scanner_*_*,std::allocator<Scanner_*>,std::_Undefined_move_tag>
          (Scanner **param_1,Scanner **param_2,Scanner **param_3,allocator<Scanner_*> *param_4,
          _Undefined_move_tag param_5,_Range_checked_iterator_tag param_6)

{
  Scanner **ppSVar1;
  
  ppSVar1 = stdext::unchecked_uninitialized_copy<Scanner_*_*,Scanner_*_*,std::allocator<Scanner_*>_>
                      (param_1,param_2,param_3,param_4);
  return ppSVar1;
}
