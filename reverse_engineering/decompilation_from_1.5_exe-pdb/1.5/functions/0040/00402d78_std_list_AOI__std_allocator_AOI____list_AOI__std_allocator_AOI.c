/*
 * Entry: 00402d78
 * Name: std::list<AOI_*,std::allocator<AOI_*>_>::list<AOI_*,std::allocator<AOI_*>_>
 * Namespace: std::list<AOI_*,std::allocator<AOI_*>_>
 * Signature: list<AOI_*,std::allocator<AOI_*>_> * list<AOI_*,std::allocator<AOI_*>_>(list<AOI_*,std::allocator<AOI_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

list<AOI_*,std::allocator<AOI_*>_> * __thiscall
std::list<AOI_*,std::allocator<AOI_*>_>::list<AOI_*,std::allocator<AOI_*>_>
          (list<AOI_*,std::allocator<AOI_*>_> *this)

{
  _Node *p_Var1;
  
  _List_val<AOI_*,std::allocator<AOI_*>_>::_List_val<AOI_*,std::allocator<AOI_*>_>
            ((_List_val<AOI_*,std::allocator<AOI_*>_> *)this,SUB41(this,0));
  p_Var1 = _Buynode(this);
  this->_Mysize = 0;
  this->_Myhead = p_Var1;
  return this;
}
