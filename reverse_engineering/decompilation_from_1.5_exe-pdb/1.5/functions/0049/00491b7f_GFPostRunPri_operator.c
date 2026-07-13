/*
 * Entry: 00491b7f
 * Name: GFPostRunPri::operator()
 * Namespace: GFPostRunPri
 * Signature: bool operator()(GFPostRunPri * this, GameFeature * param_1, GameFeature * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall
GFPostRunPri::operator()(GFPostRunPri *this,GameFeature *param_1,GameFeature *param_2)

{
  return param_2->postRunPriority < param_1->postRunPriority;
}
