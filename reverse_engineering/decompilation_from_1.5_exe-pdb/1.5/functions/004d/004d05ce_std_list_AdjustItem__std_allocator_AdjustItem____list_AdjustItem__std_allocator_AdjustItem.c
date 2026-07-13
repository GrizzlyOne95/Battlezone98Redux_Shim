/*
 * Entry: 004d05ce
 * Name: std::list<AdjustItem_*,std::allocator<AdjustItem_*>_>::list<AdjustItem_*,std::allocator<AdjustItem_*>_>
 * Namespace: std::list<AdjustItem_*,std::allocator<AdjustItem_*>_>
 * Signature: list<AdjustItem_*,std::allocator<AdjustItem_*>_> * list<AdjustItem_*,std::allocator<AdjustItem_*>_>(list<AdjustItem_*,std::allocator<AdjustItem_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

list<AdjustItem_*,std::allocator<AdjustItem_*>_> * __thiscall
std::list<AdjustItem_*,std::allocator<AdjustItem_*>_>::
list<AdjustItem_*,std::allocator<AdjustItem_*>_>
          (list<AdjustItem_*,std::allocator<AdjustItem_*>_> *this)

{
  _Node *p_Var1;
  
  _List_val<AdjustItem_*,std::allocator<AdjustItem_*>_>::
  _List_val<AdjustItem_*,std::allocator<AdjustItem_*>_>
            ((_List_val<AdjustItem_*,std::allocator<AdjustItem_*>_> *)this,SUB41(this,0));
  p_Var1 = _Buynode(this);
  this->_Mysize = 0;
  this->_Myhead = p_Var1;
  return this;
}
