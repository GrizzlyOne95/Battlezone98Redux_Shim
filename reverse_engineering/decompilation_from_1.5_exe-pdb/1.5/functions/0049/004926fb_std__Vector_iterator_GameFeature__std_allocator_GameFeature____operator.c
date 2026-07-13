/*
 * Entry: 004926fb
 * Name: std::_Vector_iterator<GameFeature_*,std::allocator<GameFeature_*>_>::operator++
 * Namespace: std::_Vector_iterator<GameFeature_*,std::allocator<GameFeature_*>_>
 * Signature: _Vector_iterator<GameFeature_*,std::allocator<GameFeature_*>_> * operator++(_Vector_iterator<GameFeature_*,std::allocator<GameFeature_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<GameFeature_*,std::allocator<GameFeature_*>_> * __thiscall
std::_Vector_iterator<GameFeature_*,std::allocator<GameFeature_*>_>::operator++
          (_Vector_iterator<GameFeature_*,std::allocator<GameFeature_*>_> *this)

{
  _Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_>::operator++
            ((_Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_> *)this);
  return this;
}
