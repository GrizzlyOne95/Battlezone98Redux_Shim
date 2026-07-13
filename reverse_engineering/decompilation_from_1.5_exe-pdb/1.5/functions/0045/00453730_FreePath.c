/*
 * Entry: 00453730
 * Name: FreePath
 * Namespace: Global
 * Signature: void FreePath(PathPlan * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl FreePath(PathPlan *param_1)

{
  if (param_1 != (PathPlan *)0x0) {
    if ((param_1->flags & 4) != 0) {
      param_1->flags = param_1->flags & 0xfffffffb;
      Search::Clean();
    }
    (**(code **)param_1->_padding_)(1);
  }
  return;
}
