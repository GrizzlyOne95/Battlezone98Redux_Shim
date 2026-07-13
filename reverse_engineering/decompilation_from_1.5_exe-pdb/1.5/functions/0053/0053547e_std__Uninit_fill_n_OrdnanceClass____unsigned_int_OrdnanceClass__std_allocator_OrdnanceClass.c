/*
 * Entry: 0053547e
 * Name: std::_Uninit_fill_n<OrdnanceClass_*_*,unsigned_int,OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>
 * Namespace: std
 * Signature: void _Uninit_fill_n<OrdnanceClass_*_*,unsigned_int,OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>(OrdnanceClass * * param_1, uint param_2, OrdnanceClass * * param_3, allocator<OrdnanceClass_*> * param_4, _Scalar_ptr_iterator_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Uninit_fill_n<OrdnanceClass_*_*,unsigned_int,OrdnanceClass_*,std::allocator<OrdnanceClass_*>_>
          (OrdnanceClass **param_1,uint param_2,OrdnanceClass **param_3,
          allocator<OrdnanceClass_*> *param_4,_Scalar_ptr_iterator_tag param_5,
          _Range_checked_iterator_tag param_6)

{
  stdext::unchecked_fill_n<OrdnanceClass_*_*,unsigned_int,OrdnanceClass_*>(param_1,param_2,param_3);
  return;
}
