/*
 * Entry: 005495b8
 * Name: std::allocator<OldNew_*>::construct
 * Namespace: std::allocator<OldNew_*>
 * Signature: void construct(allocator<OldNew_*> * this, OldNew * * param_1, OldNew * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::allocator<OldNew_*>::construct(allocator<OldNew_*> *this,OldNew **param_1,OldNew **param_2)

{
  if (param_1 != (OldNew **)0x0) {
    *param_1 = *param_2;
  }
  return;
}
