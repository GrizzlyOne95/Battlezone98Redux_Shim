/*
 * Entry: 00491b4f
 * Name: GFPostLoadPri::operator()
 * Namespace: GFPostLoadPri
 * Signature: bool operator()(GFPostLoadPri * this, GameFeature * param_1, GameFeature * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
GFPostLoadPri::operator()(GFPostLoadPri *this,GameFeature *param_1,GameFeature *param_2)

{
  return param_2->postLoadPriority < param_1->postLoadPriority;
}
