/*
 * Entry: 00537d90
 * Name: SubmitMissileLight
 * Namespace: Global
 * Signature: int SubmitMissileLight(CAMERA * param_1, VECTOR_3D * param_2, float param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl SubmitMissileLight(CAMERA *param_1,VECTOR_3D *param_2,float param_3)

{
  float fVar1;
  int iVar2;
  _ZSORTING *p_Var3;
  
  if (LightIndex == 0) {
    LightIndex = GetSpriteIndex("lsmoke.12");
  }
  p_Var3 = SortingTableCurrent;
  iVar2 = LightIndex;
  SortingTableCurrent->vcnt = 0;
  (p_Var3->Skin_Color).Color = iVar2;
  p_Var3->Type = 1;
  p_Var3->Bitmap_Operation = 4;
  p_Var3[1].Skin_Color = (POLYGON_SKIN)param_1->Orig_x;
  p_Var3[1].Bitmap_Operation = (long)param_1->Orig_y;
  p_Var3[1].Type = (long)param_1->Const_x;
  p_Var3[1].vcnt = (long)param_2;
  fVar1 = param_1->Const_x;
  p_Var3->Z_Value = fVar1;
  ZSORTAdd(fVar1);
  return 1;
}
