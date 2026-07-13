/*
 * Entry: 0041246d
 * Name: std::list<FollowGroup_*,std::allocator<FollowGroup_*>_>::list<FollowGroup_*,std::allocator<FollowGroup_*>_>
 * Namespace: std::list<FollowGroup_*,std::allocator<FollowGroup_*>_>
 * Signature: list<FollowGroup_*,std::allocator<FollowGroup_*>_> * list<FollowGroup_*,std::allocator<FollowGroup_*>_>(list<FollowGroup_*,std::allocator<FollowGroup_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

list<FollowGroup_*,std::allocator<FollowGroup_*>_> * __thiscall
std::list<FollowGroup_*,std::allocator<FollowGroup_*>_>::
list<FollowGroup_*,std::allocator<FollowGroup_*>_>
          (list<FollowGroup_*,std::allocator<FollowGroup_*>_> *this)

{
  _Node *p_Var1;
  
  _List_val<FollowGroup_*,std::allocator<FollowGroup_*>_>::
  _List_val<FollowGroup_*,std::allocator<FollowGroup_*>_>
            ((_List_val<FollowGroup_*,std::allocator<FollowGroup_*>_> *)this,SUB41(this,0));
  p_Var1 = _Buynode(this);
  this->_Mysize = 0;
  this->_Myhead = p_Var1;
  return this;
}
