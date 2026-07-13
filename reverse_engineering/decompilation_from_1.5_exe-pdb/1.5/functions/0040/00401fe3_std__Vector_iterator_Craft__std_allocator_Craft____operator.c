/*
 * Entry: 00401fe3
 * Name: std::_Vector_iterator<Craft_*,std::allocator<Craft_*>_>::operator++
 * Namespace: std::_Vector_iterator<Craft_*,std::allocator<Craft_*>_>
 * Signature: _Vector_iterator<Craft_*,std::allocator<Craft_*>_> * operator++(_Vector_iterator<Craft_*,std::allocator<Craft_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Craft_*,std::allocator<Craft_*>_> * __thiscall
std::_Vector_iterator<Craft_*,std::allocator<Craft_*>_>::operator++
          (_Vector_iterator<Craft_*,std::allocator<Craft_*>_> *this)

{
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::operator++
            ((_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> *)this);
  return this;
}
