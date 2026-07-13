/*
 * Entry: 0055841b
 * Name: std::_Uninit_fill_n<Player_*_*,unsigned_int,Player_*,std::allocator<Player_*>_>
 * Namespace: std
 * Signature: void _Uninit_fill_n<Player_*_*,unsigned_int,Player_*,std::allocator<Player_*>_>(Player * * param_1, uint param_2, Player * * param_3, allocator<Player_*> * param_4, _Scalar_ptr_iterator_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Uninit_fill_n<Player_*_*,unsigned_int,Player_*,std::allocator<Player_*>_>
          (Player **param_1,uint param_2,Player **param_3,allocator<Player_*> *param_4,
          _Scalar_ptr_iterator_tag param_5,_Range_checked_iterator_tag param_6)

{
  stdext::unchecked_fill_n<Player_*_*,unsigned_int,Player_*>(param_1,param_2,param_3);
  return;
}
