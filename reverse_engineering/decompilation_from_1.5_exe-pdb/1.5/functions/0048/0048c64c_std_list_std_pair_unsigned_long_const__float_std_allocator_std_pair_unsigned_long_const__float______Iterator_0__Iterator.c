/*
 * Entry: 0048c64c
 * Name: std::list<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_>::_Iterator<0>::_Iterator<0>
 * Namespace: std::list<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_>::_Iterator<0>
 * Signature: _Iterator<0> * _Iterator<0>(_Iterator<0> * this, _Node * param_1, list<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_> * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Iterator<0> * __thiscall
std::
list<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_>
::_Iterator<0>::_Iterator<0>
          (_Iterator<0> *this,_Node *param_1,
          list<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_>
          *param_2)

{
  *(undefined4 *)this = 0;
  *(_Node **)&this->field_0x4 = param_1;
  *(int *)this = param_2->_padding_;
  return this;
}
