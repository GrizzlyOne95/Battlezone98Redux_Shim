/*
 * Entry: 0053333e
 * Name: std::allocator<Ordnance_*>::construct
 * Namespace: std::allocator<Ordnance_*>
 * Signature: void construct(allocator<Ordnance_*> * this, Ordnance * * param_1, Ordnance * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::allocator<Ordnance_*>::construct
          (allocator<Ordnance_*> *this,Ordnance **param_1,Ordnance **param_2)

{
  if (param_1 != (Ordnance **)0x0) {
    *param_1 = *param_2;
  }
  return;
}
