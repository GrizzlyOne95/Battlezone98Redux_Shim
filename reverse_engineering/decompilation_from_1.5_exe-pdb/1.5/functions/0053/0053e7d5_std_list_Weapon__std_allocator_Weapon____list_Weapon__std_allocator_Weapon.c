/*
 * Entry: 0053e7d5
 * Name: std::list<Weapon_*,std::allocator<Weapon_*>_>::list<Weapon_*,std::allocator<Weapon_*>_>
 * Namespace: std::list<Weapon_*,std::allocator<Weapon_*>_>
 * Signature: list<Weapon_*,std::allocator<Weapon_*>_> * list<Weapon_*,std::allocator<Weapon_*>_>(list<Weapon_*,std::allocator<Weapon_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

list<Weapon_*,std::allocator<Weapon_*>_> * __thiscall
std::list<Weapon_*,std::allocator<Weapon_*>_>::list<Weapon_*,std::allocator<Weapon_*>_>
          (list<Weapon_*,std::allocator<Weapon_*>_> *this)

{
  _Node *p_Var1;
  
  _List_val<Weapon_*,std::allocator<Weapon_*>_>::_List_val<Weapon_*,std::allocator<Weapon_*>_>
            ((_List_val<Weapon_*,std::allocator<Weapon_*>_> *)this,SUB41(this,0));
  p_Var1 = _Buynode(this);
  this->_Mysize = 0;
  this->_Myhead = p_Var1;
  return this;
}
