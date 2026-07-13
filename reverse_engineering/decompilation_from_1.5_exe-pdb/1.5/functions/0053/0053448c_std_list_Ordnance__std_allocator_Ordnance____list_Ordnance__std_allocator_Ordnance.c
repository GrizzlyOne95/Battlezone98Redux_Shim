/*
 * Entry: 0053448c
 * Name: std::list<Ordnance_*,std::allocator<Ordnance_*>_>::list<Ordnance_*,std::allocator<Ordnance_*>_>
 * Namespace: std::list<Ordnance_*,std::allocator<Ordnance_*>_>
 * Signature: list<Ordnance_*,std::allocator<Ordnance_*>_> * list<Ordnance_*,std::allocator<Ordnance_*>_>(list<Ordnance_*,std::allocator<Ordnance_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

list<Ordnance_*,std::allocator<Ordnance_*>_> * __thiscall
std::list<Ordnance_*,std::allocator<Ordnance_*>_>::list<Ordnance_*,std::allocator<Ordnance_*>_>
          (list<Ordnance_*,std::allocator<Ordnance_*>_> *this)

{
  _Node *p_Var1;
  
  _List_val<Ordnance_*,std::allocator<Ordnance_*>_>::
  _List_val<Ordnance_*,std::allocator<Ordnance_*>_>
            ((_List_val<Ordnance_*,std::allocator<Ordnance_*>_> *)this,SUB41(this,0));
  p_Var1 = _Buynode(this);
  this->_Mysize = 0;
  this->_Myhead = p_Var1;
  return this;
}
