/*
 * Entry: 005240c7
 * Name: Render_Compound_Entity
 * Namespace: Global
 * Signature: void Render_Compound_Entity(_ZSORTING * param_1, CAMERA * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Render_Compound_Entity(_ZSORTING *param_1,CAMERA *param_2)

{
  SORTING_LIST_ENTITY *pSVar1;
  
  pSVar1 = (SORTING_LIST_ENTITY *)(param_1 + 1);
  if ((*(int *)(param_1[2].Bitmap_Operation + 0x9c) == 0) &&
     (*(int *)(param_1[2].Bitmap_Operation + 0xa8) == 0)) {
    if (param_1[2].Skin_Color.Color == 0) {
      Render_CachedBSP_Entity(pSVar1,param_2);
    }
    else {
      Render_CachedBSP_Object(pSVar1,param_2);
    }
  }
  else if (param_1[2].Skin_Color.Color == 0) {
    Render_BuildNewBSP_Entity(pSVar1,param_2);
  }
  else {
    Render_BuildNewBSP_Object(pSVar1,param_2);
  }
  return;
}
