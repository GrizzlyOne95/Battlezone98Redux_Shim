/*
 * Entry: 004511b0
 * Name: std::_Move_backward_opt<PathPoint_*,PathPoint_*,std::random_access_iterator_tag,std::_Undefined_move_tag>
 * Namespace: std
 * Signature: PathPoint * _Move_backward_opt<PathPoint_*,PathPoint_*,std::random_access_iterator_tag,std::_Undefined_move_tag>(PathPoint * param_1, PathPoint * param_2, PathPoint * param_3, random_access_iterator_tag param_4, _Undefined_move_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PathPoint * __cdecl
std::
_Move_backward_opt<PathPoint_*,PathPoint_*,std::random_access_iterator_tag,std::_Undefined_move_tag>
          (PathPoint *param_1,PathPoint *param_2,PathPoint *param_3,
          random_access_iterator_tag param_4,_Undefined_move_tag param_5,
          _Range_checked_iterator_tag param_6)

{
  PathPoint *pPVar1;
  
  pPVar1 = _Copy_backward_opt<PathPoint_*,PathPoint_*>
                     (param_1,param_2,param_3,param_4,(_Nonscalar_ptr_iterator_tag)0x0,
                      (_Range_checked_iterator_tag)0x0);
  return pPVar1;
}
