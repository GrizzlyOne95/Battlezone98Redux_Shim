/*
 * Entry: 00456fd8
 * Name: PatrolTask::Choose_Next_Spot
 * Namespace: PatrolTask
 * Signature: int Choose_Next_Spot(PatrolTask * this, VECTOR_3D * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall PatrolTask::Choose_Next_Spot(PatrolTask *this,VECTOR_3D *param_1)

{
  _patrol_directions *p_Var1;
  int iVar2;
  _patrol_directions _Var3;
  int iVar4;
  int iVar5;
  PatrolTask *local_c;
  PatrolTask *local_8;
  
  iVar5 = 0;
  iVar4 = 1;
  local_c = this;
  local_8 = this;
  do {
    if (7 < iVar5) {
      return 0;
    }
    iVar2 = Try_New_Patrol(this,(float *)&local_8,(float *)&local_c);
    if (iVar2 != 0) {
      param_1->x = (float)local_8;
      param_1->y = 0.0;
      param_1->z = (float)local_c;
      return iVar2;
    }
    iVar5 = iVar5 + 1;
    p_Var1 = &this->patrol_dir;
    *p_Var1 = *p_Var1 + iVar4 * iVar5;
    _Var3 = this->patrol_dir;
    if ((int)*p_Var1 < 0) {
      _Var3 = _Var3 + MAX_DIRECTIONS;
LAB_00457022:
      this->patrol_dir = _Var3;
    }
    else if (7 < (int)_Var3) {
      _Var3 = _Var3 - MAX_DIRECTIONS;
      goto LAB_00457022;
    }
    iVar4 = -iVar4;
  } while( true );
}
