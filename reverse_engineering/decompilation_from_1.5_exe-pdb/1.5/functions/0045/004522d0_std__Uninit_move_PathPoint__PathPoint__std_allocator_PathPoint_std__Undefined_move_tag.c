/*
 * Entry: 004522d0
 * Name: std::_Uninit_move<PathPoint_*,PathPoint_*,std::allocator<PathPoint>,std::_Undefined_move_tag>
 * Namespace: std
 * Signature: PathPoint * _Uninit_move<PathPoint_*,PathPoint_*,std::allocator<PathPoint>,std::_Undefined_move_tag>(PathPoint * param_1, PathPoint * param_2, PathPoint * param_3, allocator<PathPoint> * param_4, _Undefined_move_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PathPoint * __cdecl
std::_Uninit_move<PathPoint_*,PathPoint_*,std::allocator<PathPoint>,std::_Undefined_move_tag>
          (PathPoint *param_1,PathPoint *param_2,PathPoint *param_3,allocator<PathPoint> *param_4,
          _Undefined_move_tag param_5,_Range_checked_iterator_tag param_6)

{
  PathPoint *pPVar1;
  
  pPVar1 = _Uninit_copy<PathPoint_*,PathPoint_*,std::allocator<PathPoint>_>
                     (param_1,param_2,param_3,param_4,SUB41(param_3,0),
                      (_Range_checked_iterator_tag)0x0);
  return pPVar1;
}
