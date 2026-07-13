/*
 * Entry: 0049963d
 * Name: std::_Vector_val<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::~_Vector_val<GameObjectClass_*,std::allocator<GameObjectClass_*>_>
 * Namespace: std::_Vector_val<GameObjectClass_*,std::allocator<GameObjectClass_*>_>
 * Signature: void ~_Vector_val<GameObjectClass_*,std::allocator<GameObjectClass_*>_>(_Vector_val<GameObjectClass_*,std::allocator<GameObjectClass_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_Vector_val<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::
~_Vector_val<GameObjectClass_*,std::allocator<GameObjectClass_*>_>
          (_Vector_val<GameObjectClass_*,std::allocator<GameObjectClass_*>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
