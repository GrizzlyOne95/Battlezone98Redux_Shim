/*
 * Entry: 00549a87
 * Name: std::list<OldNew_*,std::allocator<OldNew_*>_>::list<OldNew_*,std::allocator<OldNew_*>_>
 * Namespace: std::list<OldNew_*,std::allocator<OldNew_*>_>
 * Signature: list<OldNew_*,std::allocator<OldNew_*>_> * list<OldNew_*,std::allocator<OldNew_*>_>(list<OldNew_*,std::allocator<OldNew_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

list<OldNew_*,std::allocator<OldNew_*>_> * __thiscall
std::list<OldNew_*,std::allocator<OldNew_*>_>::list<OldNew_*,std::allocator<OldNew_*>_>
          (list<OldNew_*,std::allocator<OldNew_*>_> *this)

{
  _Node *p_Var1;
  
  _List_val<OldNew_*,std::allocator<OldNew_*>_>::_List_val<OldNew_*,std::allocator<OldNew_*>_>
            ((_List_val<OldNew_*,std::allocator<OldNew_*>_> *)this,SUB41(this,0));
  p_Var1 = _Buynode(this);
  this->_Mysize = 0;
  this->_Myhead = p_Var1;
  return this;
}
