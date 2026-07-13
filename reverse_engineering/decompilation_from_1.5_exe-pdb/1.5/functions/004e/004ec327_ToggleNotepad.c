/*
 * Entry: 004ec327
 * Name: ToggleNotepad
 * Namespace: Global
 * Signature: void ToggleNotepad(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ToggleNotepad(void)

{
  _gas_object *p_Var1;
  int iVar2;
  
  if (ScreenMode == SCREENMODE_NOTEPAD) {
    p_Var1 = FindGASObject("cnote.wav",(_OBJ76 *)0x0);
    StopGASEvent(p_Var1);
    DeleteNotepad();
    UnPauseGAS();
    SetScreenMode(SCREENMODE_SIM);
    EnableForceFeedback();
    return;
  }
  iVar2 = InitNotepad();
  if (iVar2 != 0) {
    PauseGAS();
    SetScreenMode(SCREENMODE_NOTEPAD);
    DisableForceFeedback();
    return;
  }
  return;
}
