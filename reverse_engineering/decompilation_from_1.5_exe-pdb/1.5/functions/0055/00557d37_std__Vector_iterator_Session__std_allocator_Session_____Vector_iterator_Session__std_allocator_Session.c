/*
 * Entry: 00557d37
 * Name: std::_Vector_iterator<Session_*,std::allocator<Session_*>_>::_Vector_iterator<Session_*,std::allocator<Session_*>_>
 * Namespace: std::_Vector_iterator<Session_*,std::allocator<Session_*>_>
 * Signature: _Vector_iterator<Session_*,std::allocator<Session_*>_> * _Vector_iterator<Session_*,std::allocator<Session_*>_>(_Vector_iterator<Session_*,std::allocator<Session_*>_> * this, Session * * param_1, _Container_base_aux * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Session_*,std::allocator<Session_*>_> * __thiscall
std::_Vector_iterator<Session_*,std::allocator<Session_*>_>::
_Vector_iterator<Session_*,std::allocator<Session_*>_>
          (_Vector_iterator<Session_*,std::allocator<Session_*>_> *this,Session **param_1,
          _Container_base_aux *param_2)

{
  _Vector_const_iterator<Session_*,std::allocator<Session_*>_>::
  _Vector_const_iterator<Session_*,std::allocator<Session_*>_>
            ((_Vector_const_iterator<Session_*,std::allocator<Session_*>_> *)this,param_1,param_2);
  return this;
}
