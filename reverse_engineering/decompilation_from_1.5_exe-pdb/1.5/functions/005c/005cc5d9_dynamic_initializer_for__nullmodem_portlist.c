/*
 * Entry: 005cc5d9
 * Name: `dynamic_initializer_for_'nullmodem_portlist''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'nullmodem_portlist''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__nullmodem_portlist__(void)

{
  std::vector<PortData_*,std::allocator<PortData_*>_>::
  vector<PortData_*,std::allocator<PortData_*>_>(&nullmodem_portlist);
  atexit(_dynamic_atexit_destructor_for__nullmodem_portlist__);
  return;
}
