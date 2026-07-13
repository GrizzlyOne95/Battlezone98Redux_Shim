/*
 * Entry: 004089df
 * Name: std::_Vector_iterator<Geizer_*,std::allocator<Geizer_*>_>::operator++
 * Namespace: std::_Vector_iterator<Geizer_*,std::allocator<Geizer_*>_>
 * Signature: _Vector_iterator<Geizer_*,std::allocator<Geizer_*>_> * operator++(_Vector_iterator<Geizer_*,std::allocator<Geizer_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Geizer_*,std::allocator<Geizer_*>_> * __thiscall
std::_Vector_iterator<Geizer_*,std::allocator<Geizer_*>_>::operator++
          (_Vector_iterator<Geizer_*,std::allocator<Geizer_*>_> *this)

{
  _Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_>::operator++
            ((_Vector_const_iterator<Geizer_*,std::allocator<Geizer_*>_> *)this);
  return this;
}
