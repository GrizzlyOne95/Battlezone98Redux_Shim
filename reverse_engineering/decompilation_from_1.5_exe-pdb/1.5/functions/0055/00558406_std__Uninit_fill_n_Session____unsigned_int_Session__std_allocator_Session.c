/*
 * Entry: 00558406
 * Name: std::_Uninit_fill_n<Session_*_*,unsigned_int,Session_*,std::allocator<Session_*>_>
 * Namespace: std
 * Signature: void _Uninit_fill_n<Session_*_*,unsigned_int,Session_*,std::allocator<Session_*>_>(Session * * param_1, uint param_2, Session * * param_3, allocator<Session_*> * param_4, _Scalar_ptr_iterator_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Uninit_fill_n<Session_*_*,unsigned_int,Session_*,std::allocator<Session_*>_>
          (Session **param_1,uint param_2,Session **param_3,allocator<Session_*> *param_4,
          _Scalar_ptr_iterator_tag param_5,_Range_checked_iterator_tag param_6)

{
  stdext::unchecked_fill_n<Session_*_*,unsigned_int,Session_*>(param_1,param_2,param_3);
  return;
}
