/*
 * Entry: 00491b97
 * Name: GFRenderPri::operator()
 * Namespace: GFRenderPri
 * Signature: bool operator()(GFRenderPri * this, GameFeature * param_1, GameFeature * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall GFRenderPri::operator()(GFRenderPri *this,GameFeature *param_1,GameFeature *param_2)

{
  return param_2->renderPriority < param_1->renderPriority;
}
