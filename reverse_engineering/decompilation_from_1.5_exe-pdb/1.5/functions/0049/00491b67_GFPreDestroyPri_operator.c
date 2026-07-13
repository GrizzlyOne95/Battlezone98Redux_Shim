/*
 * Entry: 00491b67
 * Name: GFPreDestroyPri::operator()
 * Namespace: GFPreDestroyPri
 * Signature: bool operator()(GFPreDestroyPri * this, GameFeature * param_1, GameFeature * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
GFPreDestroyPri::operator()(GFPreDestroyPri *this,GameFeature *param_1,GameFeature *param_2)

{
  return param_2->preDestroyPriority < param_1->preDestroyPriority;
}
