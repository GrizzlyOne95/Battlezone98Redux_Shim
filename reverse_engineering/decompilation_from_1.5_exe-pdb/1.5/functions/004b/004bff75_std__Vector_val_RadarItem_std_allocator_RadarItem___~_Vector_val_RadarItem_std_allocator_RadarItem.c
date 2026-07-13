/*
 * Entry: 004bff75
 * Name: std::_Vector_val<RadarItem,std::allocator<RadarItem>_>::~_Vector_val<RadarItem,std::allocator<RadarItem>_>
 * Namespace: std::_Vector_val<RadarItem,std::allocator<RadarItem>_>
 * Signature: void ~_Vector_val<RadarItem,std::allocator<RadarItem>_>(_Vector_val<RadarItem,std::allocator<RadarItem>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_Vector_val<RadarItem,std::allocator<RadarItem>_>::
~_Vector_val<RadarItem,std::allocator<RadarItem>_>
          (_Vector_val<RadarItem,std::allocator<RadarItem>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
