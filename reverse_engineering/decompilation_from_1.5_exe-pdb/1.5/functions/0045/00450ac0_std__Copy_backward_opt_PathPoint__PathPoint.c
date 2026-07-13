/*
 * Entry: 00450ac0
 * Name: std::_Copy_backward_opt<PathPoint_*,PathPoint_*>
 * Namespace: std
 * Signature: PathPoint * _Copy_backward_opt<PathPoint_*,PathPoint_*>(PathPoint * param_1, PathPoint * param_2, PathPoint * param_3, random_access_iterator_tag param_4, _Nonscalar_ptr_iterator_tag param_5, _Range_checked_iterator_tag param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PathPoint * __cdecl
std::_Copy_backward_opt<PathPoint_*,PathPoint_*>
          (PathPoint *param_1,PathPoint *param_2,PathPoint *param_3,
          random_access_iterator_tag param_4,_Nonscalar_ptr_iterator_tag param_5,
          _Range_checked_iterator_tag param_6)

{
  PathPoint *pPVar1;
  PathPoint *pPVar2;
  int iVar3;
  
  if (param_1 != param_2) {
    iVar3 = (int)param_3 - (int)param_2;
    pPVar1 = param_2;
    do {
      pPVar2 = pPVar1 + -1;
      *(float *)(iVar3 + (int)pPVar2) = pPVar1[-1].point.x;
      *(float *)(iVar3 + 4 + (int)pPVar2) = pPVar1[-1].point.z;
      *(Strip **)(iVar3 + 8 + (int)pPVar2) = pPVar1[-1].strip;
      *(int *)(iVar3 + 0xc + (int)pPVar2) = pPVar1[-1].seqNo;
      pPVar1 = pPVar2;
    } while (pPVar2 != param_1);
  }
  return param_3 + -((int)param_2 - (int)param_1 >> 4);
}
