/*
 * Entry: 0052e110
 * Name: std::allocator<Explosion_*>::construct
 * Namespace: std::allocator<Explosion_*>
 * Signature: void construct(allocator<Explosion_*> * this, Explosion * * param_1, Explosion * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::allocator<Explosion_*>::construct
          (allocator<Explosion_*> *this,Explosion **param_1,Explosion **param_2)

{
  if (param_1 != (Explosion **)0x0) {
    *param_1 = *param_2;
  }
  return;
}
