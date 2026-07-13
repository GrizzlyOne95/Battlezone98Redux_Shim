/*
 * Entry: 0053e25f
 * Name: std::list<Weapon_*,std::allocator<Weapon_*>_>::clear
 * Namespace: std::list<Weapon_*,std::allocator<Weapon_*>_>
 * Signature: void clear(list<Weapon_*,std::allocator<Weapon_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::list<Weapon_*,std::allocator<Weapon_*>_>::clear(list<Weapon_*,std::allocator<Weapon_*>_> *this)

{
  _Node *p_Var1;
  _Node *p_Var2;
  
  p_Var1 = this->_Myhead;
  p_Var2 = p_Var1->_Next;
  p_Var1->_Next = p_Var1;
  this->_Myhead->_Prev = this->_Myhead;
  this->_Mysize = 0;
  if (p_Var2 != this->_Myhead) {
    do {
      p_Var1 = p_Var2->_Next;
      operator_delete(p_Var2);
      p_Var2 = p_Var1;
    } while (p_Var1 != this->_Myhead);
  }
  return;
}
