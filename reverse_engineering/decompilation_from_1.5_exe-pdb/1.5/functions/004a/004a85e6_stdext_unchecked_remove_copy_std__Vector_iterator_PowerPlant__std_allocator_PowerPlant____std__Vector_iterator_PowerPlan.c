/*
 * Entry: 004a85e6
 * Name: stdext::unchecked_remove_copy<std::_Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>,std::_Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>,PowerPlant_*>
 * Namespace: stdext
 * Signature: _Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_> unchecked_remove_copy<std::_Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>,std::_Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>,PowerPlant_*>(_Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_> param_1, _Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_> param_2, _Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_> param_3, PowerPlant * * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_> __cdecl
stdext::
unchecked_remove_copy<std::_Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>,std::_Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>,PowerPlant_*>
          (_Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_> param_1,
          _Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_> param_2,
          _Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_> param_3,PowerPlant **param_4)

{
  _Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_> _Var1;
  _Range_checked_iterator_tag in_stack_00000020;
  
  _Var1 = std::
          _Remove_copy<PowerPlant_*_*,std::_Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>,PowerPlant_*>
                    ((PowerPlant **)param_1._0_4_,(PowerPlant **)param_2._0_4_,param_3,param_4,
                     in_stack_00000020);
  _Var1._0_4_ = param_1._0_4_;
  return _Var1;
}
