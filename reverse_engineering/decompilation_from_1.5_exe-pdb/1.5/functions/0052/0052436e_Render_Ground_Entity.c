/*
 * Entry: 0052436e
 * Name: Render_Ground_Entity
 * Namespace: Global
 * Signature: void Render_Ground_Entity(_ZSORTING * param_1, CAMERA * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Render_Ground_Entity(_ZSORTING *param_1,CAMERA *param_2)

{
  DrawGroundSprite(param_2,(VECTOR_3D *)&param_1[1].Skin_Color,(float)param_1[1].vcnt,
                   (param_1->Skin_Color).Color,param_1->Bitmap_Operation);
  return;
}
