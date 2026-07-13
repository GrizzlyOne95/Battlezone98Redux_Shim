/*
 * Entry: 004609f8
 * Name: std::_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_>::operator+=
 * Namespace: std::_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_>
 * Signature: _Vector_iterator<Scrap_*,std::allocator<Scrap_*>_> * operator+=(_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_> * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_> * __thiscall
std::_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_>::operator+=
          (_Vector_iterator<Scrap_*,std::allocator<Scrap_*>_> *this,int param_1)

{
  _Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_>::operator+=
            ((_Vector_const_iterator<Scrap_*,std::allocator<Scrap_*>_> *)this,param_1);
  return this;
}
