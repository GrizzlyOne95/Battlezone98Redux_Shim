/*
 * Entry: 0052eb23
 * Name: std::_Vector_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::operator*
 * Namespace: std::_Vector_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_>
 * Signature: ExplosionClass * * operator*(_Vector_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ExplosionClass ** __thiscall
std::_Vector_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_>::operator*
          (_Vector_iterator<ExplosionClass_*,std::allocator<ExplosionClass_*>_> *this)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = *(int **)this;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = *(int **)this;
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
      goto LAB_0052e8bb;
    }
  }
  iVar2 = *piVar1;
LAB_0052e8bb:
  if (*(uint *)(iVar2 + 0x10) <= *(uint *)&this->field_0x4) {
    _invalid_parameter_noinfo();
  }
  return *(ExplosionClass ***)&this->field_0x4;
}
