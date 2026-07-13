/*
 * Entry: 0054d98f
 * Name: IsWithinRect
 * Namespace: Global
 * Signature: int IsWithinRect(tagRECT * param_1, long param_2, long param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl IsWithinRect(tagRECT *param_1,long param_2,long param_3)

{
  if ((((param_1->left <= param_2) && (param_2 <= param_1->right)) && (param_1->top <= param_3)) &&
     (param_3 <= param_1->bottom)) {
    return 1;
  }
  return 0;
}
