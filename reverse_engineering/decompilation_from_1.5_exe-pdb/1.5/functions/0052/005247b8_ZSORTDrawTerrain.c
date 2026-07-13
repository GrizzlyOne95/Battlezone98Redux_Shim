/*
 * Entry: 005247b8
 * Name: ZSORTDrawTerrain
 * Namespace: Global
 * Signature: void ZSORTDrawTerrain(CAMERA * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ZSORTDrawTerrain(CAMERA *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  CAMERA *unaff_EBX;
  int unaff_ESI;
  
  SortingTableIndexLift = SortingTableIndex + maxBucket;
  for (iVar2 = (maxBucket - minBucket) + 1; 0 < iVar2; iVar2 = iVar2 + -1) {
    if (0 < SortingTableIndexLift->EntrieAmount) {
      SortingTableLift = SortingTableIndexLift->Entrie;
      do {
        iVar1 = SortingTableLift->vcnt;
        if ((iVar1 != 0) && (SortingTableLift->Type == 0)) {
          if (useD3D == 0) {
            if (SortingTableLift->Bitmap_Operation == 0xed) {
              Set_Rounding(unaff_ESI);
              if (TerrainPixelDoubling == 0) {
                Terrain256Poly(unaff_EBX->Buffer,(POINT_3D *)(SortingTableLift + 1),
                               SortingTableLift->vcnt,SortingTableLift->Skin_Color);
              }
              else {
                Terrain256PolyDouble
                          (unaff_EBX->Buffer,(POINT_3D *)(SortingTableLift + 1),
                           SortingTableLift->vcnt,SortingTableLift->Skin_Color);
              }
              Set_Rounding(unaff_ESI);
            }
            else {
              __Camera_Software_Draw_polygon__
                        (unaff_EBX,(POINT_3D *)(SortingTableLift + 1),iVar1,
                         SortingTableLift->Skin_Color,SortingTableLift->Bitmap_Operation);
            }
          }
          else {
            Draw_D3D_Poly((POINT_3D *)(SortingTableLift + 1),iVar1,SortingTableLift->Skin_Color,
                          SortingTableLift->Bitmap_Operation);
          }
        }
        SortingTableLift = SortingTableLift->Next;
      } while (SortingTableLift != (_ZSORTING *)0x0);
      SortingTableLift = (_ZSORTING *)0x0;
    }
    SortingTableIndexLift = SortingTableIndexLift + -1;
  }
  return;
}
