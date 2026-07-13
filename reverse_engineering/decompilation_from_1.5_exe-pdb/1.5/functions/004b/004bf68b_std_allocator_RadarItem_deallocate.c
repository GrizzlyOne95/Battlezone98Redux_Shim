/*
 * Entry: 004bf68b
 * Name: std::allocator<RadarItem>::deallocate
 * Namespace: std::allocator<RadarItem>
 * Signature: void deallocate(allocator<RadarItem> * this, RadarItem * param_1, uint param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::allocator<RadarItem>::deallocate(allocator<RadarItem> *this,RadarItem *param_1,uint param_2)

{
  operator_delete(param_1);
  return;
}
