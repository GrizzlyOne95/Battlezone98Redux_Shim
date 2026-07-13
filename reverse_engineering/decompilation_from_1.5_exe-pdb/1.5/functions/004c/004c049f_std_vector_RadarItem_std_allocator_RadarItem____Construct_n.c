/*
 * Entry: 004c049f
 * Name: std::vector<RadarItem,std::allocator<RadarItem>_>::_Construct_n
 * Namespace: std::vector<RadarItem,std::allocator<RadarItem>_>
 * Signature: void _Construct_n(vector<RadarItem,std::allocator<RadarItem>_> * this, uint param_1, RadarItem * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<RadarItem,std::allocator<RadarItem>_>::_Construct_n
          (vector<RadarItem,std::allocator<RadarItem>_> *this,uint param_1,RadarItem *param_2)

{
  bool bVar1;
  RadarItem *pRVar2;
  
  bVar1 = _Buy(this,param_1);
  if (bVar1) {
    pRVar2 = _Ufill(this,this->_Myfirst,param_1,param_2);
    this->_Mylast = pRVar2;
  }
  return;
}
