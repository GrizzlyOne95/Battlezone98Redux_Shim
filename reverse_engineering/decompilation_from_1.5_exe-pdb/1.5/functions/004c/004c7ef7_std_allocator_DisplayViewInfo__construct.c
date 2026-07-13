/*
 * Entry: 004c7ef7
 * Name: std::allocator<DisplayViewInfo_*>::construct
 * Namespace: std::allocator<DisplayViewInfo_*>
 * Signature: void construct(allocator<DisplayViewInfo_*> * this, DisplayViewInfo * * param_1, DisplayViewInfo * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::allocator<DisplayViewInfo_*>::construct
          (allocator<DisplayViewInfo_*> *this,DisplayViewInfo **param_1,DisplayViewInfo **param_2)

{
  if (param_1 != (DisplayViewInfo **)0x0) {
    *param_1 = *param_2;
  }
  return;
}
