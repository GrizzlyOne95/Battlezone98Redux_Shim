/*
 * Entry: 004c7ee4
 * Name: std::allocator<DisplayInterface_*>::construct
 * Namespace: std::allocator<DisplayInterface_*>
 * Signature: void construct(allocator<DisplayInterface_*> * this, DisplayInterface * * param_1, DisplayInterface * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::allocator<DisplayInterface_*>::construct
          (allocator<DisplayInterface_*> *this,DisplayInterface **param_1,DisplayInterface **param_2
          )

{
  if (param_1 != (DisplayInterface **)0x0) {
    *param_1 = *param_2;
  }
  return;
}
