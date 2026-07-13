/*
 * Entry: 004525e0
 * Name: std::vector<PathPoint,std::allocator<PathPoint>_>::_Ufill
 * Namespace: std::vector<PathPoint,std::allocator<PathPoint>_>
 * Signature: PathPoint * _Ufill(vector<PathPoint,std::allocator<PathPoint>_> * this, PathPoint * param_1, uint param_2, PathPoint * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PathPoint * __thiscall
std::vector<PathPoint,std::allocator<PathPoint>_>::_Ufill
          (vector<PathPoint,std::allocator<PathPoint>_> *this,PathPoint *param_1,uint param_2,
          PathPoint *param_3)

{
  _Uninit_fill_n<PathPoint_*,unsigned_int,PathPoint,std::allocator<PathPoint>_>
            (param_1,param_2,param_3,(allocator<PathPoint> *)&this->_padding_,SUB41(param_3,0),
             (_Range_checked_iterator_tag)0x0);
  return param_1 + param_2;
}
