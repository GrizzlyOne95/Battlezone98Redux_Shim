/*
 * Entry: 004a8548
 * Name: stdext::_Unchecked_uninitialized_move<PowerPlant_*_*,PowerPlant_*_*,std::allocator<PowerPlant_*>_>
 * Namespace: stdext
 * Signature: PowerPlant * * _Unchecked_uninitialized_move<PowerPlant_*_*,PowerPlant_*_*,std::allocator<PowerPlant_*>_>(PowerPlant * * param_1, PowerPlant * * param_2, PowerPlant * * param_3, allocator<PowerPlant_*> * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PowerPlant ** __cdecl
stdext::_Unchecked_uninitialized_move<PowerPlant_*_*,PowerPlant_*_*,std::allocator<PowerPlant_*>_>
          (PowerPlant **param_1,PowerPlant **param_2,PowerPlant **param_3,
          allocator<PowerPlant_*> *param_4)

{
  PowerPlant **ppPVar1;
  
  ppPVar1 = std::_Uninit_copy<PowerPlant_*_*,PowerPlant_*_*,std::allocator<PowerPlant_*>_>
                      (param_1,param_2,param_3,param_4,SUB41(param_2,0),
                       (_Range_checked_iterator_tag)0x0);
  return ppPVar1;
}
