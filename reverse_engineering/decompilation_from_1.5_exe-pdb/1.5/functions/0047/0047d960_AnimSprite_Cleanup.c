/*
 * Entry: 0047d960
 * Name: AnimSprite::Cleanup
 * Namespace: AnimSprite
 * Signature: void Cleanup(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AnimSprite::Cleanup(void)

{
  AnimSprite *this;
  uint uVar1;
  AnimSprite **ppAVar2;
  _Vector_const_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> local_c;
  
  uVar1 = (int)spriteList._Mylast - (int)spriteList._Myfirst;
  while ((uVar1 & 0xfffffffc) != 0) {
    std::_Vector_const_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>::
    _Vector_const_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>
              (&local_c,spriteList._Myfirst,(_Container_base_aux *)&spriteList);
    ppAVar2 = std::_Vector_const_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>::operator*
                        (&local_c);
    this = *ppAVar2;
    if (this != (AnimSprite *)0x0) {
      ~AnimSprite(this);
      operator_delete(this);
    }
    uVar1 = (int)spriteList._Mylast - (int)spriteList._Myfirst;
  }
  return;
}
