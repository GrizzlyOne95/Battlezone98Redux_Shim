/*
 * Entry: 004bff83
 * Name: std::_Vector_iterator<RadarItem,std::allocator<RadarItem>_>::operator++
 * Namespace: std::_Vector_iterator<RadarItem,std::allocator<RadarItem>_>
 * Signature: _Vector_iterator<RadarItem,std::allocator<RadarItem>_> * operator++(_Vector_iterator<RadarItem,std::allocator<RadarItem>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<RadarItem,std::allocator<RadarItem>_> * __thiscall
std::_Vector_iterator<RadarItem,std::allocator<RadarItem>_>::operator++
          (_Vector_iterator<RadarItem,std::allocator<RadarItem>_> *this)

{
  _Vector_const_iterator<RadarItem,std::allocator<RadarItem>_>::operator++
            ((_Vector_const_iterator<RadarItem,std::allocator<RadarItem>_> *)this);
  return this;
}
