/*
 * Entry: 00524353
 * Name: Render_Sprite_3D_Entity
 * Namespace: Global
 * Signature: void Render_Sprite_3D_Entity(_ZSORTING * param_1, CAMERA * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Render_Sprite_3D_Entity(_ZSORTING *param_1,CAMERA *param_2)

{
  DrawPolySprite(param_2,(param_1->Skin_Color).Color,(VECTOR_3D *)(param_1 + 1),
                 param_1->Bitmap_Operation);
  return;
}
