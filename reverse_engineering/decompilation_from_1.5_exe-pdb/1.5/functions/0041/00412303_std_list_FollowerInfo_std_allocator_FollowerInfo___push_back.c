/*
 * Entry: 00412303
 * Name: std::list<FollowerInfo,std::allocator<FollowerInfo>_>::push_back
 * Namespace: std::list<FollowerInfo,std::allocator<FollowerInfo>_>
 * Signature: void push_back(list<FollowerInfo,std::allocator<FollowerInfo>_> * this, FollowerInfo * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::list<FollowerInfo,std::allocator<FollowerInfo>_>::push_back
          (list<FollowerInfo,std::allocator<FollowerInfo>_> *this,FollowerInfo *param_1)

{
  _Const_iterator<1> _Var1;
  _Const_iterator<1> local_c;
  
  local_c._padding_ = (int)this;
  local_c._Ptr = (_Node *)this;
  _Const_iterator<1>::_Const_iterator<1>(&local_c,this->_Myhead,this);
  _Var1._Ptr = local_c._Ptr;
  _Var1._padding_ = local_c._padding_;
  _Insert(this,_Var1,param_1);
  return;
}
