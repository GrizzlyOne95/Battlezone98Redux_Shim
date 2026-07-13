/*
 * Entry: 004789c5
 * Name: Simulate
 * Namespace: Global
 * Signature: void Simulate(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Simulate(void)

{
  _OBJ76 *p_Var1;
  int iVar2;
  tagENTITY *ptVar3;
  float fVar4;
  
  iVar2 = UserPref_arcadeMode();
  if (iVar2 == 0) {
    ClassSimulateAll();
    if (0 < AnimObj_ActiveCount) {
      AnimObj_Simulate();
    }
    ClassPostSimulateAll();
    (*View_Record.Update_Camera)();
    GameObject_UpdateRange();
    Scrap_UpdateRange();
    GameObject_ComputeVisibility();
    fVar4 = TimeStep();
    GameFeature_SimulateAll(fVar4);
  }
  else {
    ptVar3 = get_user_entity();
    if (ptVar3 != (tagENTITY *)0x0) {
      ptVar3 = get_user_entity();
      p_Var1 = ptVar3->obj76;
      GameObject_CallAI(p_Var1);
      GameObject_Simulate(p_Var1);
    }
    ClassCleanAll();
    (*View_Record.Update_Camera)();
    GameObject_UpdateRange();
    Scrap_UpdateRange();
    GameObject_MarkAllVisible();
    fVar4 = TimeStep();
    Reticle_Simulate(fVar4);
  }
  DisplayInterface_SimulateAll();
  return;
}
