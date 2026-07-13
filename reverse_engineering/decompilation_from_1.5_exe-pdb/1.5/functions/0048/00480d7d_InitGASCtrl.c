/*
 * Entry: 00480d7d
 * Name: InitGASCtrl
 * Namespace: Global
 * Signature: void InitGASCtrl(GAS_CTRL * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl InitGASCtrl(GAS_CTRL *param_1)

{
  memset(param_1,0,0x2c);
  param_1->rate = 11025.0;
  param_1->volume = 100.0;
  param_1->pan = 0.0;
  return;
}
