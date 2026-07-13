/*
 * Entry: 004c8a69
 * Name: std::list<DisplayInterface_*,std::allocator<DisplayInterface_*>_>::list<DisplayInterface_*,std::allocator<DisplayInterface_*>_>
 * Namespace: std::list<DisplayInterface_*,std::allocator<DisplayInterface_*>_>
 * Signature: list<DisplayInterface_*,std::allocator<DisplayInterface_*>_> * list<DisplayInterface_*,std::allocator<DisplayInterface_*>_>(list<DisplayInterface_*,std::allocator<DisplayInterface_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

list<DisplayInterface_*,std::allocator<DisplayInterface_*>_> * __thiscall
std::list<DisplayInterface_*,std::allocator<DisplayInterface_*>_>::
list<DisplayInterface_*,std::allocator<DisplayInterface_*>_>
          (list<DisplayInterface_*,std::allocator<DisplayInterface_*>_> *this)

{
  _Node *p_Var1;
  
  _List_val<DisplayInterface_*,std::allocator<DisplayInterface_*>_>::
  _List_val<DisplayInterface_*,std::allocator<DisplayInterface_*>_>
            ((_List_val<DisplayInterface_*,std::allocator<DisplayInterface_*>_> *)this,SUB41(this,0)
            );
  p_Var1 = _Buynode(this);
  this->_Mysize = 0;
  this->_Myhead = p_Var1;
  return this;
}
