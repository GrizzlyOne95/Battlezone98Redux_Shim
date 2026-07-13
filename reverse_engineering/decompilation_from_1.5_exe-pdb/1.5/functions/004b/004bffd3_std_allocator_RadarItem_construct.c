/*
 * Entry: 004bffd3
 * Name: std::allocator<RadarItem>::construct
 * Namespace: std::allocator<RadarItem>
 * Signature: void construct(allocator<RadarItem> * this, RadarItem * param_1, RadarItem * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::allocator<RadarItem>::construct
          (allocator<RadarItem> *this,RadarItem *param_1,RadarItem *param_2)

{
  _Construct<RadarItem,RadarItem>(param_1,param_2);
  return;
}
