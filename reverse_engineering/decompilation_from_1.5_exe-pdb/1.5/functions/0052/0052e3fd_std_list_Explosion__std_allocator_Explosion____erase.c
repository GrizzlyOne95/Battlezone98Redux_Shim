/*
 * Entry: 0052e3fd
 * Name: std::list<Explosion_*,std::allocator<Explosion_*>_>::erase
 * Namespace: std::list<Explosion_*,std::allocator<Explosion_*>_>
 * Signature: _Iterator<1> erase(list<Explosion_*,std::allocator<Explosion_*>_> * this, _Const_iterator<1> param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Iterator<1> __thiscall
std::list<Explosion_*,std::allocator<Explosion_*>_>::erase
          (list<Explosion_*,std::allocator<Explosion_*>_> *this,_Const_iterator<1> param_1)

{
  undefined4 extraout_EDX;
  _Iterator<1> _Var1;
  _Node *in_stack_0000000c;
  
  _Const_iterator<1>::operator++((_Const_iterator<1> *)&param_1._Ptr);
  if (in_stack_0000000c != this->_Myhead) {
    in_stack_0000000c->_Prev->_Next = in_stack_0000000c->_Next;
    in_stack_0000000c->_Next->_Prev = in_stack_0000000c->_Prev;
    operator_delete(in_stack_0000000c);
    this->_Mysize = this->_Mysize - 1;
  }
  _Const_iterator<1>::_Const_iterator<1>
            ((_Const_iterator<1> *)param_1._padding_,in_stack_0000000c,this);
  _Var1._4_4_ = extraout_EDX;
  _Var1._0_4_ = param_1._padding_;
  return _Var1;
}
