/*
 * Entry: 005192ef
 * Name: std::vector<GridPoint,std::allocator<GridPoint>_>::_Ufill
 * Namespace: std::vector<GridPoint,std::allocator<GridPoint>_>
 * Signature: GridPoint * _Ufill(vector<GridPoint,std::allocator<GridPoint>_> * this, GridPoint * param_1, uint param_2, GridPoint * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GridPoint * __thiscall
std::vector<GridPoint,std::allocator<GridPoint>_>::_Ufill
          (vector<GridPoint,std::allocator<GridPoint>_> *this,GridPoint *param_1,uint param_2,
          GridPoint *param_3)

{
  stdext::
  unchecked_uninitialized_fill_n<GridPoint_*,unsigned_int,GridPoint,std::allocator<GridPoint>_>
            (param_1,param_2,param_3,(allocator<GridPoint> *)&this->_padding_);
  return param_1 + param_2;
}
