/*
 * Entry: 005576c6
 * Name: std::_Vector_iterator<Server_*,std::allocator<Server_*>_>::operator++
 * Namespace: std::_Vector_iterator<Server_*,std::allocator<Server_*>_>
 * Signature: _Vector_iterator<Server_*,std::allocator<Server_*>_> * operator++(_Vector_iterator<Server_*,std::allocator<Server_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Server_*,std::allocator<Server_*>_> * __thiscall
std::_Vector_iterator<Server_*,std::allocator<Server_*>_>::operator++
          (_Vector_iterator<Server_*,std::allocator<Server_*>_> *this)

{
  _Vector_const_iterator<Server_*,std::allocator<Server_*>_>::operator++
            ((_Vector_const_iterator<Server_*,std::allocator<Server_*>_> *)this);
  return this;
}
