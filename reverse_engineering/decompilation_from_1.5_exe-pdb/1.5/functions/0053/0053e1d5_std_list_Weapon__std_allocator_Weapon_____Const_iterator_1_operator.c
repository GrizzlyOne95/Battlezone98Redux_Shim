/*
 * Entry: 0053e1d5
 * Name: std::list<Weapon_*,std::allocator<Weapon_*>_>::_Const_iterator<1>::operator!=
 * Namespace: std::list<Weapon_*,std::allocator<Weapon_*>_>::_Const_iterator<1>
 * Signature: bool operator!=(_Const_iterator<1> * this, _Const_iterator<1> * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::list<Weapon_*,std::allocator<Weapon_*>_>::_Const_iterator<1>::operator!=
          (_Const_iterator<1> *this,_Const_iterator<1> *param_1)

{
  bool bVar1;
  
  bVar1 = operator==(this,param_1);
  return !bVar1;
}
