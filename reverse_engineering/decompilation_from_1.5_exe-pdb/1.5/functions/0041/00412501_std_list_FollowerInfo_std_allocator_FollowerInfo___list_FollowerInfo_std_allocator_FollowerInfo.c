/*
 * Entry: 00412501
 * Name: std::list<FollowerInfo,std::allocator<FollowerInfo>_>::list<FollowerInfo,std::allocator<FollowerInfo>_>
 * Namespace: std::list<FollowerInfo,std::allocator<FollowerInfo>_>
 * Signature: list<FollowerInfo,std::allocator<FollowerInfo>_> * list<FollowerInfo,std::allocator<FollowerInfo>_>(list<FollowerInfo,std::allocator<FollowerInfo>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

list<FollowerInfo,std::allocator<FollowerInfo>_> * __thiscall
std::list<FollowerInfo,std::allocator<FollowerInfo>_>::
list<FollowerInfo,std::allocator<FollowerInfo>_>
          (list<FollowerInfo,std::allocator<FollowerInfo>_> *this)

{
  _Node *p_Var1;
  
  _List_val<FollowerInfo,std::allocator<FollowerInfo>_>::
  _List_val<FollowerInfo,std::allocator<FollowerInfo>_>
            ((_List_val<FollowerInfo,std::allocator<FollowerInfo>_> *)this,SUB41(this,0));
  p_Var1 = _Buynode(this);
  this->_Mysize = 0;
  this->_Myhead = p_Var1;
  return this;
}
