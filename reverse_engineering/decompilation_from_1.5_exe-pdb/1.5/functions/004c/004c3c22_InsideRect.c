/*
 * Entry: 004c3c22
 * Name: InsideRect
 * Namespace: Global
 * Signature: int InsideRect(tagPOINT param_1, tagRECT * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl InsideRect(tagPOINT param_1,tagRECT *param_2)

{
  if ((((param_2->left <= param_1.x) && (param_1.x <= param_2->right)) &&
      (param_2->top <= param_1.y)) && (param_1.y <= param_2->bottom)) {
    return 1;
  }
  return 0;
}
