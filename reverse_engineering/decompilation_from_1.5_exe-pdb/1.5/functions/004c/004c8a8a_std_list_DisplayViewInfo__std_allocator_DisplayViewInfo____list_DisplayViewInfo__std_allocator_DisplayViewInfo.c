/*
 * Entry: 004c8a8a
 * Name: std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>
 * Namespace: std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>
 * Signature: list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_> * list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>(list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_> * __thiscall
std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::
list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>
          (list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_> *this)

{
  _Node *p_Var1;
  
  _List_val<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::
  _List_val<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>
            ((_List_val<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_> *)this,SUB41(this,0));
  p_Var1 = _Buynode(this);
  this->_Mysize = 0;
  this->_Myhead = p_Var1;
  return this;
}
