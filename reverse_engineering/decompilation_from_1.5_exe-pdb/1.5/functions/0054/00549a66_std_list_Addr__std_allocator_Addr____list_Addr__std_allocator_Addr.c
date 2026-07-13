/*
 * Entry: 00549a66
 * Name: std::list<Addr_*,std::allocator<Addr_*>_>::list<Addr_*,std::allocator<Addr_*>_>
 * Namespace: std::list<Addr_*,std::allocator<Addr_*>_>
 * Signature: list<Addr_*,std::allocator<Addr_*>_> * list<Addr_*,std::allocator<Addr_*>_>(list<Addr_*,std::allocator<Addr_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

list<Addr_*,std::allocator<Addr_*>_> * __thiscall
std::list<Addr_*,std::allocator<Addr_*>_>::list<Addr_*,std::allocator<Addr_*>_>
          (list<Addr_*,std::allocator<Addr_*>_> *this)

{
  _Node *p_Var1;
  
  _List_val<Addr_*,std::allocator<Addr_*>_>::_List_val<Addr_*,std::allocator<Addr_*>_>
            ((_List_val<Addr_*,std::allocator<Addr_*>_> *)this,SUB41(this,0));
  p_Var1 = _Buynode(this);
  this->_Mysize = 0;
  this->_Myhead = p_Var1;
  return this;
}
