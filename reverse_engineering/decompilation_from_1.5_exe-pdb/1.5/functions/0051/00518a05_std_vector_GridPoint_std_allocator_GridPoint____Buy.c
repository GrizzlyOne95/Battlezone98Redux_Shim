/*
 * Entry: 00518a05
 * Name: std::vector<GridPoint,std::allocator<GridPoint>_>::_Buy
 * Namespace: std::vector<GridPoint,std::allocator<GridPoint>_>
 * Signature: bool _Buy(vector<GridPoint,std::allocator<GridPoint>_> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::vector<GridPoint,std::allocator<GridPoint>_>::_Buy
          (vector<GridPoint,std::allocator<GridPoint>_> *this,uint param_1)

{
  bool bVar1;
  GridPoint *pGVar2;
  
  this->_Myfirst = (GridPoint *)0x0;
  this->_Mylast = (GridPoint *)0x0;
  this->_Myend = (GridPoint *)0x0;
  if (param_1 == 0) {
    bVar1 = false;
  }
  else {
    if (param_1 < 0x20000000) {
      pGVar2 = _Allocate<GridPoint>(param_1,(GridPoint *)0x0);
      this->_Myfirst = pGVar2;
      this->_Mylast = pGVar2;
      this->_Myend = pGVar2 + param_1;
    }
    else {
      _Xlen();
    }
    bVar1 = true;
  }
  return bVar1;
}
