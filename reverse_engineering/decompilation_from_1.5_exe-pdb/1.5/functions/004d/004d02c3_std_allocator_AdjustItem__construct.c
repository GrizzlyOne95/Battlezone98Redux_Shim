/*
 * Entry: 004d02c3
 * Name: std::allocator<AdjustItem_*>::construct
 * Namespace: std::allocator<AdjustItem_*>
 * Signature: void construct(allocator<AdjustItem_*> * this, AdjustItem * * param_1, AdjustItem * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::allocator<AdjustItem_*>::construct
          (allocator<AdjustItem_*> *this,AdjustItem **param_1,AdjustItem **param_2)

{
  if (param_1 != (AdjustItem **)0x0) {
    *param_1 = *param_2;
  }
  return;
}
