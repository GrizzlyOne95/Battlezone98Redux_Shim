/*
 * Entry: 004a8510
 * Name: std::find<std::_Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>,PowerPlant_*>
 * Namespace: std
 * Signature: _Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_> find<std::_Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>,PowerPlant_*>(_Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_> param_1, _Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_> param_2, PowerPlant * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_> __cdecl
std::find<std::_Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_>,PowerPlant_*>
          (_Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_> param_1,
          _Vector_iterator<PowerPlant_*,std::allocator<PowerPlant_*>_> param_2,PowerPlant **param_3)

{
  PowerPlant **ppPVar1;
  PowerPlant **in_stack_00000018;
  
  ppPVar1 = _Find<PowerPlant_*_*,PowerPlant_*>
                      ((PowerPlant **)param_2._0_4_,param_3,in_stack_00000018);
  *(undefined4 *)param_1._0_4_ = param_1._4_4_;
  *(PowerPlant ***)(param_1._0_4_ + 4) = ppPVar1;
  return param_1;
}
