/*
 * Entry: 0047c8fb
 * Name: std::allocator<Craft_*>::allocate
 * Namespace: std::allocator<Craft_*>
 * Signature: Craft * * allocate(allocator<Craft_*> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Craft ** __thiscall std::allocator<Craft_*>::allocate(allocator<Craft_*> *this,uint param_1)

{
  Craft **ppCVar1;
  
  ppCVar1 = _Allocate<Craft_*>(param_1,(Craft **)0x0);
  return ppCVar1;
}
