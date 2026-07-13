/*
 * Entry: 005172fa
 * Name: PosX2POS
 * Namespace: Global
 * Signature: int PosX2POS(double param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl PosX2POS(double param_1)

{
  param_1._0_4_ = SUB84(param_1 * 0.1 + Float2Int,0);
  if (param_1._0_4_ < aiGridX0) {
    return 0;
  }
  if (aiGridX1 <= param_1._0_4_) {
    return (aiGridX1 - aiGridX0) + -1;
  }
  return param_1._0_4_ - aiGridX0;
}
