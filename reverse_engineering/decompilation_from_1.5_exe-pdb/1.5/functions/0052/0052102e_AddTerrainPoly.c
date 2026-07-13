/*
 * Entry: 0052102e
 * Name: AddTerrainPoly
 * Namespace: Global
 * Signature: void AddTerrainPoly(int param_1, int param_2, int param_3, float param_4, VECTOR_3D * param_5, VECTOR_3D * param_6, VECTOR_3D * param_7, VECTOR_3D * param_8, tagLIGHTING param_9, tagLIGHTING param_10, tagLIGHTING param_11, tagLIGHTING param_12, tagMIX2UV * param_13)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
AddTerrainPoly(int param_1,int param_2,int param_3,float param_4,VECTOR_3D *param_5,
              VECTOR_3D *param_6,VECTOR_3D *param_7,VECTOR_3D *param_8,tagLIGHTING param_9,
              tagLIGHTING param_10,tagLIGHTING param_11,tagLIGHTING param_12,tagMIX2UV *param_13)

{
  POLYGON_SKIN PVar1;
  float fVar2;
  _ZSORTING *p_Var3;
  float *in_EAX;
  TEXTURE *pTVar4;
  long lVar5;
  int unaff_EDI;
  
  p_Var3 = SortingTableCurrent;
  SortingTableCurrent->Z_Value = param_4;
  p_Var3->Type = 0;
  if (param_7 == (VECTOR_3D *)0x0) {
    p_Var3[2].Next = (_ZSORTING *)*in_EAX;
    p_Var3[2].Previous = (_ZSORTING *)in_EAX[1];
    p_Var3[3].vcnt = (long)in_EAX[2];
    p_Var3[1].Previous = (_ZSORTING *)param_5->x;
    p_Var3[2].vcnt = (long)param_5->y;
    p_Var3[2].Skin_Color = (POLYGON_SKIN)param_5->z;
    p_Var3[1].vcnt = (long)param_6->x;
    p_Var3[1].Skin_Color = (POLYGON_SKIN)param_6->y;
    p_Var3[1].Bitmap_Operation = (long)param_6->z;
    p_Var3[3].Type = (long)param_8;
    p_Var3[2].Z_Value = (float)param_9;
    p_Var3->vcnt = 3;
    param_11 = param_10;
  }
  else {
    p_Var3[3].Z_Value = *in_EAX;
    p_Var3[3].Next = (_ZSORTING *)in_EAX[1];
    p_Var3[3].Previous = (_ZSORTING *)in_EAX[2];
    p_Var3[2].Next = (_ZSORTING *)param_5->x;
    p_Var3[2].Previous = (_ZSORTING *)param_5->y;
    p_Var3[3].vcnt = (long)param_5->z;
    p_Var3[1].Previous = (_ZSORTING *)param_6->x;
    p_Var3[2].vcnt = (long)param_6->y;
    p_Var3[2].Skin_Color = (POLYGON_SKIN)param_6->z;
    p_Var3[1].vcnt = (long)param_7->x;
    p_Var3[1].Skin_Color = (POLYGON_SKIN)param_7->y;
    p_Var3[1].Bitmap_Operation = (long)param_7->z;
    p_Var3[4].Bitmap_Operation = (long)param_8;
    p_Var3[3].Type = (long)param_9;
    p_Var3[2].Z_Value = (float)param_10;
    p_Var3->vcnt = 4;
  }
  fVar2 = TerrainView.Flat_Range;
  p_Var3[1].Next = (_ZSORTING *)param_11;
  if ((fVar2 < param_4) || (solidPoly != 0)) {
    if (flatROP != 0x109) {
      AverageLuma((POINT_3D *)p_Var3->vcnt,unaff_EDI);
    }
    lVar5 = (*ClipSolidTile)(Terrain.Camera,(POINT_3D *)(p_Var3 + 1),(POINT_3D *)(p_Var3 + 1),
                             p_Var3->vcnt,0xf6);
    p_Var3->vcnt = lVar5;
    if (lVar5 == 0) {
      return;
    }
    p_Var3->Bitmap_Operation = flatROP;
    p_Var3->Skin_Color = *(POLYGON_SKIN *)(MaterialColors + pre_minM);
  }
  else {
    p_Var3->Bitmap_Operation = 0xed;
    pTVar4 = GetTexelInfo(param_1,param_2);
    (p_Var3->Skin_Color).Texture = pTVar4;
    PVar1 = *(POLYGON_SKIN *)param_12;
    if (param_3 == 1) {
      p_Var3[3].Skin_Color = PVar1;
      p_Var3[3].Bitmap_Operation = *(long *)((int)param_12 + 4);
      p_Var3[2].Bitmap_Operation = *(long *)((int)param_12 + 8);
      p_Var3[2].Type = *(long *)((int)param_12 + 0xc);
      p_Var3[1].Type = *(long *)((int)param_12 + 0x10);
      fVar2 = *(float *)((int)param_12 + 0x14);
    }
    else {
      if (param_3 == 2) {
        p_Var3[3].Skin_Color = PVar1;
        lVar5 = *(long *)((int)param_12 + 4);
      }
      else {
        *(POLYGON_SKIN *)(p_Var3 + 4) = PVar1;
        p_Var3[4].Skin_Color = *(POLYGON_SKIN *)((int)param_12 + 4);
        p_Var3[3].Skin_Color = *(POLYGON_SKIN *)((int)param_12 + 8);
        lVar5 = *(long *)((int)param_12 + 0xc);
      }
      p_Var3[3].Bitmap_Operation = lVar5;
      p_Var3[2].Bitmap_Operation = *(long *)((int)param_12 + 0x10);
      p_Var3[2].Type = *(long *)((int)param_12 + 0x14);
      p_Var3[1].Type = *(long *)((int)param_12 + 0x18);
      fVar2 = *(float *)((int)param_12 + 0x1c);
    }
    p_Var3[1].Z_Value = fVar2;
    lVar5 = (*ClipTexturedTile)(Terrain.Camera,(POINT_3D *)(p_Var3 + 1),(POINT_3D *)(p_Var3 + 1),
                                p_Var3->vcnt,0xf6);
    p_Var3->vcnt = lVar5;
    if (((byte)D3IniFlags & 1) != 0) {
      p_Var3->Z_Value = (float)pre_idx;
    }
    if (lVar5 == 0) {
      return;
    }
  }
  ZSORTAdd(p_Var3->Z_Value);
  Terrain_Polygon_Counter = Terrain_Polygon_Counter + 1;
  return;
}
