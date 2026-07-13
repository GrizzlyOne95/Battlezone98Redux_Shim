/*
 * Entry: 0045c30d
 * Name: SAVAttackVehicleTask::`scalar_deleting_destructor'
 * Namespace: SAVAttackVehicleTask
 * Signature: void * `scalar_deleting_destructor'(SAVAttackVehicleTask * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
SAVAttackVehicleTask::_scalar_deleting_destructor_(SAVAttackVehicleTask *this,uint param_1)

{
  ~SAVAttackVehicleTask(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
