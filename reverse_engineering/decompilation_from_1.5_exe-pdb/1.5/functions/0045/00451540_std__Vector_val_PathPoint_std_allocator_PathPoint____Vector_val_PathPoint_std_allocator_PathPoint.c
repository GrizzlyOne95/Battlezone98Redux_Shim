/*
 * Entry: 00451540
 * Name: std::_Vector_val<PathPoint,std::allocator<PathPoint>_>::_Vector_val<PathPoint,std::allocator<PathPoint>_>
 * Namespace: std::_Vector_val<PathPoint,std::allocator<PathPoint>_>
 * Signature: _Vector_val<PathPoint,std::allocator<PathPoint>_> * _Vector_val<PathPoint,std::allocator<PathPoint>_>(_Vector_val<PathPoint,std::allocator<PathPoint>_> * this, allocator<PathPoint> param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_val<PathPoint,std::allocator<PathPoint>_> * __thiscall
std::_Vector_val<PathPoint,std::allocator<PathPoint>_>::
_Vector_val<PathPoint,std::allocator<PathPoint>_>
          (_Vector_val<PathPoint,std::allocator<PathPoint>_> *this,allocator<PathPoint> param_1)

{
  undefined4 *puVar1;
  
  puVar1 = operator_new(4);
  if (puVar1 != (undefined4 *)0x0) {
    *puVar1 = this;
    this->_padding_ = (int)puVar1;
    return this;
  }
  this->_padding_ = 0;
  return this;
}
