/*
 * Entry: 005495a5
 * Name: std::allocator<Addr_*>::construct
 * Namespace: std::allocator<Addr_*>
 * Signature: void construct(allocator<Addr_*> * this, Addr * * param_1, Addr * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::allocator<Addr_*>::construct(allocator<Addr_*> *this,Addr **param_1,Addr **param_2)

{
  if (param_1 != (Addr **)0x0) {
    *param_1 = *param_2;
  }
  return;
}
