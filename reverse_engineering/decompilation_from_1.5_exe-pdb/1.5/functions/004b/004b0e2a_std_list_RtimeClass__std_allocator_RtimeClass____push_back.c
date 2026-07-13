/*
 * Entry: 004b0e2a
 * Name: std::list<RtimeClass_*,std::allocator<RtimeClass_*>_>::push_back
 * Namespace: std::list<RtimeClass_*,std::allocator<RtimeClass_*>_>
 * Signature: void push_back(list<RtimeClass_*,std::allocator<RtimeClass_*>_> * this, RtimeClass * * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::list<RtimeClass_*,std::allocator<RtimeClass_*>_>::push_back
          (list<RtimeClass_*,std::allocator<RtimeClass_*>_> *this,RtimeClass **param_1)

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
