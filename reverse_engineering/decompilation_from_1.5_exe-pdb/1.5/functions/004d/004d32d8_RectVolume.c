/*
 * Entry: 004d32d8
 * Name: RectVolume
 * Namespace: Global
 * Signature: long RectVolume(tagRECT * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl RectVolume(tagRECT *param_1)

{
  long lVar1;
  
  lVar1 = (param_1->bottom - param_1->top) * (param_1->right - param_1->left);
  if (lVar1 < 0) {
    lVar1 = -lVar1;
  }
  return lVar1;
}
