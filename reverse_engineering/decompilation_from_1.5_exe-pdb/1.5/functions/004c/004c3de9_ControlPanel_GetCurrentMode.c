/*
 * Entry: 004c3de9
 * Name: ControlPanel::GetCurrentMode
 * Namespace: ControlPanel
 * Signature: int GetCurrentMode(ControlPanel * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall ControlPanel::GetCurrentMode(ControlPanel *this)

{
  int iVar1;
  
  iVar1 = 0;
  if (command_controls.cmd_multi == '\0') {
    iVar1 = this->currentMode;
  }
  return iVar1;
}
