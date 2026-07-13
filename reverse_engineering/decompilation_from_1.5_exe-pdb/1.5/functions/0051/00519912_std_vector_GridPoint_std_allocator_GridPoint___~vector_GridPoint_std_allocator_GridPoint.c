/*
 * Entry: 00519912
 * Name: std::vector<GridPoint,std::allocator<GridPoint>_>::~vector<GridPoint,std::allocator<GridPoint>_>
 * Namespace: std::vector<GridPoint,std::allocator<GridPoint>_>
 * Signature: void ~vector<GridPoint,std::allocator<GridPoint>_>(vector<GridPoint,std::allocator<GridPoint>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<GridPoint,std::allocator<GridPoint>_>::~vector<GridPoint,std::allocator<GridPoint>_>
          (vector<GridPoint,std::allocator<GridPoint>_> *this)

{
  _Tidy(this);
  operator_delete((void *)this->_padding_);
  return;
}
