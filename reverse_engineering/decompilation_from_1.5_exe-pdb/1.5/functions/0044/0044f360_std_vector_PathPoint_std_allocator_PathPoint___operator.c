/*
 * Entry: 0044f360
 * Name: std::vector<PathPoint,std::allocator<PathPoint>_>::operator[]
 * Namespace: std::vector<PathPoint,std::allocator<PathPoint>_>
 * Signature: PathPoint * operator[](vector<PathPoint,std::allocator<PathPoint>_> * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PathPoint * __thiscall
std::vector<PathPoint,std::allocator<PathPoint>_>::operator[]
          (vector<PathPoint,std::allocator<PathPoint>_> *this,uint param_1)

{
  if ((uint)((int)this->_Mylast - (int)this->_Myfirst >> 4) <= param_1) {
    _invalid_parameter_noinfo();
  }
  return this->_Myfirst + param_1;
}
