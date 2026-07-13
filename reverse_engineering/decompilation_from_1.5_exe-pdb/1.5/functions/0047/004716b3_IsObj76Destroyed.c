/*
 * Entry: 004716b3
 * Name: IsObj76Destroyed
 * Namespace: Global
 * Signature: int IsObj76Destroyed(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl IsObj76Destroyed(_OBJ76 *param_1)

{
  if ((param_1 != (_OBJ76 *)0x0) && ((param_1->flags & 0x200) != 0)) {
    return 1;
  }
  return 0;
}
