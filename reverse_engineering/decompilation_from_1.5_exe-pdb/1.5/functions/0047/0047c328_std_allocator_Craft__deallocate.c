/*
 * Entry: 0047c328
 * Name: std::allocator<Craft_*>::deallocate
 * Namespace: std::allocator<Craft_*>
 * Signature: void deallocate(allocator<Craft_*> * this, Craft * * param_1, uint param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::allocator<Craft_*>::deallocate(allocator<Craft_*> *this,Craft **param_1,uint param_2)

{
  operator_delete(param_1);
  return;
}
