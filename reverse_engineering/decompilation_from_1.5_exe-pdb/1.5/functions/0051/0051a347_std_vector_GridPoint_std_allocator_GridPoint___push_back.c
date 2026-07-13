/*
 * Entry: 0051a347
 * Name: std::vector<GridPoint,std::allocator<GridPoint>_>::push_back
 * Namespace: std::vector<GridPoint,std::allocator<GridPoint>_>
 * Signature: void push_back(vector<GridPoint,std::allocator<GridPoint>_> * this, GridPoint * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<GridPoint,std::allocator<GridPoint>_>::push_back
          (vector<GridPoint,std::allocator<GridPoint>_> *this,GridPoint *param_1)

{
  _Vector_const_iterator<GridPoint,std::allocator<GridPoint>_> _Var1;
  uint uVar2;
  GridPoint *pGVar3;
  _Vector_const_iterator<GridPoint,std::allocator<GridPoint>_> local_c;
  
  pGVar3 = this->_Mylast;
  local_c._padding_ = (int)this;
  local_c._Myptr = (GridPoint *)this;
  uVar2 = capacity(this);
  if ((uint)((int)pGVar3 - (int)this->_Myfirst >> 3) < uVar2) {
    pGVar3 = _Ufill(this,pGVar3,1,param_1);
    this->_Mylast = pGVar3;
  }
  else {
    _Vector_const_iterator<GridPoint,std::allocator<GridPoint>_>::
    _Vector_const_iterator<GridPoint,std::allocator<GridPoint>_>
              (&local_c,pGVar3,(_Container_base_aux *)this);
    _Var1._Myptr = (GridPoint *)local_c._padding_;
    _Var1._padding_ = (int)&local_c;
    insert(this,_Var1,local_c._Myptr);
  }
  return;
}
