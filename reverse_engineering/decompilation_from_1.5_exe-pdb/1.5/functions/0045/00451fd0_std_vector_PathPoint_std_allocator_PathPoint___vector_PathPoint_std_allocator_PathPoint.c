/*
 * Entry: 00451fd0
 * Name: std::vector<PathPoint,std::allocator<PathPoint>_>::vector<PathPoint,std::allocator<PathPoint>_>
 * Namespace: std::vector<PathPoint,std::allocator<PathPoint>_>
 * Signature: vector<PathPoint,std::allocator<PathPoint>_> * vector<PathPoint,std::allocator<PathPoint>_>(vector<PathPoint,std::allocator<PathPoint>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

vector<PathPoint,std::allocator<PathPoint>_> * __thiscall
std::vector<PathPoint,std::allocator<PathPoint>_>::vector<PathPoint,std::allocator<PathPoint>_>
          (vector<PathPoint,std::allocator<PathPoint>_> *this)

{
  undefined4 *puVar1;
  
  puVar1 = operator_new(4);
  if (puVar1 != (undefined4 *)0x0) {
    *puVar1 = this;
    this->_padding_ = (int)puVar1;
    this->_Myfirst = (PathPoint *)0x0;
    this->_Mylast = (PathPoint *)0x0;
    this->_Myend = (PathPoint *)0x0;
    return this;
  }
  this->_padding_ = 0;
  this->_Myfirst = (PathPoint *)0x0;
  this->_Mylast = (PathPoint *)0x0;
  this->_Myend = (PathPoint *)0x0;
  return this;
}
