/*
 * Entry: 004510c0
 * Name: stdext::unchecked_copy<PathPoint_*,PathPoint_*>
 * Namespace: stdext
 * Signature: PathPoint * unchecked_copy<PathPoint_*,PathPoint_*>(PathPoint * param_1, PathPoint * param_2, PathPoint * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PathPoint * __cdecl
stdext::unchecked_copy<PathPoint_*,PathPoint_*>
          (PathPoint *param_1,PathPoint *param_2,PathPoint *param_3)

{
  PathPoint *pPVar1;
  
  pPVar1 = std::_Copy_opt<PathPoint_*,PathPoint_*>
                     (param_1,param_2,param_3,SUB41(param_2,0),
                      (_Nonscalar_ptr_iterator_tag)SUB41(param_2,0),(_Range_checked_iterator_tag)0x0
                     );
  return pPVar1;
}
