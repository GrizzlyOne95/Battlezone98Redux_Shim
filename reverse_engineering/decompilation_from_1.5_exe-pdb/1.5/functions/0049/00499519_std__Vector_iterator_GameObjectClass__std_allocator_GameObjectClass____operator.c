/*
 * Entry: 00499519
 * Name: std::_Vector_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::operator*
 * Namespace: std::_Vector_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_>
 * Signature: GameObjectClass * * operator*(_Vector_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass ** __thiscall
std::_Vector_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_>::operator*
          (_Vector_iterator<GameObjectClass_*,std::allocator<GameObjectClass_*>_> *this)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = *(int **)this;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = *(int **)this;
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
      goto LAB_0049927d;
    }
  }
  iVar2 = *piVar1;
LAB_0049927d:
  if (*(uint *)(iVar2 + 0x10) <= *(uint *)&this->field_0x4) {
    _invalid_parameter_noinfo();
  }
  return *(GameObjectClass ***)&this->field_0x4;
}
