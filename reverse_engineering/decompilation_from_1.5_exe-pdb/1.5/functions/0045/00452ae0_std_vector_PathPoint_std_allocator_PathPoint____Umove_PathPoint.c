/*
 * Entry: 00452ae0
 * Name: std::vector<PathPoint,std::allocator<PathPoint>_>::_Umove<PathPoint_*>
 * Namespace: std::vector<PathPoint,std::allocator<PathPoint>_>
 * Signature: PathPoint * _Umove<PathPoint_*>(vector<PathPoint,std::allocator<PathPoint>_> * this, PathPoint * param_1, PathPoint * param_2, PathPoint * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PathPoint * __thiscall
std::vector<PathPoint,std::allocator<PathPoint>_>::_Umove<PathPoint_*>
          (vector<PathPoint,std::allocator<PathPoint>_> *this,PathPoint *param_1,PathPoint *param_2,
          PathPoint *param_3)

{
  PathPoint *pPVar1;
  
  pPVar1 = _Uninit_copy<PathPoint_*,PathPoint_*,std::allocator<PathPoint>_>
                     (param_1,param_2,param_3,(allocator<PathPoint> *)&this->_padding_,
                      SUB41(param_3,0),(_Range_checked_iterator_tag)0x0);
  return pPVar1;
}
