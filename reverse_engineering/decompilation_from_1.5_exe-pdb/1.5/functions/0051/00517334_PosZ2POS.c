/*
 * Entry: 00517334
 * Name: PosZ2POS
 * Namespace: Global
 * Signature: int PosZ2POS(double param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl PosZ2POS(double param_1)

{
  param_1._0_4_ = SUB84(param_1 * 0.1 + Float2Int,0);
  if (param_1._0_4_ < aiGridZ0) {
    return 0;
  }
  if (aiGridZ1 <= param_1._0_4_) {
    return (aiGridZ1 - aiGridZ0) + -1;
  }
  return param_1._0_4_ - aiGridZ0;
}
