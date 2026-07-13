/*
 * Entry: 00555922
 * Name: std::_Uninit_copy<Session_*_*,Session_*_*,std::allocator<Session_*>_>
 * Namespace: std
 * Signature: Session * * _Uninit_copy<Session_*_*,Session_*_*,std::allocator<Session_*>_>(Session * * param_1, Session * * param_2, Session * * param_3, allocator<Session_*> * param_4, _Scalar_ptr_iterator_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Session ** __cdecl
std::_Uninit_copy<Session_*_*,Session_*_*,std::allocator<Session_*>_>
          (Session **param_1,Session **param_2,Session **param_3,allocator<Session_*> *param_4,
          _Scalar_ptr_iterator_tag param_5,_Range_checked_iterator_tag param_6)

{
  int iVar1;
  
  iVar1 = (int)param_2 - (int)param_1 >> 2;
  if (iVar1 != 0) {
    memmove_s(param_3,iVar1 * 4,param_1,iVar1 * 4);
  }
  return param_3 + iVar1;
}
