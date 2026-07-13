/*
 * Entry: 00524115
 * Name: Render_Single_Entity
 * Namespace: Global
 * Signature: void Render_Single_Entity(_ZSORTING * param_1, CAMERA * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Render_Single_Entity(_ZSORTING *param_1,CAMERA *param_2)

{
  SORTING_LIST_ENTITY *pSVar1;
  
  pSVar1 = (SORTING_LIST_ENTITY *)(param_1 + 1);
  if (param_1[2].Skin_Color.Color == 0) {
    if (param_1[2].Bitmap_Operation == 0) {
      Render_Chunk_Object(pSVar1,param_2);
    }
    else {
      Render_CachedBSP_Entity(pSVar1,param_2);
    }
  }
  else {
    Render_CachedBSP_Object(pSVar1,param_2);
  }
  return;
}
