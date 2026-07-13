/*
 * Entry: 0047c937
 * Name: std::allocator<AnimSprite_*>::allocate
 * Namespace: std::allocator<AnimSprite_*>
 * Signature: AnimSprite * * allocate(allocator<AnimSprite_*> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AnimSprite ** __thiscall
std::allocator<AnimSprite_*>::allocate(allocator<AnimSprite_*> *this,uint param_1)

{
  AnimSprite **ppAVar1;
  
  ppAVar1 = _Allocate<AnimSprite_*>(param_1,(AnimSprite **)0x0);
  return ppAVar1;
}
