/*
 * Entry: 004bfcfa
 * Name: std::_Vector_const_iterator<RadarItem,std::allocator<RadarItem>_>::operator!=
 * Namespace: std::_Vector_const_iterator<RadarItem,std::allocator<RadarItem>_>
 * Signature: bool operator!=(_Vector_const_iterator<RadarItem,std::allocator<RadarItem>_> * this, _Vector_const_iterator<RadarItem,std::allocator<RadarItem>_> * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::_Vector_const_iterator<RadarItem,std::allocator<RadarItem>_>::operator!=
          (_Vector_const_iterator<RadarItem,std::allocator<RadarItem>_> *this,
          _Vector_const_iterator<RadarItem,std::allocator<RadarItem>_> *param_1)

{
  bool bVar1;
  
  bVar1 = operator==(this,param_1);
  return !bVar1;
}
