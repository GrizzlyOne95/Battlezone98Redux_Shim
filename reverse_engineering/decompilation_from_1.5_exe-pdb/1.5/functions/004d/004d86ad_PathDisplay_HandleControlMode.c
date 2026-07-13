/*
 * Entry: 004d86ad
 * Name: PathDisplay::HandleControlMode
 * Namespace: PathDisplay
 * Signature: void HandleControlMode(PathDisplay * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PathDisplay::HandleControlMode(PathDisplay *this)

{
  ControlMode CVar1;
  
  if (this->nextControlMode != ~CONTROL_PLAN) {
    if (this->controlMode == CONTROL_PLAN) {
      CleanControlPlan(this);
    }
    else if (this->controlMode == CONTROL_PATH) {
      CleanControlPath(this);
    }
    CVar1 = this->nextControlMode;
    this->nextControlMode = ~CONTROL_PLAN;
    this->controlMode = CVar1;
    if (CVar1 == CONTROL_PLAN) {
      InitControlPlan(this);
    }
    else if (CVar1 == CONTROL_PATH) {
      this->editSelect = 0;
    }
    else if (CVar1 == CONTROL_TASK) {
      InitControlTask(this);
    }
    else if (CVar1 == CONTROL_OBJECT) {
      this->taskWhoHandle = 0;
      (this->prevMousePos).y = 0;
    }
  }
  CVar1 = this->controlMode;
  if (CVar1 == CONTROL_PLAN) {
    DoControlPlan(this);
    return;
  }
  if (CVar1 == CONTROL_PATH) {
    DoControlPath(this);
    return;
  }
  if (CVar1 != CONTROL_TASK) {
    if (CVar1 == CONTROL_OBJECT) {
      DoControlObject(this);
      return;
    }
    return;
  }
  DoControlTask(this);
  return;
}
