/*
 * Entry: 004a845d
 * Name: std::_Uninit_move<PowerPlant_*_*,PowerPlant_*_*,std::allocator<PowerPlant_*>,std::_Undefined_move_tag>
 * Namespace: std
 * Signature: PowerPlant * * _Uninit_move<PowerPlant_*_*,PowerPlant_*_*,std::allocator<PowerPlant_*>,std::_Undefined_move_tag>(PowerPlant * * param_1, PowerPlant * * param_2, PowerPlant * * param_3, allocator<PowerPlant_*> * param_4, _Undefined_move_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PowerPlant ** __cdecl
std::
_Uninit_move<PowerPlant_*_*,PowerPlant_*_*,std::allocator<PowerPlant_*>,std::_Undefined_move_tag>
          (PowerPlant **param_1,PowerPlant **param_2,PowerPlant **param_3,
          allocator<PowerPlant_*> *param_4,_Undefined_move_tag param_5,
          _Range_checked_iterator_tag param_6)

{
  PowerPlant **ppPVar1;
  
  ppPVar1 = stdext::
            unchecked_uninitialized_copy<PowerPlant_*_*,PowerPlant_*_*,std::allocator<PowerPlant_*>_>
                      (param_1,param_2,param_3,param_4);
  return ppPVar1;
}
