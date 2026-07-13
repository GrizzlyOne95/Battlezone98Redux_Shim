/*
 * Entry: 00491b37
 * Name: GFPreLoadPri::operator()
 * Namespace: GFPreLoadPri
 * Signature: bool operator()(GFPreLoadPri * this, GameFeature * param_1, GameFeature * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
GFPreLoadPri::operator()(GFPreLoadPri *this,GameFeature *param_1,GameFeature *param_2)

{
  return param_2->preLoadPriority < param_1->preLoadPriority;
}
