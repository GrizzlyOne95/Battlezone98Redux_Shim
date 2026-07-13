/*
 * Entry: 004c0597
 * Name: std::sort<std::_Vector_iterator<RadarItem,std::allocator<RadarItem>_>_>
 * Namespace: std
 * Signature: void sort<std::_Vector_iterator<RadarItem,std::allocator<RadarItem>_>_>(_Vector_iterator<RadarItem,std::allocator<RadarItem>_> param_1, _Vector_iterator<RadarItem,std::allocator<RadarItem>_> param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::sort<std::_Vector_iterator<RadarItem,std::allocator<RadarItem>_>_>
          (_Vector_iterator<RadarItem,std::allocator<RadarItem>_> param_1,
          _Vector_iterator<RadarItem,std::allocator<RadarItem>_> param_2)

{
  int iVar1;
  
  iVar1 = _Vector_const_iterator<RadarItem,std::allocator<RadarItem>_>::operator-
                    ((_Vector_const_iterator<RadarItem,std::allocator<RadarItem>_> *)&param_2,
                     (_Vector_const_iterator<RadarItem,std::allocator<RadarItem>_> *)&param_1);
  _Sort<RadarItem_*,int>((RadarItem *)param_1._4_4_,(RadarItem *)param_2._4_4_,iVar1);
  return;
}
