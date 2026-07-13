/*
 * Entry: 0053e2df
 * Name: std::allocator<Weapon_*>::construct
 * Namespace: std::allocator<Weapon_*>
 * Signature: void construct(allocator<Weapon_*> * this, Weapon * * param_1, Weapon * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::allocator<Weapon_*>::construct(allocator<Weapon_*> *this,Weapon **param_1,Weapon **param_2)

{
  if (param_1 != (Weapon **)0x0) {
    *param_1 = *param_2;
  }
  return;
}
