/*
 * Entry: 004c0573
 * Name: std::vector<RadarItem,std::allocator<RadarItem>_>::vector<RadarItem,std::allocator<RadarItem>_>
 * Namespace: std::vector<RadarItem,std::allocator<RadarItem>_>
 * Signature: vector<RadarItem,std::allocator<RadarItem>_> * vector<RadarItem,std::allocator<RadarItem>_>(vector<RadarItem,std::allocator<RadarItem>_> * this, uint param_1, RadarItem * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

vector<RadarItem,std::allocator<RadarItem>_> * __thiscall
std::vector<RadarItem,std::allocator<RadarItem>_>::vector<RadarItem,std::allocator<RadarItem>_>
          (vector<RadarItem,std::allocator<RadarItem>_> *this,uint param_1,RadarItem *param_2)

{
  _Vector_val<RadarItem,std::allocator<RadarItem>_>::
  _Vector_val<RadarItem,std::allocator<RadarItem>_>
            ((_Vector_val<RadarItem,std::allocator<RadarItem>_> *)this,SUB41(this,0));
  _Construct_n(this,param_1,param_2);
  return this;
}
