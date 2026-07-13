/*
 * Entry: 004c479c
 * Name: ControlPanel::Cleanup
 * Namespace: ControlPanel
 * Signature: void Cleanup(ControlPanel * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ControlPanel::Cleanup(ControlPanel *this)

{
  int iVar1;
  long *plVar2;
  
  SelectNone(this);
  plVar2 = this->groupNum;
  for (iVar1 = 10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *plVar2 = 0;
    plVar2 = plVar2 + 1;
  }
  CleanupBuildItem(&buildMenu);
  return;
}
