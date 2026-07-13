/*
 * Entry: 00408a32
 * Name: std::_Vector_iterator<PathPoint,std::allocator<PathPoint>_>::operator++
 * Namespace: std::_Vector_iterator<PathPoint,std::allocator<PathPoint>_>
 * Signature: _Vector_iterator<PathPoint,std::allocator<PathPoint>_> * operator++(_Vector_iterator<PathPoint,std::allocator<PathPoint>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_Vector_iterator<PathPoint,std::allocator<PathPoint>_> * __thiscall
std::_Vector_iterator<PathPoint,std::allocator<PathPoint>_>::operator++
          (_Vector_iterator<PathPoint,std::allocator<PathPoint>_> *this)

{
  _Vector_const_iterator<PathPoint,std::allocator<PathPoint>_>::operator++
            ((_Vector_const_iterator<PathPoint,std::allocator<PathPoint>_> *)this);
  return this;
}
