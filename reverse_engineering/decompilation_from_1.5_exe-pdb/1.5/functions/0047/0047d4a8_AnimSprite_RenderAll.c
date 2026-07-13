/*
 * Entry: 0047d4a8
 * Name: AnimSprite::RenderAll
 * Namespace: AnimSprite
 * Signature: void RenderAll(CAMERA * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AnimSprite::RenderAll(CAMERA *param_1)

{
  bool bVar1;
  AnimSprite **ppAVar2;
  _Vector_const_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> local_1c;
  _Vector_const_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> local_14;
  _Vector_const_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_> local_c;
  
  std::_Vector_const_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>::
  _Vector_const_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>
            (&local_c,spriteList._Myfirst,(_Container_base_aux *)&spriteList);
  while( true ) {
    std::_Vector_const_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>::
    _Vector_const_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>
              (&local_14,spriteList._Mylast,(_Container_base_aux *)&spriteList);
    bVar1 = std::_Vector_const_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>::operator==
                      (&local_c,&local_14);
    if (bVar1) break;
    local_1c._padding_ = local_c._padding_;
    local_1c._Myptr = local_c._Myptr;
    std::_Vector_const_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>::operator++(&local_c);
    ppAVar2 = std::_Vector_const_iterator<AnimSprite_*,std::allocator<AnimSprite_*>_>::operator*
                        (&local_1c);
    Render(*ppAVar2,param_1);
  }
  return;
}
