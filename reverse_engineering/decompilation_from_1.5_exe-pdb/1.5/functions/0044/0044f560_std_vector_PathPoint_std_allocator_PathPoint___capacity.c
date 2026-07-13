/*
 * Entry: 0044f560
 * Name: std::vector<PathPoint,std::allocator<PathPoint>_>::capacity
 * Namespace: std::vector<PathPoint,std::allocator<PathPoint>_>
 * Signature: uint capacity(vector<PathPoint,std::allocator<PathPoint>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall
std::vector<PathPoint,std::allocator<PathPoint>_>::capacity
          (vector<PathPoint,std::allocator<PathPoint>_> *this)

{
  if (this->_Myfirst == (PathPoint *)0x0) {
    return 0;
  }
  return (int)this->_Myend - (int)this->_Myfirst >> 4;
}
