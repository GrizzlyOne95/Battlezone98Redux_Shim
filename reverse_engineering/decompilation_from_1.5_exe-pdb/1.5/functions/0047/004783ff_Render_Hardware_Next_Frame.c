/*
 * Entry: 004783ff
 * Name: Render_Hardware_Next_Frame
 * Namespace: Global
 * Signature: void Render_Hardware_Next_Frame(CAMERA * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Render_Hardware_Next_Frame(CAMERA *param_1)

{
  tagENTITY *ptVar1;
  int iVar2;
  CAMERA *unaff_ESI;
  bool bVar3;
  tagENTITY *ptVar4;
  
  ptVar1 = get_user_entity();
  bVar3 = View_Record.Intenal_View != 0;
  if (D3D_Device_Lost != 0) {
    return;
  }
  iVar2 = IsWiggleBurgerOn();
  if (iVar2 != 0) {
    WiggleBurger(unaff_ESI);
  }
  Polygon_Counter = 0;
  Triangle_Counter = 0;
  Terrain_Polygon_Counter = 0;
  Batch_Counter = 0;
  Update_Rotator_Matrix(unaff_ESI);
  Begin_D3D_Scene(unaff_ESI);
  if (((View_Record.Current_View == OVER_VIEW) || (View_Record.Current_View == EDIT_VIEW)) ||
     (TerrainExposeMode != 0)) {
    (*Device.Refresh.BlitFill)(&Device,0);
  }
  if (((byte)D3IniFlags & 1) != 0) {
    RenderTargetView();
    RenderSniperView();
  }
  if (View_Record.Current_View != TWO_D_VIEW) {
    if (((View_Record.Current_View != OVER_VIEW) && (View_Record.Current_View != EDIT_VIEW)) &&
       (TerrainExposeMode == 0)) {
      Draw_Sky(unaff_ESI,0xdf,(uint)(UserProfilePtr->graphicDetail).clouds);
    }
    if (((View_Record.Current_View != TWO_D_VIEW) &&
        (Submit_Terrain_Mesh(unaff_ESI), View_Record.Current_View != TWO_D_VIEW)) &&
       (View_Record.Current_View != EDIT_VIEW)) {
      if (View_Record.Current_View == OVER_VIEW) {
        Submit_Overview_Entities(unaff_ESI);
      }
      else {
        ptVar4 = ptVar1;
        if (bVar3 == 0) {
          ptVar4 = (tagENTITY *)0x0;
        }
        Submit_All_Entities(unaff_ESI,ptVar4);
      }
      Ordnance_SubmitAll(unaff_ESI);
      Submit_Scrounge_Objects(unaff_ESI);
      GameFeature_SubmitAll(unaff_ESI);
    }
  }
  ZSORTDraw(unaff_ESI,1);
  RenderHUD(unaff_ESI,ptVar1,(uint)bVar3);
  End_D3D_Scene();
  return;
}
