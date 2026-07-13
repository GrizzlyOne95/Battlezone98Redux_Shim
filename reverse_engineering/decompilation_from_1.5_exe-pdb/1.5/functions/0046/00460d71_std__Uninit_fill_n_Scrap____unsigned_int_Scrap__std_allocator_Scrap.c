/*
 * Entry: 00460d71
 * Name: std::_Uninit_fill_n<Scrap_*_*,unsigned_int,Scrap_*,std::allocator<Scrap_*>_>
 * Namespace: std
 * Signature: void _Uninit_fill_n<Scrap_*_*,unsigned_int,Scrap_*,std::allocator<Scrap_*>_>(Scrap * * param_1, uint param_2, Scrap * * param_3, allocator<Scrap_*> * param_4, _Scalar_ptr_iterator_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Uninit_fill_n<Scrap_*_*,unsigned_int,Scrap_*,std::allocator<Scrap_*>_>
          (Scrap **param_1,uint param_2,Scrap **param_3,allocator<Scrap_*> *param_4,
          _Scalar_ptr_iterator_tag param_5,_Range_checked_iterator_tag param_6)

{
  stdext::unchecked_fill_n<Scrap_*_*,unsigned_int,Scrap_*>(param_1,param_2,param_3);
  return;
}
