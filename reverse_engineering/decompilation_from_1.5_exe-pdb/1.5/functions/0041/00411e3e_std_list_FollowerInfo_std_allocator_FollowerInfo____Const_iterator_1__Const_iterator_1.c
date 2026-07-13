/*
 * Entry: 00411e3e
 * Name: std::list<FollowerInfo,std::allocator<FollowerInfo>_>::_Const_iterator<1>::_Const_iterator<1>
 * Namespace: std::list<FollowerInfo,std::allocator<FollowerInfo>_>::_Const_iterator<1>
 * Signature: _Const_iterator<1> * _Const_iterator<1>(_Const_iterator<1> * this, _Node * param_1, list<FollowerInfo,std::allocator<FollowerInfo>_> * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Const_iterator<1> * __thiscall
std::list<FollowerInfo,std::allocator<FollowerInfo>_>::_Const_iterator<1>::_Const_iterator<1>
          (_Const_iterator<1> *this,_Node *param_1,
          list<FollowerInfo,std::allocator<FollowerInfo>_> *param_2)

{
  this->_padding_ = 0;
  this->_Ptr = param_1;
  if (param_2 == (list<FollowerInfo,std::allocator<FollowerInfo>_> *)0x0) {
    _invalid_parameter_noinfo();
  }
  this->_padding_ = param_2->_padding_;
  return this;
}
