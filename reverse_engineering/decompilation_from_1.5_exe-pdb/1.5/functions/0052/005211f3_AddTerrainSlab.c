/*
 * Entry: 005211f3
 * Name: AddTerrainSlab
 * Namespace: Global
 * Signature: void AddTerrainSlab(int param_1, int param_2, int param_3, float param_4, VECTOR_3D * param_5, VECTOR_3D * param_6, VECTOR_3D * param_7, VECTOR_3D * param_8, VECTOR_3D * param_9, VECTOR_3D * param_10, tagLIGHTING param_11, tagLIGHTING param_12, tagLIGHTING param_13, tagLIGHTING param_14, tagLIGHTING param_15, tagLIGHTING param_16, tagMIX2UV * param_17)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
AddTerrainSlab(int param_1,int param_2,int param_3,float param_4,VECTOR_3D *param_5,
              VECTOR_3D *param_6,VECTOR_3D *param_7,VECTOR_3D *param_8,VECTOR_3D *param_9,
              VECTOR_3D *param_10,tagLIGHTING param_11,tagLIGHTING param_12,tagLIGHTING param_13,
              tagLIGHTING param_14,tagLIGHTING param_15,tagLIGHTING param_16,tagMIX2UV *param_17)

{
  bool bVar1;
  _ZSORTING *p_Var2;
  long *in_EAX;
  TEXTURE *pTVar3;
  long lVar4;
  int unaff_EDI;
  
  p_Var2 = SortingTableCurrent;
  SortingTableCurrent->Type = 0;
  p_Var2->Z_Value = (float)param_3;
  bVar1 = TerrainView.Flat_Range < (float)param_3;
  p_Var2[1].vcnt = *in_EAX;
  p_Var2[1].Skin_Color = *(POLYGON_SKIN *)(in_EAX + 1);
  p_Var2[1].Bitmap_Operation = in_EAX[2];
  p_Var2[1].Previous = *(_ZSORTING **)param_4;
  p_Var2[2].vcnt = *(long *)((int)param_4 + 4);
  p_Var2[2].Skin_Color = *(POLYGON_SKIN *)((int)param_4 + 8);
  p_Var2[2].Next = (_ZSORTING *)param_6->x;
  p_Var2[2].Previous = (_ZSORTING *)param_6->y;
  p_Var2[3].vcnt = (long)param_6->z;
  p_Var2[3].Z_Value = param_5->x;
  p_Var2[3].Next = (_ZSORTING *)param_5->y;
  p_Var2[3].Previous = (_ZSORTING *)param_5->z;
  p_Var2[4].Type = (long)param_8->x;
  p_Var2[4].Z_Value = param_8->y;
  p_Var2[4].Next = (_ZSORTING *)param_8->z;
  p_Var2[5].Bitmap_Operation = (long)param_7->x;
  p_Var2[5].Type = (long)param_7->y;
  p_Var2[5].Z_Value = param_7->z;
  p_Var2[2].Z_Value = (float)param_9;
  p_Var2[1].Next = (_ZSORTING *)param_10;
  *(tagLIGHTING *)(p_Var2 + 6) = param_13;
  p_Var2[5].Skin_Color = (POLYGON_SKIN)param_14;
  p_Var2[4].Bitmap_Operation = (long)param_11;
  p_Var2[3].Type = (long)param_12;
  p_Var2->vcnt = 6;
  if ((bVar1) || (solidPoly != 0)) {
    if (flatROP != 0x109) {
      AverageLuma((POINT_3D *)0x6,unaff_EDI);
    }
    lVar4 = (*ClipSolidTile)(Terrain.Camera,(POINT_3D *)(p_Var2 + 1),(POINT_3D *)(p_Var2 + 1),
                             p_Var2->vcnt,0xf6);
    p_Var2->vcnt = lVar4;
    if (lVar4 != 0) {
      p_Var2->Bitmap_Operation = flatROP;
      p_Var2->Skin_Color = *(POLYGON_SKIN *)(MaterialColors + pre_minM);
      Terrain_Polygon_Counter = Terrain_Polygon_Counter + 1;
      ZSORTAdd(p_Var2->Z_Value);
    }
  }
  else {
    p_Var2->Bitmap_Operation = 0xed;
    pTVar3 = GetTexelInfo(param_1,param_2);
    (p_Var2->Skin_Color).Texture = pTVar3;
    p_Var2[2].Bitmap_Operation = *(long *)param_15;
    p_Var2[2].Type = *(long *)((int)param_15 + 4);
    p_Var2[1].Type = *(long *)((int)param_15 + 8);
    p_Var2[1].Z_Value = *(float *)((int)param_15 + 0xc);
    p_Var2[5].Next = *(_ZSORTING **)((int)param_15 + 0x28);
    p_Var2[5].Previous = *(_ZSORTING **)((int)param_15 + 0x2c);
    p_Var2[4].Previous = *(_ZSORTING **)((int)param_15 + 0x30);
    p_Var2[5].vcnt = *(long *)((int)param_15 + 0x34);
    p_Var2[4].vcnt = *(long *)((int)param_15 + 0x10);
    p_Var2[4].Skin_Color = *(POLYGON_SKIN *)((int)param_15 + 0x14);
    p_Var2[3].Skin_Color = *(POLYGON_SKIN *)((int)param_15 + 0x18);
    p_Var2[3].Bitmap_Operation = *(long *)((int)param_15 + 0x1c);
    if (((byte)D3IniFlags & 1) != 0) {
      p_Var2->Z_Value = (float)pre_idx;
    }
    lVar4 = (*ClipTexturedTile)(Terrain.Camera,(POINT_3D *)(p_Var2 + 1),(POINT_3D *)(p_Var2 + 1),6,
                                0xf6);
    p_Var2->vcnt = lVar4;
    if (lVar4 != 0) {
      ZSORTAdd(p_Var2->Z_Value);
      Terrain_Polygon_Counter = Terrain_Polygon_Counter + 1;
    }
  }
  return;
}
