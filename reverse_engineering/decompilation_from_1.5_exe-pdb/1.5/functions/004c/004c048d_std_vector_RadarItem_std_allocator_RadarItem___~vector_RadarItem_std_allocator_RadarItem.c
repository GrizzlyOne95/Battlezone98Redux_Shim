/*
 * Entry: 004c048d
 * Name: std::vector<RadarItem,std::allocator<RadarItem>_>::~vector<RadarItem,std::allocator<RadarItem>_>
 * Namespace: std::vector<RadarItem,std::allocator<RadarItem>_>
 * Signature: void ~vector<RadarItem,std::allocator<RadarItem>_>(vector<RadarItem,std::allocator<RadarItem>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<RadarItem,std::allocator<RadarItem>_>::~vector<RadarItem,std::allocator<RadarItem>_>
          (vector<RadarItem,std::allocator<RadarItem>_> *this)

{
  _Tidy(this);
  operator_delete((void *)this->_padding_);
  return;
}
