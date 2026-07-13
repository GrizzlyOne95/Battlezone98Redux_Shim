/*
 * Entry: 00456f61
 * Name: PatrolTask::Try_New_Patrol
 * Namespace: PatrolTask
 * Signature: int Try_New_Patrol(PatrolTask * this, float * param_1, float * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall PatrolTask::Try_New_Patrol(PatrolTask *this,float *param_1,float *param_2)

{
  int iVar1;
  VECTOR_3D VVar2;
  VECTOR_3D *pVVar3;
  int iVar4;
  int iVar5;
  goal_type_enum gVar6;
  
  iVar5 = Patrol_Offset_x[this->patrol_dir];
  iVar1 = Patrol_Offset_z[this->patrol_dir];
  pVVar3 = (VECTOR_3D *)(**(code **)(this->my_craft->_padding_ + 0xc))();
  gVar6 = this->patrol_type;
  VVar2 = *pVVar3;
  iVar4 = (**(code **)(this->my_craft->_padding_ + 4))();
  iVar5 = ScheduleGlue_Get_New_Patrol_Coords(VVar2,iVar5,iVar1,param_1,param_2,iVar4,gVar6);
  return iVar5;
}
