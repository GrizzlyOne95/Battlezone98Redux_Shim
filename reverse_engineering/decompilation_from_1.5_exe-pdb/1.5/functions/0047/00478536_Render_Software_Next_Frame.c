/*
 * Entry: 00478536
 * Name: Render_Software_Next_Frame
 * Namespace: Global
 * Signature: void Render_Software_Next_Frame(CAMERA * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Render_Software_Next_Frame(CAMERA *param_1)

{
  uchar uVar1;
  tagENTITY *ptVar2;
  int iVar3;
  CAMERA *unaff_ESI;
  bool bVar4;
  tagENTITY *ptVar5;
  
  Polygon_Counter = 0;
  Triangle_Counter = 0;
  Terrain_Polygon_Counter = 0;
  Batch_Counter = 0;
  ptVar2 = get_user_entity();
  bVar4 = View_Record.Intenal_View != 0;
  Update_Rotator_Matrix(unaff_ESI);
  (*Device.VideoMode.LockBuffer)(&Device);
  if (View_Record.Current_View == OVER_VIEW) {
LAB_004785ea:
    (*Device.Refresh.BlitFill)(&Device,0);
  }
  else {
    if (View_Record.Current_View == TWO_D_VIEW) goto LAB_00478647;
    if (View_Record.Current_View == EDIT_VIEW) goto LAB_004785ea;
    uVar1 = UserPref_lineskip();
    if (uVar1 != '\0') {
      if ((FogDirection != 0) || ((UserProfilePtr->graphicDetail).clouds != '\0')) {
        (*Device.Refresh.BlitFill)(&Device,0);
      }
      EnableSkipLines(unaff_ESI,1,(uint)(View_Record.Current_View == COCKPIT_VIEW));
    }
    Draw_Sky(unaff_ESI,0xdf,(uint)(UserProfilePtr->graphicDetail).clouds);
  }
  if (((View_Record.Current_View != TWO_D_VIEW) &&
      (Submit_Terrain_Mesh(unaff_ESI), View_Record.Current_View != TWO_D_VIEW)) &&
     (View_Record.Current_View != EDIT_VIEW)) {
    if (View_Record.Current_View == OVER_VIEW) {
      Submit_Overview_Entities(unaff_ESI);
    }
    else {
      ptVar5 = ptVar2;
      if (!bVar4) {
        ptVar5 = (tagENTITY *)0x0;
      }
      Submit_All_Entities(unaff_ESI,ptVar5);
    }
    Ordnance_SubmitAll(unaff_ESI);
    Submit_Scrounge_Objects(unaff_ESI);
    GameFeature_SubmitAll(unaff_ESI);
  }
LAB_00478647:
  ZSORTDraw(unaff_ESI,1);
  if (((Cockpit_Visible != 0) && (ptVar2 != (tagENTITY *)0x0)) && (bVar4)) {
    Render_Entity_Cockpit(unaff_ESI,ptVar2);
  }
  uVar1 = UserPref_lineskip();
  if (uVar1 != '\0') {
    EnableSkipLines(unaff_ESI,0,0);
  }
  GameFeature_RenderAll();
  iVar3 = IsWiggleBurgerOn();
  if (iVar3 != 0) {
    WiggleBurger(unaff_ESI);
  }
  if (useDisplayInterface != 0) {
    if (hudFlags != 0) {
      Render_RadarBackdrop();
      Render_RadarMesh();
    }
    DisplayInterface_RenderAll();
  }
  Update_FPS();
  Show_framerate(&View_Record.MainCam);
  Scroll_Tick();
  TextInput_Update();
  iVar3 = Net_IsNetGame();
  if (iVar3 != 0) {
    Scores_DisplayScores();
  }
  (*Device.VideoMode.UnlockBuffer)(&Device);
  return;
}
