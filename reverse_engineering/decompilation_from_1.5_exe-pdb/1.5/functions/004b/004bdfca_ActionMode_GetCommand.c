/*
 * Entry: 004bdfca
 * Name: ActionMode::GetCommand
 * Namespace: ActionMode
 * Signature: AiCommand GetCommand(ActionMode * this, VECTOR_3D * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AiCommand __thiscall ActionMode::GetCommand(ActionMode *this,VECTOR_3D *param_1)

{
  GameObject *pGVar1;
  AiCommand AVar2;
  int iVar3;
  
  if (0 < controlPanel.selectNum) {
    pGVar1 = GameObject::GetObj(controlPanel.selectList[0]);
                    /* WARNING: Could not recover jumptable at 0x004bdfe3. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    AVar2 = (**(code **)(pGVar1->_padding_ + 0x30))();
    return AVar2;
  }
  iVar3 = ControlPanel::GetCurrentMode(&controlPanel);
  if ((iVar3 == 0) || (iVar3 != 1)) {
    AVar2 = CMD_NONE;
  }
  else {
    AVar2 = CMD_GO;
  }
  return AVar2;
}
