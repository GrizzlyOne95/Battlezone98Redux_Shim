/*
 * Entry: 00489365
 * Name: std::_Uninit_fill_n<Craft_*_*,unsigned_int,Craft_*,std::allocator<Craft_*>_>
 * Namespace: std
 * Signature: void _Uninit_fill_n<Craft_*_*,unsigned_int,Craft_*,std::allocator<Craft_*>_>(Craft * * param_1, uint param_2, Craft * * param_3, allocator<Craft_*> * param_4, _Scalar_ptr_iterator_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Uninit_fill_n<Craft_*_*,unsigned_int,Craft_*,std::allocator<Craft_*>_>
          (Craft **param_1,uint param_2,Craft **param_3,allocator<Craft_*> *param_4,
          _Scalar_ptr_iterator_tag param_5,_Range_checked_iterator_tag param_6)

{
  stdext::unchecked_fill_n<Craft_*_*,unsigned_int,Craft_*>(param_1,param_2,param_3);
  return;
}
