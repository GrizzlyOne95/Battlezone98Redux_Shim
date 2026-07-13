/*
 * Entry: 004a8408
 * Name: stdext::_Unchecked_move_backward<PowerPlant_*_*,PowerPlant_*_*>
 * Namespace: stdext
 * Signature: PowerPlant * * _Unchecked_move_backward<PowerPlant_*_*,PowerPlant_*_*>(PowerPlant * * param_1, PowerPlant * * param_2, PowerPlant * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PowerPlant ** __cdecl
stdext::_Unchecked_move_backward<PowerPlant_*_*,PowerPlant_*_*>
          (PowerPlant **param_1,PowerPlant **param_2,PowerPlant **param_3)

{
  PowerPlant **ppPVar1;
  
  ppPVar1 = std::
            _Move_backward_opt<PowerPlant_*_*,PowerPlant_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>
                      (param_1,param_2,param_3,SUB41(param_2,0),
                       (_Undefined_move_tag)SUB41(param_2,0),(_Range_checked_iterator_tag)0x0);
  return ppPVar1;
}
