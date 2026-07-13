/*
 * Entry: 004d01b9
 * Name: std::_Construct<AdjustItem_*,AdjustItem_*>
 * Namespace: std
 * Signature: void _Construct<AdjustItem_*,AdjustItem_*>(AdjustItem * * param_1, AdjustItem * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl std::_Construct<AdjustItem_*,AdjustItem_*>(AdjustItem **param_1,AdjustItem **param_2)

{
  if (param_1 != (AdjustItem **)0x0) {
    *param_1 = *param_2;
  }
  return;
}
