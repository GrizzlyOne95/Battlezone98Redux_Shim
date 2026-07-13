/*
 * Entry: 0053eee1
 * Name: stdext::unchecked_uninitialized_fill_n<WeaponClass_*_*,unsigned_int,WeaponClass_*,std::allocator<WeaponClass_*>_>
 * Namespace: stdext
 * Signature: void unchecked_uninitialized_fill_n<WeaponClass_*_*,unsigned_int,WeaponClass_*,std::allocator<WeaponClass_*>_>(WeaponClass * * param_1, uint param_2, WeaponClass * * param_3, allocator<WeaponClass_*> * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
stdext::
unchecked_uninitialized_fill_n<WeaponClass_*_*,unsigned_int,WeaponClass_*,std::allocator<WeaponClass_*>_>
          (WeaponClass **param_1,uint param_2,WeaponClass **param_3,
          allocator<WeaponClass_*> *param_4)

{
  unchecked_fill_n<WeaponClass_*_*,unsigned_int,WeaponClass_*>(param_1,param_2,param_3);
  return;
}
