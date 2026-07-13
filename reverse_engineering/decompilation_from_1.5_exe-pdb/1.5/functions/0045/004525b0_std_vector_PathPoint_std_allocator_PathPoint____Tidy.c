/*
 * Entry: 004525b0
 * Name: std::vector<PathPoint,std::allocator<PathPoint>_>::_Tidy
 * Namespace: std::vector<PathPoint,std::allocator<PathPoint>_>
 * Signature: void _Tidy(vector<PathPoint,std::allocator<PathPoint>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<PathPoint,std::allocator<PathPoint>_>::_Tidy
          (vector<PathPoint,std::allocator<PathPoint>_> *this)

{
  if (this->_Myfirst != (PathPoint *)0x0) {
    operator_delete(this->_Myfirst);
  }
  this->_Myfirst = (PathPoint *)0x0;
  this->_Mylast = (PathPoint *)0x0;
  this->_Myend = (PathPoint *)0x0;
  return;
}
