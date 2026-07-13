/*
 * Entry: 005ca7cd
 * Name: `dynamic_initializer_for_'AnimSprite::spriteList''
 * Namespace: `dynamic_initializer_for_'AnimSprite
 * Signature: void spriteList''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl `dynamic_initializer_for_'AnimSprite::spriteList__(void)

{
  std::vector<AnimSprite_*,std::allocator<AnimSprite_*>_>::
  vector<AnimSprite_*,std::allocator<AnimSprite_*>_>(&AnimSprite::spriteList);
  atexit(`dynamic_atexit_destructor_for_'AnimSprite::spriteList__);
  return;
}
