/*
 * Entry: 0056d95f
 * Name: fsm_push_camera
 * Namespace: Global
 * Signature: void fsm_push_camera(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl fsm_push_camera(void)

{
  int iVar1;
  
  iVar1 = Push_Camera();
  if (iVar1 == 0) {
    DEBUG_systemError("Fsm error: Camera Stack Underfow");
  }
  Camera_Record.End_Path = 0;
  Camera_Record.Last_Path = (void *)0x0;
  Camera_Record.Last_Fnct = fsm_push_camera;
  Camera_Set_Clipping_Rect
            (&View_Record.MainCam,((View_Record.MainCam.Buffer)->Pane).x0,0,
             ((View_Record.MainCam.Buffer)->Pane).x1,(View_Record.MainCam.Buffer)->Height);
  View_Record.Intenal_View = 0;
  View_Record.Current_View = FSM_CAMERA_CONTROL;
  View_Record.Update_Camera = Fsm_Do_Nothing;
  return;
}
