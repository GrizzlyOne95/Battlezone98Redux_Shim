/*
 * Entry: 004c0464
 * Name: std::vector<RadarItem,std::allocator<RadarItem>_>::_Ufill
 * Namespace: std::vector<RadarItem,std::allocator<RadarItem>_>
 * Signature: RadarItem * _Ufill(vector<RadarItem,std::allocator<RadarItem>_> * this, RadarItem * param_1, uint param_2, RadarItem * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

RadarItem * __thiscall
std::vector<RadarItem,std::allocator<RadarItem>_>::_Ufill
          (vector<RadarItem,std::allocator<RadarItem>_> *this,RadarItem *param_1,uint param_2,
          RadarItem *param_3)

{
  stdext::
  unchecked_uninitialized_fill_n<RadarItem_*,unsigned_int,RadarItem,std::allocator<RadarItem>_>
            (param_1,param_2,param_3,(allocator<RadarItem> *)&this->_padding_);
  return param_1 + param_2;
}
