/*
 * Entry: 0053e497
 * Name: std::list<Weapon_*,std::allocator<Weapon_*>_>::_Make_iter
 * Namespace: std::list<Weapon_*,std::allocator<Weapon_*>_>
 * Signature: _Iterator<1> _Make_iter(list<Weapon_*,std::allocator<Weapon_*>_> * this, _Const_iterator<1> param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Iterator<1> __thiscall
std::list<Weapon_*,std::allocator<Weapon_*>_>::_Make_iter
          (list<Weapon_*,std::allocator<Weapon_*>_> *this,_Const_iterator<1> param_1)

{
  undefined4 extraout_EDX;
  _Iterator<1> _Var1;
  _Node *in_stack_0000000c;
  
  _Const_iterator<1>::_Const_iterator<1>
            ((_Const_iterator<1> *)param_1._padding_,in_stack_0000000c,this);
  _Var1._4_4_ = extraout_EDX;
  _Var1._0_4_ = param_1._padding_;
  return _Var1;
}
