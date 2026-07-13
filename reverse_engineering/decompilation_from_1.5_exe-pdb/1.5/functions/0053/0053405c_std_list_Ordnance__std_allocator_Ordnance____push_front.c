/*
 * Entry: 0053405c
 * Name: std::list<Ordnance_*,std::allocator<Ordnance_*>_>::push_front
 * Namespace: std::list<Ordnance_*,std::allocator<Ordnance_*>_>
 * Signature: void push_front(list<Ordnance_*,std::allocator<Ordnance_*>_> * this, Ordnance * * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::list<Ordnance_*,std::allocator<Ordnance_*>_>::push_front
          (list<Ordnance_*,std::allocator<Ordnance_*>_> *this,Ordnance **param_1)

{
  _Const_iterator<1> _Var1;
  _Const_iterator<1> local_c;
  
  local_c._padding_ = (int)this;
  local_c._Ptr = (_Node *)this;
  _Const_iterator<1>::_Const_iterator<1>(&local_c,this->_Myhead->_Next,this);
  _Var1._Ptr = local_c._Ptr;
  _Var1._padding_ = local_c._padding_;
  _Insert(this,_Var1,param_1);
  return;
}
