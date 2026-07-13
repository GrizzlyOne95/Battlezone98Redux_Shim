/*
 * Entry: 004926f2
 * Name: std::_Vector_val<GameFeature_*,std::allocator<GameFeature_*>_>::~_Vector_val<GameFeature_*,std::allocator<GameFeature_*>_>
 * Namespace: std::_Vector_val<GameFeature_*,std::allocator<GameFeature_*>_>
 * Signature: void ~_Vector_val<GameFeature_*,std::allocator<GameFeature_*>_>(_Vector_val<GameFeature_*,std::allocator<GameFeature_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_Vector_val<GameFeature_*,std::allocator<GameFeature_*>_>::
~_Vector_val<GameFeature_*,std::allocator<GameFeature_*>_>
          (_Vector_val<GameFeature_*,std::allocator<GameFeature_*>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
