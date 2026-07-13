/*
 * Entry: 004926d8
 * Name: std::_Vector_iterator<GameFeature_*,std::allocator<GameFeature_*>_>::operator*
 * Namespace: std::_Vector_iterator<GameFeature_*,std::allocator<GameFeature_*>_>
 * Signature: GameFeature * * operator*(_Vector_iterator<GameFeature_*,std::allocator<GameFeature_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameFeature ** __thiscall
std::_Vector_iterator<GameFeature_*,std::allocator<GameFeature_*>_>::operator*
          (_Vector_iterator<GameFeature_*,std::allocator<GameFeature_*>_> *this)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = *(int **)this;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = *(int **)this;
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
      goto LAB_00491ed5;
    }
  }
  iVar2 = *piVar1;
LAB_00491ed5:
  if (*(uint *)(iVar2 + 0x10) <= *(uint *)&this->field_0x4) {
    _invalid_parameter_noinfo();
  }
  return *(GameFeature ***)&this->field_0x4;
}
