/*
 * Entry: 004540d0
 * Name: std::vector<PathPoint,std::allocator<PathPoint>_>::resize
 * Namespace: std::vector<PathPoint,std::allocator<PathPoint>_>
 * Signature: void resize(vector<PathPoint,std::allocator<PathPoint>_> * this, uint param_1, PathPoint param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
std::vector<PathPoint,std::allocator<PathPoint>_>::resize
          (vector<PathPoint,std::allocator<PathPoint>_> *this,uint param_1,PathPoint param_2)

{
  PathPoint *pPVar1;
  PathPoint *pPVar2;
  _Vector_const_iterator<PathPoint,std::allocator<PathPoint>_> _Var3;
  _Vector_const_iterator<PathPoint,std::allocator<PathPoint>_> _Var4;
  _Vector_const_iterator<PathPoint,std::allocator<PathPoint>_> _Var5;
  uint uVar6;
  _Vector_iterator<PathPoint,std::allocator<PathPoint>_> _Var7;
  undefined8 local_18;
  int local_10;
  undefined1 local_8 [8];
  
  pPVar1 = this->_Myfirst;
  pPVar2 = this->_Mylast;
  uVar6 = (int)pPVar2 - (int)pPVar1 >> 4;
  if (uVar6 < param_1) {
    if (pPVar2 < pPVar1) {
      _invalid_parameter_noinfo();
    }
    _Var5._Myptr = pPVar2;
    _Var5._padding_ = this->_padding_;
    _Insert_n(this,_Var5,param_1 - ((int)this->_Mylast - (int)this->_Myfirst >> 4),&param_2);
    return;
  }
  if (param_1 < uVar6) {
    if (pPVar2 < pPVar1) {
      _invalid_parameter_noinfo();
    }
    local_10 = this->_padding_;
    pPVar1 = this->_Myfirst;
    if (this->_Mylast < pPVar1) {
      _invalid_parameter_noinfo();
    }
    local_18._0_4_ = this->_padding_;
    local_18._4_4_ = pPVar1;
    _Var7 = _Vector_iterator<PathPoint,std::allocator<PathPoint>_>::operator+
                      ((_Vector_iterator<PathPoint,std::allocator<PathPoint>_> *)&local_18,
                       (int)local_8);
    _Var3._Myptr = (PathPoint *)*_Var7._0_4_;
    _Var3._padding_ = (int)&local_18 + 4;
    _Var4._Myptr = local_18._4_4_;
    _Var4._padding_ = _Var7._0_4_[1];
    erase(this,_Var3,_Var4);
  }
  return;
}
