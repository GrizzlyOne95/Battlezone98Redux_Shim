/*
 * Entry: 0047c3a1
 * Name: std::allocator<AnimSprite_*>::deallocate
 * Namespace: std::allocator<AnimSprite_*>
 * Signature: void deallocate(allocator<AnimSprite_*> * this, AnimSprite * * param_1, uint param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::allocator<AnimSprite_*>::deallocate
          (allocator<AnimSprite_*> *this,AnimSprite **param_1,uint param_2)

{
  operator_delete(param_1);
  return;
}
