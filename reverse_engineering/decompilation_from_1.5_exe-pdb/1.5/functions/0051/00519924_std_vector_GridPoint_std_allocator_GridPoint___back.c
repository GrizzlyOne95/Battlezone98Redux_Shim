/*
 * Entry: 00519924
 * Name: std::vector<GridPoint,std::allocator<GridPoint>_>::back
 * Namespace: std::vector<GridPoint,std::allocator<GridPoint>_>
 * Signature: GridPoint * back(vector<GridPoint,std::allocator<GridPoint>_> * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GridPoint * __thiscall
std::vector<GridPoint,std::allocator<GridPoint>_>::back
          (vector<GridPoint,std::allocator<GridPoint>_> *this)

{
  GridPoint *pGVar1;
  _Vector_iterator<GridPoint,std::allocator<GridPoint>_> _Var2;
  undefined1 local_14 [8];
  _Vector_const_iterator<GridPoint,std::allocator<GridPoint>_> local_c;
  
  _Vector_const_iterator<GridPoint,std::allocator<GridPoint>_>::
  _Vector_const_iterator<GridPoint,std::allocator<GridPoint>_>
            (&local_c,this->_Mylast,(_Container_base_aux *)this);
  _Var2 = _Vector_iterator<GridPoint,std::allocator<GridPoint>_>::operator-
                    ((_Vector_iterator<GridPoint,std::allocator<GridPoint>_> *)&local_c,
                     (int)local_14);
  pGVar1 = _Vector_const_iterator<GridPoint,std::allocator<GridPoint>_>::operator*(_Var2._0_4_);
  return pGVar1;
}
