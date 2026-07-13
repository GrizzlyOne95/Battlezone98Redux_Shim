/*
 * Entry: 0052e3d2
 * Name: std::list<Explosion_*,std::allocator<Explosion_*>_>::push_front
 * Namespace: std::list<Explosion_*,std::allocator<Explosion_*>_>
 * Signature: void push_front(list<Explosion_*,std::allocator<Explosion_*>_> * this, Explosion * * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::list<Explosion_*,std::allocator<Explosion_*>_>::push_front
          (list<Explosion_*,std::allocator<Explosion_*>_> *this,Explosion **param_1)

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
