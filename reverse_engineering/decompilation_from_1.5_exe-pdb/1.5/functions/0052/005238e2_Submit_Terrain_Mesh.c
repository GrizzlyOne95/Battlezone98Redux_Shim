/*
 * Entry: 005238e2
 * Name: Submit_Terrain_Mesh
 * Namespace: Global
 * Signature: void Submit_Terrain_Mesh(CAMERA * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Submit_Terrain_Mesh(CAMERA *param_1)

{
  CAMERAS_TYPES CVar1;
  CAMERA *unaff_EDI;
  
  Set_Rounding((int)unaff_EDI);
  CVar1 = View_Record.Current_View;
  if (View_Record.Current_View != TerrainView.Current_View) {
    SelectTerrainView(View_Record.Current_View);
  }
  Terrain.Vertex_Counter = 0;
  Terrain.Camera = param_1;
  Terrain.Shade_Type = 1;
  Terrain.Eye_Point.x = (float)param_1->View_Pyramid[0].x * Terrain.Grid_Scale;
  Terrain.Eye_Point.z = Terrain.Grid_Scale * (float)param_1->View_Pyramid[0].z;
  Terrain.Eye_Point.y = (float)param_1->View_Pyramid[0].y * 10.0;
  if (CVar1 == OVER_VIEW) {
    BuildTerrainOverview(unaff_EDI);
  }
  else if (TerrainWireFrame == 0) {
    if ((param_1 == &View_Record.MainCam) && (TerrainExposeMode != 0)) {
      BuildTerrainExpose(unaff_EDI);
      TerrainExposeMode = 0;
    }
    else {
      BuildTerrainPolys(param_1);
    }
  }
  else {
    BuildTerrainWireFrame(unaff_EDI);
  }
  Submit_AnimatedScrounge(param_1);
  Set_Rounding((int)param_1);
  return;
}
