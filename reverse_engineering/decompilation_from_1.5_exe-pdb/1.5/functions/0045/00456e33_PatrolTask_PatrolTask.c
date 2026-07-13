/*
 * Entry: 00456e33
 * Name: PatrolTask::PatrolTask
 * Namespace: PatrolTask
 * Signature: PatrolTask * PatrolTask(PatrolTask * this, Craft * param_1, VECTOR_3D * param_2, goal_type_enum param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

PatrolTask * __thiscall
PatrolTask::PatrolTask(PatrolTask *this,Craft *param_1,VECTOR_3D *param_2,goal_type_enum param_3)

{
  _patrol_directions _Var1;
  
  GotoTask::GotoTask((GotoTask *)this,param_1,param_2);
  this->_padding_ = (int)&_vftable_;
  this->patrol_type = param_3;
  this->my_craft = param_1;
  _Var1 = rand();
  _Var1 = _Var1 & 0x80000007;
  if ((int)_Var1 < 0) {
    _Var1 = (_Var1 - PATROL_NE | 0xfffffff8) + PATROL_NE;
  }
  this->patrol_dir = _Var1;
  return this;
}
