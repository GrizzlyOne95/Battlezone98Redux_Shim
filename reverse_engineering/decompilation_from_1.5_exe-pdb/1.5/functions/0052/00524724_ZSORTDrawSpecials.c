/*
 * Entry: 00524724
 * Name: ZSORTDrawSpecials
 * Namespace: Global
 * Signature: void ZSORTDrawSpecials(CAMERA * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ZSORTDrawSpecials(CAMERA *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  CAMERA *unaff_EDI;
  
  SortingTableIndexLift = SortingTableIndex + maxBucket;
  for (iVar2 = (maxBucket - minBucket) + 1; 0 < iVar2; iVar2 = iVar2 + -1) {
    if (0 < SortingTableIndexLift->EntrieAmount) {
      SortingTableLift = SortingTableIndexLift->Entrie;
      do {
        iVar1 = SortingTableLift->vcnt;
        if (iVar1 == 0) {
          if (SortingTableLift->Type != 6) {
            (*SortRender[SortingTableLift->Type])(SortingTableLift,unaff_EDI);
          }
        }
        else if (SortingTableLift->Type != 0) {
          if (useD3D == 0) {
            __Camera_Software_Draw_polygon__
                      (unaff_EDI,(POINT_3D *)(SortingTableLift + 1),iVar1,
                       SortingTableLift->Skin_Color,SortingTableLift->Bitmap_Operation);
          }
          else {
            __Camera_Hardware_Draw_polygon__
                      (unaff_EDI,(POINT_3D *)(SortingTableLift + 1),iVar1,
                       SortingTableLift->Skin_Color,SortingTableLift->Bitmap_Operation);
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
