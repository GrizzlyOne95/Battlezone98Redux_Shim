/*
 * Entry: 005576d2
 * Name: std::_Vector_iterator<Session_*,std::allocator<Session_*>_>::operator++
 * Namespace: std::_Vector_iterator<Session_*,std::allocator<Session_*>_>
 * Signature: _Vector_iterator<Session_*,std::allocator<Session_*>_> * operator++(_Vector_iterator<Session_*,std::allocator<Session_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Session_*,std::allocator<Session_*>_> * __thiscall
std::_Vector_iterator<Session_*,std::allocator<Session_*>_>::operator++
          (_Vector_iterator<Session_*,std::allocator<Session_*>_> *this)

{
  _Vector_const_iterator<Session_*,std::allocator<Session_*>_>::operator++
            ((_Vector_const_iterator<Session_*,std::allocator<Session_*>_> *)this);
  return this;
}
