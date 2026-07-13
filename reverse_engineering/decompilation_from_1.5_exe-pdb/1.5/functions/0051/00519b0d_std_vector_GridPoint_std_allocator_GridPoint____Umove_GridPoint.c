/*
 * Entry: 00519b0d
 * Name: std::vector<GridPoint,std::allocator<GridPoint>_>::_Umove<GridPoint_*>
 * Namespace: std::vector<GridPoint,std::allocator<GridPoint>_>
 * Signature: GridPoint * _Umove<GridPoint_*>(vector<GridPoint,std::allocator<GridPoint>_> * this, GridPoint * param_1, GridPoint * param_2, GridPoint * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GridPoint * __thiscall
std::vector<GridPoint,std::allocator<GridPoint>_>::_Umove<GridPoint_*>
          (vector<GridPoint,std::allocator<GridPoint>_> *this,GridPoint *param_1,GridPoint *param_2,
          GridPoint *param_3)

{
  GridPoint *pGVar1;
  
  pGVar1 = stdext::unchecked_uninitialized_copy<GridPoint_*,GridPoint_*,std::allocator<GridPoint>_>
                     (param_1,param_2,param_3,(allocator<GridPoint> *)&this->_padding_);
  return pGVar1;
}
