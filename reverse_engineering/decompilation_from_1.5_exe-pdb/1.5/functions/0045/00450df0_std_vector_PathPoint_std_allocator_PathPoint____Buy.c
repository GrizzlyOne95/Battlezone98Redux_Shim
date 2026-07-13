/*
 * Entry: 00450df0
 * Name: std::vector<PathPoint,std::allocator<PathPoint>_>::_Buy
 * Namespace: std::vector<PathPoint,std::allocator<PathPoint>_>
 * Signature: bool _Buy(vector<PathPoint,std::allocator<PathPoint>_> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
std::vector<PathPoint,std::allocator<PathPoint>_>::_Buy
          (vector<PathPoint,std::allocator<PathPoint>_> *this,uint param_1)

{
  PathPoint *pPVar1;
  
  this->_Myfirst = (PathPoint *)0x0;
  this->_Mylast = (PathPoint *)0x0;
  this->_Myend = (PathPoint *)0x0;
  if (param_1 == 0) {
    return false;
  }
  if (0xfffffff < param_1) {
    _Xlen();
    return true;
  }
  pPVar1 = _Allocate<PathPoint>(param_1,(PathPoint *)0x0);
  this->_Myfirst = pPVar1;
  this->_Mylast = pPVar1;
  this->_Myend = pPVar1 + param_1;
  return true;
}
