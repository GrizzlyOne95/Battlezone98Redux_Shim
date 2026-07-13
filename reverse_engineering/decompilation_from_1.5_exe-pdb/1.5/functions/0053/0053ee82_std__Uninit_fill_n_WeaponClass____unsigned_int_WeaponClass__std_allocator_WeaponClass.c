/*
 * Entry: 0053ee82
 * Name: std::_Uninit_fill_n<WeaponClass_*_*,unsigned_int,WeaponClass_*,std::allocator<WeaponClass_*>_>
 * Namespace: std
 * Signature: void _Uninit_fill_n<WeaponClass_*_*,unsigned_int,WeaponClass_*,std::allocator<WeaponClass_*>_>(WeaponClass * * param_1, uint param_2, WeaponClass * * param_3, allocator<WeaponClass_*> * param_4, _Scalar_ptr_iterator_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Uninit_fill_n<WeaponClass_*_*,unsigned_int,WeaponClass_*,std::allocator<WeaponClass_*>_>
          (WeaponClass **param_1,uint param_2,WeaponClass **param_3,
          allocator<WeaponClass_*> *param_4,_Scalar_ptr_iterator_tag param_5,
          _Range_checked_iterator_tag param_6)

{
  stdext::unchecked_fill_n<WeaponClass_*_*,unsigned_int,WeaponClass_*>(param_1,param_2,param_3);
  return;
}
