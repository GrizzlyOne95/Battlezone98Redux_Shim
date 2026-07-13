/*
 * Entry: 004b2f32
 * Name: FindHitch
 * Namespace: Global
 * Signature: void FindHitch(_OBJ76 * param_1, _OBJ76 * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl FindHitch(_OBJ76 *param_1,_OBJ76 **param_2)

{
  if (param_1 != (_OBJ76 *)0x0) {
    while (param_1->class_id != CLASS_ID_SPECIAL_HARDPOINT) {
      if ((param_1->child != (_OBJ76 *)0x0) &&
         (FindHitch(param_1->child,param_2), *param_2 != (_OBJ76 *)0x0)) {
        return;
      }
      param_1 = param_1->sibling;
      if (param_1 == (_OBJ76 *)0x0) {
        return;
      }
    }
    *param_2 = param_1;
  }
  return;
}
