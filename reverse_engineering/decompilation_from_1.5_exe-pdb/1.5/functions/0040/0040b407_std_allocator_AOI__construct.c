/*
 * Entry: 0040b407
 * Name: std::allocator<AOI_*>::construct
 * Namespace: std::allocator<AOI_*>
 * Signature: void construct(allocator<AOI_*> * this, AOI * * param_1, AOI * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall std::allocator<AOI_*>::construct(allocator<AOI_*> *this,AOI **param_1,AOI **param_2)

{
  if (param_1 != (AOI **)0x0) {
    *param_1 = *param_2;
  }
  return;
}
