/*
 * Entry: 0040e985
 * Name: std::list<AttackGroup_*,std::allocator<AttackGroup_*>_>::list<AttackGroup_*,std::allocator<AttackGroup_*>_>
 * Namespace: std::list<AttackGroup_*,std::allocator<AttackGroup_*>_>
 * Signature: list<AttackGroup_*,std::allocator<AttackGroup_*>_> * list<AttackGroup_*,std::allocator<AttackGroup_*>_>(list<AttackGroup_*,std::allocator<AttackGroup_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

list<AttackGroup_*,std::allocator<AttackGroup_*>_> * __thiscall
std::list<AttackGroup_*,std::allocator<AttackGroup_*>_>::
list<AttackGroup_*,std::allocator<AttackGroup_*>_>
          (list<AttackGroup_*,std::allocator<AttackGroup_*>_> *this)

{
  _Node *p_Var1;
  
  _List_val<AttackGroup_*,std::allocator<AttackGroup_*>_>::
  _List_val<AttackGroup_*,std::allocator<AttackGroup_*>_>
            ((_List_val<AttackGroup_*,std::allocator<AttackGroup_*>_> *)this,SUB41(this,0));
  p_Var1 = _Buynode(this);
  this->_Mysize = 0;
  this->_Myhead = p_Var1;
  return this;
}
