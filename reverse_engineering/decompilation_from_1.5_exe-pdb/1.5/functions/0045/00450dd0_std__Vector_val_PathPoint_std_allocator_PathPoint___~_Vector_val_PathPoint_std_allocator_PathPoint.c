/*
 * Entry: 00450dd0
 * Name: std::_Vector_val<PathPoint,std::allocator<PathPoint>_>::~_Vector_val<PathPoint,std::allocator<PathPoint>_>
 * Namespace: std::_Vector_val<PathPoint,std::allocator<PathPoint>_>
 * Signature: void ~_Vector_val<PathPoint,std::allocator<PathPoint>_>(_Vector_val<PathPoint,std::allocator<PathPoint>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::_Vector_val<PathPoint,std::allocator<PathPoint>_>::
~_Vector_val<PathPoint,std::allocator<PathPoint>_>
          (_Vector_val<PathPoint,std::allocator<PathPoint>_> *this)

{
  operator_delete((void *)this->_padding_);
  return;
}
