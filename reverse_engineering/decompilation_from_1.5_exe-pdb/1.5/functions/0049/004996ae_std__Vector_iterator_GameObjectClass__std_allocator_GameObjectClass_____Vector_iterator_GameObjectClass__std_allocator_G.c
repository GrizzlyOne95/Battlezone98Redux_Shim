/*
 * Entry: 004996ae
 * Name: std::_Vector_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::_Vector_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_>
 * Namespace: std::_Vector_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_>
 * Signature: _Vector_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_> * _Vector_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_>(_Vector_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_> * this, GameObjectClass * * param_1, _Container_base_aux * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_> * __thiscall
std::_Vector_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::
_Vector_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_>
          (_Vector_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_> *this,
          GameObjectClass **param_1,_Container_base_aux *param_2)

{
  _Vector_const_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::
  _Vector_const_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_>
            ((_Vector_const_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_> *)this,
             param_1,param_2);
  return this;
}
