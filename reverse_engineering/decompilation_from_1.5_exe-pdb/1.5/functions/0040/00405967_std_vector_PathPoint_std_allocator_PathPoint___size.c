/*
 * Entry: 00405967
 * Name: std::vector<PathPoint,std::allocator<PathPoint>_>::size
 * Namespace: std::vector<PathPoint,std::allocator<PathPoint>_>
 * Signature: uint size(vector<PathPoint,std::allocator<PathPoint>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uint __thiscall
std::vector<PathPoint,std::allocator<PathPoint>_>::size
          (vector<PathPoint,std::allocator<PathPoint>_> *this)

{
  return (int)this->_Mylast - (int)this->_Myfirst >> 4;
}
