/*
 * Entry: 004b0d60
 * Name: std::list<RtimeClass_*,std::allocator<RtimeClass_*>_>::_Const_iterator<1>::_Const_iterator<1>
 * Namespace: std::list<RtimeClass_*,std::allocator<RtimeClass_*>_>::_Const_iterator<1>
 * Signature: _Const_iterator<1> * _Const_iterator<1>(_Const_iterator<1> * this, _Node * param_1, list<RtimeClass_*,std::allocator<RtimeClass_*>_> * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Const_iterator<1> * __thiscall
std::list<RtimeClass_*,std::allocator<RtimeClass_*>_>::_Const_iterator<1>::_Const_iterator<1>
          (_Const_iterator<1> *this,_Node *param_1,
          list<RtimeClass_*,std::allocator<RtimeClass_*>_> *param_2)

{
  this->_padding_ = 0;
  this->_Ptr = param_1;
  if (param_2 == (list<RtimeClass_*,std::allocator<RtimeClass_*>_> *)0x0) {
    _invalid_parameter_noinfo();
  }
  this->_padding_ = param_2->_padding_;
  return this;
}
