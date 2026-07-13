/*
 * Entry: 0053e36c
 * Name: std::list<Weapon_*,std::allocator<Weapon_*>_>::_Iterator<1>::_Iterator<1>
 * Namespace: std::list<Weapon_*,std::allocator<Weapon_*>_>::_Iterator<1>
 * Signature: _Iterator<1> * _Iterator<1>(_Iterator<1> * this, _Node * param_1, list<Weapon_*,std::allocator<Weapon_*>_> * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Iterator<1> * __thiscall
std::list<Weapon_*,std::allocator<Weapon_*>_>::_Iterator<1>::_Iterator<1>
          (_Iterator<1> *this,_Node *param_1,list<Weapon_*,std::allocator<Weapon_*>_> *param_2)

{
  list<Weapon_*,std::allocator<Weapon_*>_>::_Const_iterator<1>::_Const_iterator<1>
            ((_Const_iterator<1> *)this,param_1,param_2);
  return this;
}
