/*
 * Entry: 0053e758
 * Name: Weapon::~Weapon
 * Namespace: Weapon
 * Signature: void ~Weapon(Weapon * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Weapon::~Weapon(Weapon *this)

{
  _Const_iterator<1> _Var1;
  bool bVar2;
  Weapon **ppWVar3;
  _Const_iterator<1> local_14;
  _Const_iterator<1> local_c;
  
  this->_padding_ = (int)&_vftable_;
  std::list<Weapon_*,std::allocator<Weapon_*>_>::_Const_iterator<1>::_Const_iterator<1>
            (&local_14,(weaponList._Myhead)->_Next,&weaponList);
  local_c._padding_ = local_14._padding_;
  local_c._Ptr = local_14._Ptr;
  while( true ) {
    std::list<Weapon_*,std::allocator<Weapon_*>_>::_Const_iterator<1>::_Const_iterator<1>
              (&local_14,weaponList._Myhead,&weaponList);
    bVar2 = std::list<Weapon_*,std::allocator<Weapon_*>_>::_Const_iterator<1>::operator==
                      (&local_c,&local_14);
    if (bVar2) {
      return;
    }
    ppWVar3 = std::list<Weapon_*,std::allocator<Weapon_*>_>::_Const_iterator<1>::operator*(&local_c)
    ;
    if (this == *ppWVar3) break;
    std::list<Weapon_*,std::allocator<Weapon_*>_>::_Const_iterator<1>::operator++(&local_c);
  }
  _Var1._Ptr = (_Node *)local_c._padding_;
  _Var1._padding_ = (int)&local_14;
  std::list<Weapon_*,std::allocator<Weapon_*>_>::erase(&weaponList,_Var1);
  return;
}
