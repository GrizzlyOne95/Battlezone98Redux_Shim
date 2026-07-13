/*
 * Entry: 0052490b
 * Name: ZSORTDraw
 * Namespace: Global
 * Signature: void ZSORTDraw(CAMERA * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ZSORTDraw(CAMERA *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int unaff_EBX;
  int unaff_ESI;
  CAMERA *unaff_EDI;
  POLYGON_SKIN PVar3;
  int iVar4;
  
  if (maxBucket < minBucket) {
    ZSORTReset();
    return;
  }
  if (TerrainSeparateDraw == 0) {
    SortingTableIndexLift = SortingTableIndex + maxBucket;
    for (iVar2 = (maxBucket - minBucket) + 1; 0 < iVar2; iVar2 = iVar2 + -1) {
      if (0 < SortingTableIndexLift->EntrieAmount) {
        SortingTableLift = SortingTableIndexLift->Entrie;
        do {
          iVar1 = SortingTableLift->vcnt;
          if (iVar1 == 0) {
            (*SortRender[SortingTableLift->Type])(SortingTableLift,param_1);
          }
          else if (SortingTableLift->Type == 0) {
            if (useD3D == 0) {
              iVar4 = SortingTableLift->Bitmap_Operation;
              if (iVar4 != 0xed) {
                PVar3 = SortingTableLift->Skin_Color;
                goto LAB_00524a00;
              }
              Set_Rounding(unaff_ESI);
              if (TerrainPixelDoubling == 0) {
                Terrain256Poly(param_1->Buffer,(POINT_3D *)(SortingTableLift + 1),
                               SortingTableLift->vcnt,SortingTableLift->Skin_Color);
              }
              else {
                Terrain256PolyDouble
                          (param_1->Buffer,(POINT_3D *)(SortingTableLift + 1),SortingTableLift->vcnt
                           ,SortingTableLift->Skin_Color);
              }
              Set_Rounding(unaff_ESI);
            }
            else {
              Draw_D3D_Poly((POINT_3D *)(SortingTableLift + 1),iVar1,SortingTableLift->Skin_Color,
                            SortingTableLift->Bitmap_Operation);
            }
          }
          else {
            iVar4 = SortingTableLift->Bitmap_Operation;
            PVar3 = SortingTableLift->Skin_Color;
            if (useD3D == 0) {
LAB_00524a00:
              __Camera_Software_Draw_polygon__
                        (param_1,(POINT_3D *)(SortingTableLift + 1),iVar1,PVar3,iVar4);
            }
            else {
              __Camera_Hardware_Draw_polygon__
                        (param_1,(POINT_3D *)(SortingTableLift + 1),iVar1,PVar3,iVar4);
            }
          }
          SortingTableLift = SortingTableLift->Next;
        } while (SortingTableLift != (_ZSORTING *)0x0);
        SortingTableLift = (_ZSORTING *)0x0;
      }
      SortingTableIndexLift = SortingTableIndexLift + -1;
    }
  }
  else {
    ZSORTDrawTerrain(unaff_EDI,unaff_EBX);
    ZSORTDrawModels(param_1,(int)unaff_EDI);
    ZSORTDrawSpecials(unaff_EDI,unaff_EBX);
  }
  ZSORTReset();
  return;
}
