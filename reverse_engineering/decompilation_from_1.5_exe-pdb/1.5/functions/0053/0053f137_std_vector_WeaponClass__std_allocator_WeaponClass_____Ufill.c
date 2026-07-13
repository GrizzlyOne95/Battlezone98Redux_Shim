/*
 * Entry: 0053f137
 * Name: std::vector<WeaponClass_*,std::allocator<WeaponClass_*>_>::_Ufill
 * Namespace: std::vector<WeaponClass_*,std::allocator<WeaponClass_*>_>
 * Signature: WeaponClass * * _Ufill(vector<WeaponClass_*,std::allocator<WeaponClass_*>_> * this, WeaponClass * * param_1, uint param_2, WeaponClass * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

WeaponClass ** __thiscall
std::vector<WeaponClass_*,std::allocator<WeaponClass_*>_>::_Ufill
          (vector<WeaponClass_*,std::allocator<WeaponClass_*>_> *this,WeaponClass **param_1,
          uint param_2,WeaponClass **param_3)

{
  stdext::unchecked_fill_n<WeaponClass_*_*,unsigned_int,WeaponClass_*>(param_1,param_2,param_3);
  return param_1 + param_2;
}
