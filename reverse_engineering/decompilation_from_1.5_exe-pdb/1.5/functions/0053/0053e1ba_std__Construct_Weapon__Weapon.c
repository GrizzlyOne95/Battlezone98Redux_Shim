/*
 * Entry: 0053e1ba
 * Name: std::_Construct<Weapon_*,Weapon_*>
 * Namespace: std
 * Signature: void _Construct<Weapon_*,Weapon_*>(Weapon * * param_1, Weapon * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl std::_Construct<Weapon_*,Weapon_*>(Weapon **param_1,Weapon **param_2)

{
  if (param_1 != (Weapon **)0x0) {
    *param_1 = *param_2;
  }
  return;
}
