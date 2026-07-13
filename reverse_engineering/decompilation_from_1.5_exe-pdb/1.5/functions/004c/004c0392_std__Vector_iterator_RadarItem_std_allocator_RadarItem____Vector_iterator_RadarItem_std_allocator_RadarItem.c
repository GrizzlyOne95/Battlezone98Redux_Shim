/*
 * Entry: 004c0392
 * Name: std::_Vector_iterator<RadarItem,std::allocator<RadarItem>_>::_Vector_iterator<RadarItem,std::allocator<RadarItem>_>
 * Namespace: std::_Vector_iterator<RadarItem,std::allocator<RadarItem>_>
 * Signature: _Vector_iterator<RadarItem,std::allocator<RadarItem>_> * _Vector_iterator<RadarItem,std::allocator<RadarItem>_>(_Vector_iterator<RadarItem,std::allocator<RadarItem>_> * this, RadarItem * param_1, _Container_base_aux * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<RadarItem,std::allocator<RadarItem>_> * __thiscall
std::_Vector_iterator<RadarItem,std::allocator<RadarItem>_>::
_Vector_iterator<RadarItem,std::allocator<RadarItem>_>
          (_Vector_iterator<RadarItem,std::allocator<RadarItem>_> *this,RadarItem *param_1,
          _Container_base_aux *param_2)

{
  _Vector_const_iterator<RadarItem,std::allocator<RadarItem>_>::
  _Vector_const_iterator<RadarItem,std::allocator<RadarItem>_>
            ((_Vector_const_iterator<RadarItem,std::allocator<RadarItem>_> *)this,param_1,param_2);
  return this;
}
