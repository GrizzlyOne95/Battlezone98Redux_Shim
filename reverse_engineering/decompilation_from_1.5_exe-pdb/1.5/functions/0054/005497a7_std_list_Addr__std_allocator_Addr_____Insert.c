/*
 * Entry: 005497a7
 * Name: std::list<Addr_*,std::allocator<Addr_*>_>::_Insert
 * Namespace: std::list<Addr_*,std::allocator<Addr_*>_>
 * Signature: void _Insert(list<Addr_*,std::allocator<Addr_*>_> * this, _Const_iterator<1> param_1, Addr * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::list<Addr_*,std::allocator<Addr_*>_>::_Insert
          (list<Addr_*,std::allocator<Addr_*>_> *this,_Const_iterator<1> param_1,Addr **param_2)

{
  _Node *p_Var1;
  
  p_Var1 = _Buynode(this,param_1._Ptr,(param_1._Ptr)->_Prev,param_2);
  _Incsize(this,1);
  (param_1._Ptr)->_Prev = p_Var1;
  p_Var1->_Prev->_Next = p_Var1;
  return;
}
