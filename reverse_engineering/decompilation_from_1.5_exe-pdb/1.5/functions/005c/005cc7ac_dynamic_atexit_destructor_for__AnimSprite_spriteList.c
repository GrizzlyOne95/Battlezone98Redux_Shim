/*
 * Entry: 005cc7ac
 * Name: `dynamic_atexit_destructor_for_'AnimSprite::spriteList''
 * Namespace: `dynamic_atexit_destructor_for_'AnimSprite
 * Signature: void spriteList''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl `dynamic_atexit_destructor_for_'AnimSprite::spriteList__(void)

{
  std::vector<AnimSprite_*,std::allocator<AnimSprite_*>_>::_Tidy(&AnimSprite::spriteList);
  operator_delete((void *)AnimSprite::spriteList._padding_);
  return;
}
