/*
 * Entry: 0055575e
 * Name: std::_Fill<PortData_*_*,PortData_*>
 * Namespace: std
 * Signature: void _Fill<PortData_*_*,PortData_*>(PortData * * param_1, PortData * * param_2, PortData * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::_Fill<PortData_*_*,PortData_*>(PortData **param_1,PortData **param_2,PortData **param_3)

{
  for (; param_1 != param_2; param_1 = param_1 + 1) {
    *param_1 = *param_3;
  }
  return;
}
