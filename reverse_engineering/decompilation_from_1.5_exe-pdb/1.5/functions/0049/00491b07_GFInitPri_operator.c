/*
 * Entry: 00491b07
 * Name: GFInitPri::operator()
 * Namespace: GFInitPri
 * Signature: bool operator()(GFInitPri * this, GameFeature * param_1, GameFeature * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall GFInitPri::operator()(GFInitPri *this,GameFeature *param_1,GameFeature *param_2)

{
  return param_2->initPriority < param_1->initPriority;
}
