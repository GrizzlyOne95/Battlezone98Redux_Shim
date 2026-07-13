/*
 * Entry: 0056ea55
 * Name: check_roll_over
 * Namespace: Global
 * Signature: int check_roll_over(tagRECT * param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl check_roll_over(tagRECT *param_1,int param_2,int param_3)

{
  if ((((param_1->left < param_2) && (param_2 < param_1->right)) && (param_1->top < param_3)) &&
     (param_3 < param_1->bottom)) {
    return 1;
  }
  return 0;
}
