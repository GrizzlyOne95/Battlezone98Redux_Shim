/*
 * Entry: 00496ba0
 * Name: std::_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_>::_Checked_iterator_base
 * Namespace: std::_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_>
 * Signature: GameObject * * _Checked_iterator_base(_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject ** __thiscall
std::_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_>::_Checked_iterator_base
          (_Vector_iterator<GameObject_*,std::allocator<GameObject_*>_> *this)

{
  return *(GameObject ***)&this->field_0x4;
}
