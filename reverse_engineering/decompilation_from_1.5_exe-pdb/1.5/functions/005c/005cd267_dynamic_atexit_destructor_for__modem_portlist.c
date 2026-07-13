/*
 * Entry: 005cd267
 * Name: `dynamic_atexit_destructor_for_'modem_portlist''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'modem_portlist''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__modem_portlist__(void)

{
  std::vector<PortData_*,std::allocator<PortData_*>_>::_Tidy(&modem_portlist);
  operator_delete((void *)modem_portlist._padding_);
  return;
}
