/*
 * Entry: 0053e587
 * Name: Weapon_SimulateAll
 * Namespace: Global
 * Signature: void Weapon_SimulateAll(float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Weapon_SimulateAll(float param_1)

{
  bool bVar1;
  Weapon **ppWVar2;
  _Const_iterator<1> local_14;
  _Const_iterator<1> local_c;
  
  std::list<Weapon_*,std::allocator<Weapon_*>_>::_Const_iterator<1>::_Const_iterator<1>
            (&local_14,(Weapon::weaponList._Myhead)->_Next,&Weapon::weaponList);
  local_c._padding_ = local_14._padding_;
  local_c._Ptr = local_14._Ptr;
  while( true ) {
    std::list<Weapon_*,std::allocator<Weapon_*>_>::_Const_iterator<1>::_Const_iterator<1>
              (&local_14,Weapon::weaponList._Myhead,&Weapon::weaponList);
    bVar1 = std::list<Weapon_*,std::allocator<Weapon_*>_>::_Const_iterator<1>::operator==
                      (&local_c,&local_14);
    if (bVar1) break;
    ppWVar2 = std::list<Weapon_*,std::allocator<Weapon_*>_>::_Const_iterator<1>::operator*(&local_c)
    ;
    if ((*ppWVar2)->obj->gravestone == 0) {
      (**(code **)((*ppWVar2)->_padding_ + 0x18))(param_1);
    }
    std::list<Weapon_*,std::allocator<Weapon_*>_>::_Const_iterator<1>::operator++(&local_c);
  }
  return;
}
