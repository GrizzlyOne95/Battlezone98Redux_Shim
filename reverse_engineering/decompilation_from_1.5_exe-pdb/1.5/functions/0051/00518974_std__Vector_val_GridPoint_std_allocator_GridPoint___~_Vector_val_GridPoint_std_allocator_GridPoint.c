/*
 * Entry: 00518974
 * Name: std::_Vector_val<GridPoint,std::allocator<GridPoint>_>::~_Vector_val<GridPoint,std::allocator<GridPoint>_>
 * Namespace: std::_Vector_val<GridPoint,std::allocator<GridPoint>_>
 * Signature: void ~_Vector_val<GridPoint,std::allocator<GridPoint>_>(_Vector_val<GridPoint,std::allocator<GridPoint>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_Vector_val<GridPoint,std::allocator<GridPoint>_>::
~_Vector_val<GridPoint,std::allocator<GridPoint>_>
          (_Vector_val<GridPoint,std::allocator<GridPoint>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
