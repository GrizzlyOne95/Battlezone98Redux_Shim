/*
 * Entry: 004c7f83
 * Name: std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Const_iterator<0>::_Const_iterator<0>
 * Namespace: std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Const_iterator<0>
 * Signature: _Const_iterator<0> * _Const_iterator<0>(_Const_iterator<0> * this, _Node * param_1, list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_> * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Const_iterator<0> * __thiscall
std::list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_>::_Const_iterator<0>::
_Const_iterator<0>(_Const_iterator<0> *this,_Node *param_1,
                  list<DisplayViewInfo_*,std::allocator<DisplayViewInfo_*>_> *param_2)

{
  this->_padding_ = 0;
  this->_Ptr = param_1;
  this->_padding_ = param_2->_padding_;
  return this;
}
