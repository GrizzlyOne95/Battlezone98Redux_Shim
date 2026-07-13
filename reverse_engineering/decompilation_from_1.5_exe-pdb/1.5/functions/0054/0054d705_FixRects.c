/*
 * Entry: 0054d705
 * Name: FixRects
 * Namespace: Global
 * Signature: void FixRects(tagRECT * param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl FixRects(tagRECT *param_1,long param_2)

{
  if (0 < param_2) {
    do {
      param_1->right = param_1->right + param_1->left;
      param_1->bottom = param_1->bottom + param_1->top;
      param_1 = param_1 + 1;
      param_2 = param_2 + -1;
    } while (param_2 != 0);
  }
  return;
}
