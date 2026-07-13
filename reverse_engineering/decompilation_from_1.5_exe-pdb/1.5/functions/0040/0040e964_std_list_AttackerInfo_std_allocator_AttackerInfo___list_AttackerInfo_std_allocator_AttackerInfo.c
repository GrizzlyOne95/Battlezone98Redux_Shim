/*
 * Entry: 0040e964
 * Name: std::list<AttackerInfo,std::allocator<AttackerInfo>_>::list<AttackerInfo,std::allocator<AttackerInfo>_>
 * Namespace: std::list<AttackerInfo,std::allocator<AttackerInfo>_>
 * Signature: list<AttackerInfo,std::allocator<AttackerInfo>_> * list<AttackerInfo,std::allocator<AttackerInfo>_>(list<AttackerInfo,std::allocator<AttackerInfo>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

list<AttackerInfo,std::allocator<AttackerInfo>_> * __thiscall
std::list<AttackerInfo,std::allocator<AttackerInfo>_>::
list<AttackerInfo,std::allocator<AttackerInfo>_>
          (list<AttackerInfo,std::allocator<AttackerInfo>_> *this)

{
  _Node *p_Var1;
  
  _List_val<AttackerInfo,std::allocator<AttackerInfo>_>::
  _List_val<AttackerInfo,std::allocator<AttackerInfo>_>
            ((_List_val<AttackerInfo,std::allocator<AttackerInfo>_> *)this,SUB41(this,0));
  p_Var1 = _Buynode(this);
  this->_Mysize = 0;
  this->_Myhead = p_Var1;
  return this;
}
