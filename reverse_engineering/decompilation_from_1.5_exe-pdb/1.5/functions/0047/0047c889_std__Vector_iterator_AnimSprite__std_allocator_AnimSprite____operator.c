/*
 * Entry: 0047c889
 * Name: std::_Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>::operator*
 * Namespace: std::_Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>
 * Signature: AnimSprite * * operator*(_Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AnimSprite ** __thiscall
std::_Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>::operator*
          (_Vector_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> *this)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = *(int **)this;
  if (piVar1 == (int *)0x0) {
    _invalid_parameter_noinfo();
    piVar1 = *(int **)this;
    if (piVar1 == (int *)0x0) {
      iVar2 = 0;
      goto LAB_0047c222;
    }
  }
  iVar2 = *piVar1;
LAB_0047c222:
  if (*(uint *)(iVar2 + 0x10) <= *(uint *)&this->field_0x4) {
    _invalid_parameter_noinfo();
  }
  return *(AnimSprite ***)&this->field_0x4;
}
