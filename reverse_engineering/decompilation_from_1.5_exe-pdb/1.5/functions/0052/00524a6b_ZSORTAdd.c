/*
 * Entry: 00524a6b
 * Name: ZSORTAdd
 * Namespace: Global
 * Signature: void ZSORTAdd(float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ZSORTAdd(float param_1)

{
  int iVar1;
  tagENTITY *ptVar2;
  _ZSORTING *p_Var3;
  int iVar4;
  long lVar5;
  int local_14;
  
  iVar1 = SortingTableCurrent->vcnt;
  lVar5 = iVar1 * 0x18;
  if (SortingTableEnd < SortingTableCurrent) {
    return;
  }
  if ((SortingTableCurrent->Type == 9) && ((float)SortingTableCurrent[1].Type < 1.5)) {
    return;
  }
  if (0x20 < iVar1) {
    return;
  }
  local_14 = SUB84((double)(param_1 + 300.0 + (float)Float2Int),0);
  if (local_14 < 0) {
    local_14 = 0;
  }
  if (0xfff < local_14) {
    local_14 = 0xfff;
  }
  if (local_14 < minBucket) {
    minBucket = local_14;
  }
  if (maxBucket < local_14) {
    maxBucket = local_14;
  }
  if (((iVar1 != 0) && ((SortingTableCurrent->Bitmap_Operation & 4) != 0)) &&
     ((SortingTableCurrent->Skin_Color).Color == 0)) {
    SortingTableCurrent->Bitmap_Operation = 0;
  }
  if ((SortingTableCurrent->Type == 9) && (((byte)LODInfo.mergeBSP & 2) != 0)) {
    iVar4 = 0;
    if (0 < Visible_Entity_Count) {
      do {
        ptVar2 = Visible_Entity_Cluster[iVar4];
        if ((((float)SortingTableCurrent[1].Previous - (float)SortingTableCurrent[1].Next <
              (ptVar2->max).x) &&
            ((ptVar2->min).x <
             (float)SortingTableCurrent[1].Next + (float)SortingTableCurrent[1].Previous)) &&
           (((float)SortingTableCurrent[2].vcnt - (float)SortingTableCurrent[1].Next <
             (ptVar2->max).y &&
            ((((ptVar2->min).y <
               (float)SortingTableCurrent[1].Next + (float)SortingTableCurrent[2].vcnt &&
              ((float)SortingTableCurrent[2].Skin_Color < (ptVar2->max).z)) &&
             ((ptVar2->min).z < (float)SortingTableCurrent[2].Skin_Color)))))) goto LAB_00524c60;
        iVar4 = iVar4 + 1;
      } while (iVar4 < Visible_Entity_Count);
    }
  }
  SortingTableIndexLift = SortingTableIndex + local_14;
  InsideNode = SortingTableIndexLift->Entrie;
  if (InsideNode == (_ZSORTING *)0x0) {
    SortingTableIndexLift->LastEntrie = SortingTableCurrent;
    SortingTableIndexLift->Entrie = SortingTableCurrent;
    SortingTableIndexLift->EntrieAmount = 1;
    SortingTableCurrent->Previous = (_ZSORTING *)0x0;
LAB_00524ba2:
    SortingTableCurrent->Next = (_ZSORTING *)0x0;
  }
  else {
    if (((byte)D3IniFlags & 1) != 0) {
LAB_00524d16:
      SortingTableIndexLift->LastEntrie->Next = SortingTableCurrent;
      SortingTableIndexLift->LastEntrie = SortingTableCurrent;
      SortingTableIndexLift->EntrieAmount = SortingTableIndexLift->EntrieAmount + 1;
      goto LAB_00524ba2;
    }
    if (((param_1 <= InsideNode->Z_Value) || (InsideNode->Type < 4)) || (10 < InsideNode->Type)) {
      do {
        p_Var3 = InsideNode;
        InsideNode = p_Var3->Next;
        if (InsideNode == (_ZSORTING *)0x0) goto LAB_00524d16;
      } while (((param_1 <= InsideNode->Z_Value) || (InsideNode->Type < 4)) ||
              (10 < InsideNode->Type));
      p_Var3->Next = SortingTableCurrent;
      SortingTableCurrent->Previous = p_Var3;
      SortingTableCurrent->Next = InsideNode;
      InsideNode->Previous = SortingTableCurrent;
      SortingTableIndexLift->EntrieAmount = SortingTableIndexLift->EntrieAmount + 1;
      goto LAB_00524c80;
    }
    SortingTableCurrent->Next = InsideNode;
    InsideNode->Previous = SortingTableCurrent;
    SortingTableCurrent->Previous = (_ZSORTING *)0x0;
    SortingTableIndexLift->Entrie = SortingTableCurrent;
    SortingTableIndexLift->EntrieAmount = SortingTableIndexLift->EntrieAmount + 1;
  }
  if (iVar1 != 0) {
    SortingTableCurrent = (_ZSORTING *)(&SortingTableCurrent[1].vcnt + iVar1 * 6);
    return;
  }
LAB_00524d6d:
  lVar5 = SizeRender[SortingTableCurrent->Type];
LAB_00524d77:
  SortingTableCurrent = (_ZSORTING *)((int)&SortingTableCurrent[1].vcnt + lVar5);
  return;
LAB_00524c60:
  for (; ptVar2->mergeNext != (tagENTITY *)0x0; ptVar2 = ptVar2->mergeNext) {
  }
  SortingTableCurrent->Next = ptVar2->mergePoly;
  ptVar2->mergePoly = SortingTableCurrent;
LAB_00524c80:
  if (iVar1 != 0) goto LAB_00524d77;
  goto LAB_00524d6d;
}
