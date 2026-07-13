/*
 * Entry: 00450a10
 * Name: std::_Copy_opt<PathPoint_*,PathPoint_*>
 * Namespace: std
 * Signature: PathPoint * _Copy_opt<PathPoint_*,PathPoint_*>(PathPoint * param_1, PathPoint * param_2, PathPoint * param_3, random_access_iterator_tag param_4, _Nonscalar_ptr_iterator_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PathPoint * __cdecl
std::_Copy_opt<PathPoint_*,PathPoint_*>
          (PathPoint *param_1,PathPoint *param_2,PathPoint *param_3,
          random_access_iterator_tag param_4,_Nonscalar_ptr_iterator_tag param_5,
          _Range_checked_iterator_tag param_6)

{
  int iVar1;
  int iVar2;
  
  iVar1 = (int)param_2 - (int)param_1;
  if (param_1 != param_2) {
    iVar2 = (int)param_3 - (int)param_1;
    do {
      *(float *)(iVar2 + (int)param_1) = (param_1->point).x;
      *(float *)(iVar2 + 4 + (int)param_1) = (param_1->point).z;
      *(Strip **)(iVar2 + 8 + (int)param_1) = param_1->strip;
      *(int *)(iVar2 + 0xc + (int)param_1) = param_1->seqNo;
      param_1 = param_1 + 1;
    } while (param_1 != param_2);
  }
  return param_3 + (iVar1 >> 4);
}
