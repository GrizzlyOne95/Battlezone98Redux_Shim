/*
 * Entry: 004bffb5
 * Name: std::allocator<RadarItem>::allocate
 * Namespace: std::allocator<RadarItem>
 * Signature: RadarItem * allocate(allocator<RadarItem> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

RadarItem * __thiscall std::allocator<RadarItem>::allocate(allocator<RadarItem> *this,uint param_1)

{
  RadarItem *pRVar1;
  
  pRVar1 = _Allocate<RadarItem>(param_1,(RadarItem *)0x0);
  return pRVar1;
}
