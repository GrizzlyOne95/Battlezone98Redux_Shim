/*
 * Entry: 00493173
 * Name: std::_Vector_iterator<GameFeature_*,std::allocator<GameFeature_*>_>::_Vector_iterator<GameFeature_*,std::allocator<GameFeature_*>_>
 * Namespace: std::_Vector_iterator<GameFeature_*,std::allocator<GameFeature_*>_>
 * Signature: _Vector_iterator<GameFeature_*,std::allocator<GameFeature_*>_> * _Vector_iterator<GameFeature_*,std::allocator<GameFeature_*>_>(_Vector_iterator<GameFeature_*,std::allocator<GameFeature_*>_> * this, GameFeature * * param_1, _Container_base_aux * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<GameFeature_*,std::allocator<GameFeature_*>_> * __thiscall
std::_Vector_iterator<GameFeature_*,std::allocator<GameFeature_*>_>::
_Vector_iterator<GameFeature_*,std::allocator<GameFeature_*>_>
          (_Vector_iterator<GameFeature_*,std::allocator<GameFeature_*>_> *this,
          GameFeature **param_1,_Container_base_aux *param_2)

{
  _Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_>::
  _Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_>
            ((_Vector_const_iterator<GameFeature_*,std::allocator<GameFeature_*>_> *)this,param_1,
             param_2);
  return this;
}
