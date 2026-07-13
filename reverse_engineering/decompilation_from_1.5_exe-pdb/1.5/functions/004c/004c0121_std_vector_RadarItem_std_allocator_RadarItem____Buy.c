/*
 * Entry: 004c0121
 * Name: std::vector<RadarItem,std::allocator<RadarItem>_>::_Buy
 * Namespace: std::vector<RadarItem,std::allocator<RadarItem>_>
 * Signature: bool _Buy(vector<RadarItem,std::allocator<RadarItem>_> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::vector<RadarItem,std::allocator<RadarItem>_>::_Buy
          (vector<RadarItem,std::allocator<RadarItem>_> *this,uint param_1)

{
  bool bVar1;
  RadarItem *pRVar2;
  
  this->_Myfirst = (RadarItem *)0x0;
  this->_Mylast = (RadarItem *)0x0;
  this->_Myend = (RadarItem *)0x0;
  if (param_1 == 0) {
    bVar1 = false;
  }
  else {
    if (param_1 < 0x20000000) {
      pRVar2 = _Allocate<RadarItem>(param_1,(RadarItem *)0x0);
      this->_Myfirst = pRVar2;
      this->_Mylast = pRVar2;
      this->_Myend = pRVar2 + param_1;
    }
    else {
      _Xlen();
    }
    bVar1 = true;
  }
  return bVar1;
}
