/*
 * Entry: 0052e035
 * Name: std::list<Explosion_*,std::allocator<Explosion_*>_>::_Iterator<1>::operator*
 * Namespace: std::list<Explosion_*,std::allocator<Explosion_*>_>::_Iterator<1>
 * Signature: Explosion * * operator*(_Iterator<1> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Explosion ** __thiscall
std::list<Explosion_*,std::allocator<Explosion_*>_>::_Iterator<1>::operator*(_Iterator<1> *this)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = *(int **)this;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = *(int **)this;
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
      goto LAB_0052df76;
    }
  }
  iVar2 = *piVar1;
LAB_0052df76:
  if (*(int *)&this->field_0x4 == *(int *)(iVar2 + 0x14)) {
    _invalid_parameter_noinfo();
  }
  return (Explosion **)(*(int *)&this->field_0x4 + 8);
}
