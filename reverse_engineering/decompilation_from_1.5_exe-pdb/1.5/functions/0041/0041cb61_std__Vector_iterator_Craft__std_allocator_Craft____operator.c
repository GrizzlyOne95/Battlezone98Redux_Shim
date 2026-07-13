/*
 * Entry: 0041cb61
 * Name: std::_Vector_iterator<Craft_*,std::allocator<Craft_*>_>::operator+=
 * Namespace: std::_Vector_iterator<Craft_*,std::allocator<Craft_*>_>
 * Signature: _Vector_iterator<Craft_*,std::allocator<Craft_*>_> * operator+=(_Vector_iterator<Craft_*,std::allocator<Craft_*>_> * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<Craft_*,std::allocator<Craft_*>_> * __thiscall
std::_Vector_iterator<Craft_*,std::allocator<Craft_*>_>::operator+=
          (_Vector_iterator<Craft_*,std::allocator<Craft_*>_> *this,int param_1)

{
  _Vector_const_iterator<Craft_*,std::allocator<Craft_*>_>::operator+=
            ((_Vector_const_iterator<Craft_*,std::allocator<Craft_*>_> *)this,param_1);
  return this;
}
