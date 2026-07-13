/*
 * Entry: 0053ea84
 * Name: std::_Fill<WeaponClass_*_*,WeaponClass_*>
 * Namespace: std
 * Signature: void _Fill<WeaponClass_*_*,WeaponClass_*>(WeaponClass * * param_1, WeaponClass * * param_2, WeaponClass * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Fill<WeaponClass_*_*,WeaponClass_*>
          (WeaponClass **param_1,WeaponClass **param_2,WeaponClass **param_3)

{
  for (; param_1 != param_2; param_1 = param_1 + 1) {
    *param_1 = *param_3;
  }
  return;
}
