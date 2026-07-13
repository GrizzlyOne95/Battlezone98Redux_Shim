/*
 * Entry: 00555952
 * Name: std::_Uninit_copy<Player_*_*,Player_*_*,std::allocator<Player_*>_>
 * Namespace: std
 * Signature: Player * * _Uninit_copy<Player_*_*,Player_*_*,std::allocator<Player_*>_>(Player * * param_1, Player * * param_2, Player * * param_3, allocator<Player_*> * param_4, _Scalar_ptr_iterator_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Player ** __cdecl
std::_Uninit_copy<Player_*_*,Player_*_*,std::allocator<Player_*>_>
          (Player **param_1,Player **param_2,Player **param_3,allocator<Player_*> *param_4,
          _Scalar_ptr_iterator_tag param_5,_Range_checked_iterator_tag param_6)

{
  int iVar1;
  
  iVar1 = (int)param_2 - (int)param_1 >> 2;
  if (iVar1 != 0) {
    memmove_s(param_3,iVar1 * 4,param_1,iVar1 * 4);
  }
  return param_3 + iVar1;
}
