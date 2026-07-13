/*
 * Entry: 005cc5c3
 * Name: `dynamic_initializer_for_'modem_portlist''
 * Namespace: Global
 * Signature: void `dynamic_initializer_for_'modem_portlist''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_initializer_for__modem_portlist__(void)

{
  std::vector<PortData_*,std::allocator<PortData_*>_>::
  vector<PortData_*,std::allocator<PortData_*>_>(&modem_portlist);
  atexit(_dynamic_atexit_destructor_for__modem_portlist__);
  return;
}
