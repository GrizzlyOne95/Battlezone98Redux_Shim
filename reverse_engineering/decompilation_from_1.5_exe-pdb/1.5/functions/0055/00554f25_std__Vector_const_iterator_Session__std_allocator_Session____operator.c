/*
 * Entry: 00554f25
 * Name: std::_Vector_const_iterator<Session_*,std::allocator<Session_*>_>::operator!=
 * Namespace: std::_Vector_const_iterator<Session_*,std::allocator<Session_*>_>
 * Signature: bool operator!=(_Vector_const_iterator<Session_*,std::allocator<Session_*>_> * this, _Vector_const_iterator<Session_*,std::allocator<Session_*>_> * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::_Vector_const_iterator<Session_*,std::allocator<Session_*>_>::operator!=
          (_Vector_const_iterator<Session_*,std::allocator<Session_*>_> *this,
          _Vector_const_iterator<Session_*,std::allocator<Session_*>_> *param_1)

{
  bool bVar1;
  
  bVar1 = operator==(this,param_1);
  return !bVar1;
}
