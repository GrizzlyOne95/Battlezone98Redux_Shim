/*
 * Entry: 0056d7fa
 * Name: fsm_pop_camera
 * Namespace: Global
 * Signature: void fsm_pop_camera(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl fsm_pop_camera(void)

{
  int iVar1;
  
  iVar1 = Pop_Camera();
  if (iVar1 == 0) {
    DEBUG_systemWarning("Fsm error: Camera Stack 0verfow");
  }
  Camera_Record.End_Path = 0;
  Camera_Record.Last_Path = (void *)0x0;
  Camera_Record.Last_Fnct = fsm_pop_camera;
  return;
}
