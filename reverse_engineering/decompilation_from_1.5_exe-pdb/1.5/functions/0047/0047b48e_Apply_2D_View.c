/*
 * Entry: 0047b48e
 * Name: Apply_2D_View
 * Namespace: Global
 * Signature: void Apply_2D_View(tagENTITY * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Apply_2D_View(tagENTITY *param_1)

{
  if (TerrainEdit != 0) {
    Cockpit_Visible = 0;
    View_Record.Intenal_View = 0;
    useDisplayInterface = 1;
    View_Record.Current_View = TWO_D_VIEW;
    View_Record.Update_Camera = Set_2D_View;
    View_Record.Camera_Owner = param_1;
    Camera_Set_Zoom(&View_Record.MainCam,1.0);
    SetControlMode(0);
  }
  return;
}
