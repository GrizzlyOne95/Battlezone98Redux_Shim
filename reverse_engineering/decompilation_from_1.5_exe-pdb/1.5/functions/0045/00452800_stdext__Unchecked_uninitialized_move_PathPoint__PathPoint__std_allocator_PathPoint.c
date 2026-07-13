/*
 * Entry: 00452800
 * Name: stdext::_Unchecked_uninitialized_move<PathPoint_*,PathPoint_*,std::allocator<PathPoint>_>
 * Namespace: stdext
 * Signature: PathPoint * _Unchecked_uninitialized_move<PathPoint_*,PathPoint_*,std::allocator<PathPoint>_>(PathPoint * param_1, PathPoint * param_2, PathPoint * param_3, allocator<PathPoint> * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PathPoint * __cdecl
stdext::_Unchecked_uninitialized_move<PathPoint_*,PathPoint_*,std::allocator<PathPoint>_>
          (PathPoint *param_1,PathPoint *param_2,PathPoint *param_3,allocator<PathPoint> *param_4)

{
  PathPoint *pPVar1;
  
  pPVar1 = std::_Uninit_copy<PathPoint_*,PathPoint_*,std::allocator<PathPoint>_>
                     (param_1,param_2,param_3,param_4,SUB41(param_3,0),
                      (_Range_checked_iterator_tag)0x0);
  return pPVar1;
}
