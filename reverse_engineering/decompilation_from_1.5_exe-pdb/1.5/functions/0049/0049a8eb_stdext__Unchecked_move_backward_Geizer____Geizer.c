/*
 * Entry: 0049a8eb
 * Name: stdext::_Unchecked_move_backward<Geizer_*_*,Geizer_*_*>
 * Namespace: stdext
 * Signature: Geizer * * _Unchecked_move_backward<Geizer_*_*,Geizer_*_*>(Geizer * * param_1, Geizer * * param_2, Geizer * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Geizer ** __cdecl
stdext::_Unchecked_move_backward<Geizer_*_*,Geizer_*_*>
          (Geizer **param_1,Geizer **param_2,Geizer **param_3)

{
  Geizer **ppGVar1;
  
  ppGVar1 = std::
            _Move_backward_opt<Geizer_*_*,Geizer_*_*,std::random_access_iterator_tag,std::_Undefined_move_tag>
                      (param_1,param_2,param_3,SUB41(param_2,0),
                       (_Undefined_move_tag)SUB41(param_2,0),(_Range_checked_iterator_tag)0x0);
  return ppGVar1;
}
