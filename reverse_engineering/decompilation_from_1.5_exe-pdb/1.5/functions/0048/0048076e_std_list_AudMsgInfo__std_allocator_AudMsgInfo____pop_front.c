/*
 * Entry: 0048076e
 * Name: std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::pop_front
 * Namespace: std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>
 * Signature: void pop_front(list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_>::pop_front
          (list<AudMsgInfo_*,std::allocator<AudMsgInfo_*>_> *this)

{
  _Const_iterator<1> _Var1;
  _Const_iterator<1> local_c;
  
  local_c._padding_ = (int)this;
  local_c._Ptr = (_Node *)this;
  _Const_iterator<1>::_Const_iterator<1>(&local_c,this->_Myhead->_Next,this);
  _Var1._Ptr = (_Node *)local_c._padding_;
  _Var1._padding_ = (int)&local_c;
  erase(this,_Var1);
  return;
}
