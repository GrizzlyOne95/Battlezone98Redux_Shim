/*
 * Entry: 00455e90
 * Name: Splice
 * Namespace: Global
 * Signature: PathPlan * Splice(PathPlan * param_1, PathPlan * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PathPlan * __cdecl Splice(PathPlan *param_1,PathPlan *param_2)

{
  PathPoint *pPVar1;
  int *piVar2;
  int in_EAX;
  PathPlan *this;
  int in_ECX;
  int iVar3;
  uint uVar4;
  PathPlan *local_c;
  
  this = MemoryPool::Alloc(&planPool);
  iVar3 = 0;
  if (this == (PathPlan *)0x0) {
    local_c = (PathPlan *)0x0;
  }
  else {
    local_c = PathPlan::PathPlan(this);
  }
  local_c->flags = 0;
  local_c->curPoint = 0;
  uVar4 = 0;
  if (*(int *)(in_ECX + 0x14) - *(int *)(in_ECX + 0x10) >> 4 != 0) {
    do {
      if ((uint)(*(int *)(in_ECX + 0x14) - *(int *)(in_ECX + 0x10) >> 4) <= uVar4) {
        _invalid_parameter_noinfo();
      }
      std::vector<PathPoint,std::allocator<PathPoint>_>::push_back
                (&local_c->points,(PathPoint *)(*(int *)(in_ECX + 0x10) + iVar3));
      uVar4 = uVar4 + 1;
      iVar3 = iVar3 + 0x10;
    } while (uVar4 < (uint)(*(int *)(in_ECX + 0x14) - *(int *)(in_ECX + 0x10) >> 4));
  }
  uVar4 = 0;
  if (*(int *)(in_EAX + 0x14) - *(int *)(in_EAX + 0x10) >> 4 != 0) {
    iVar3 = 0;
    do {
      if ((uint)(*(int *)(in_EAX + 0x14) - *(int *)(in_EAX + 0x10) >> 4) <= uVar4) {
        _invalid_parameter_noinfo();
      }
      std::vector<PathPoint,std::allocator<PathPoint>_>::push_back
                (&local_c->points,(PathPoint *)(*(int *)(in_EAX + 0x10) + iVar3));
      uVar4 = uVar4 + 1;
      iVar3 = iVar3 + 0x10;
    } while (uVar4 < (uint)(*(int *)(in_EAX + 0x14) - *(int *)(in_EAX + 0x10) >> 4));
  }
  local_c->curPoint = 0;
  pPVar1 = (local_c->points)._Mylast;
  if (pPVar1 < (local_c->points)._Myfirst) {
    _invalid_parameter_noinfo();
  }
  piVar2 = (int *)(local_c->points)._padding_;
  if (piVar2 == (int *)0x0) {
    _invalid_parameter_noinfo();
    iVar3 = 0;
  }
  else {
    iVar3 = *piVar2;
  }
  if (pPVar1 + -1 <= *(PathPoint **)(iVar3 + 0x10)) {
    if (piVar2 == (int *)0x0) {
      iVar3 = 0;
    }
    else {
      iVar3 = *piVar2;
    }
    if (*(PathPoint **)(iVar3 + 0xc) <= pPVar1 + -1) goto LAB_00455fb1;
  }
  _invalid_parameter_noinfo();
LAB_00455fb1:
  if (piVar2 == (int *)0x0) {
    _invalid_parameter_noinfo();
    iVar3 = 0;
  }
  else {
    iVar3 = *piVar2;
  }
  if (*(PathPoint **)(iVar3 + 0x10) <= pPVar1 + -1) {
    _invalid_parameter_noinfo();
  }
  (local_c->goal).x = pPVar1[-1].point.x;
  (local_c->goal).z = pPVar1[-1].point.z;
  return local_c;
}
