/*
 * Entry: 00452900
 * Name: std::vector<PathPoint,std::allocator<PathPoint>_>::~vector<PathPoint,std::allocator<PathPoint>_>
 * Namespace: std::vector<PathPoint,std::allocator<PathPoint>_>
 * Signature: void ~vector<PathPoint,std::allocator<PathPoint>_>(vector<PathPoint,std::allocator<PathPoint>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<PathPoint,std::allocator<PathPoint>_>::~vector<PathPoint,std::allocator<PathPoint>_>
          (vector<PathPoint,std::allocator<PathPoint>_> *this)

{
  if (this->_Myfirst != (PathPoint *)0x0) {
    operator_delete(this->_Myfirst);
  }
  this->_Myfirst = (PathPoint *)0x0;
  this->_Mylast = (PathPoint *)0x0;
  this->_Myend = (PathPoint *)0x0;
  operator_delete((void *)this->_padding_);
  return;
}
