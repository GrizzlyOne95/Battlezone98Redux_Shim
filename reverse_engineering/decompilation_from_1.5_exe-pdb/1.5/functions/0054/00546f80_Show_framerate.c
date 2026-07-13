/*
 * Entry: 00546f80
 * Name: Show_framerate
 * Namespace: Global
 * Signature: void Show_framerate(CAMERA * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Show_framerate(CAMERA *param_1)

{
  _GRAPHIC_BUFFER *p_Var1;
  float fVar2;
  int iVar3;
  float fVar4;
  
  if (Frame_Rate_On != 0) {
    Frames = Frames + 1.0;
    p_Var1 = param_1->Buffer;
    Total_Polygons = (float)Polygon_Counter + Total_Polygons;
    Total_Terrain_Polygons = (float)Terrain_Polygon_Counter + Total_Terrain_Polygons;
    Total_Triangles = (float)Triangle_Counter + Total_Triangles;
    Total_Batches = (float)Batch_Counter + Total_Batches;
    if (10.0 < Frames != (Frames == 10.0)) {
      fVar4 = Get_Time();
      fVar2 = Frames / (fVar4 - Time0);
      FrameAmount = FrameAmount + 1.0;
      if (JustToggledOn == 0) {
        if (HighestFrame < fVar2) {
          HighestFrame = fVar2;
        }
        if (fVar2 < LowestFrame) {
          LowestFrame = fVar2;
        }
        TotalFrameRate = TotalFrameRate + fVar2;
        Time0 = fVar4;
        sprintf(Speed,"FPS %6.2f (Low %6.2f Avg %6.2f)",(double)fVar2,(double)LowestFrame,
                (double)(TotalFrameRate / FrameAmount));
      }
      else {
        if (4.0 < FrameAmount) {
          JustToggledOn = 0;
          FrameAmount = 0.0;
        }
        HighestFrame = 0.0;
        LowestFrame = 100.0;
        TotalFrameRate = 0.0;
        Time0 = Get_Time();
      }
      fVar2 = 1.0 / Frames;
      Total_Polygons = Total_Polygons * fVar2;
      Total_Terrain_Polygons = fVar2 * Total_Terrain_Polygons;
      Total_Triangles = fVar2 * Total_Triangles;
      Total_Batches = fVar2 * Total_Batches;
      if (useD3D == 0) {
        fVar2 = Total_Terrain_Polygons + Total_Polygons;
      }
      else {
        sprintf(lp_Sub_Poly,"Triangles %5.0f (%5.0f batches)",(double)Total_Triangles,
                (double)Total_Batches);
        sprintf(lp_D3DText,"Texture: mem=%d(of %d) load=%d replace=%d flush=%d %c%c%c-%d",
                (int)(D3DTextMem + (D3DTextMem >> 0x1f & 0x3ffU)) >> 10,
                d3dappi.TextureTotalMem >> 10,D3DTextLoads,D3DTextMisses,D3DTextFlushes,
                ~(D3IniFlags << 4) & 0x20U | 0x41,~((uint)D3IniFlags >> 9) & 0x20 | 0x4d,
                (uint)((D3IniFlags & 8U) != 0) * 8 + 8);
        fVar2 = Total_Polygons;
      }
      sprintf(lp_Poly,"TerrPoly %5.0f TotalPoly %5.0f Snd Mem %8.0f",(double)Total_Terrain_Polygons,
              (double)fVar2,(double)UsedMemory);
      Frames = 0.0;
      Total_Polygons = 0.0;
      Total_Terrain_Polygons = 0.0;
      Total_Triangles = 0.0;
      Total_Batches = 0.0;
    }
    iVar3 = Default_Font->char_height;
    Font_Set_Foreground(Default_Font,fgFPS);
    Font_Print_String(Default_Font,p_Var1,0xdc,10,Speed);
    Font_Print_String(Default_Font,p_Var1,0xdc,iVar3 + 0xe,lp_Poly);
    if (useD3D != 0) {
      Font_Print_String(Default_Font,p_Var1,0xdc,iVar3 + 0xe + iVar3 + 4,lp_Sub_Poly);
      Font_Print_String(Default_Font,p_Var1,0xdc,(iVar3 + 4) * 3 + 10,lp_D3DText);
    }
    iVar3 = Mono_IsActive(Mono_Handle);
    if ((iVar3 != 0) && (Mono_Line(Mono_Handle,1,7,7,lp_Poly), useD3D != 0)) {
      Mono_Line(Mono_Handle,1,8,7,lp_Sub_Poly);
    }
  }
  return;
}
