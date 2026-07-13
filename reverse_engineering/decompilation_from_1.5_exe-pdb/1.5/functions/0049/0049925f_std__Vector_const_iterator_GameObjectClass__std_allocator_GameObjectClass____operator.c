/*
 * Entry: 0049925f
 * Name: std::_Vector_const_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::operator*
 * Namespace: std::_Vector_const_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_>
 * Signature: GameObjectClass * * operator*(_Vector_const_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass ** __thiscall
std::_Vector_const_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::operator*
          (_Vector_const_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_> *this)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)this->_padding_;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = (int *)this->_padding_;
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
      goto LAB_0049927d;
    }
  }
  iVar2 = *piVar1;
LAB_0049927d:
  if (*(GameObjectClass ***)(iVar2 + 0x10) <= this->_Myptr) {
    _invalid_parameter_noinfo();
  }
  return this->_Myptr;
}
