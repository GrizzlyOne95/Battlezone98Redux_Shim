/*
 * Entry: 0045b183
 * Name: std::_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_>::operator++
 * Namespace: std::_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_>
 * Signature: _Vector_iterator<Scrap_*,std::allocator<Scrap_*>_> * operator++(_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_> * __thiscall
std::_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_>::operator++
          (_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_> *this)

{
  _Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_>::operator++
            ((_Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_> *)this);
  return this;
}
