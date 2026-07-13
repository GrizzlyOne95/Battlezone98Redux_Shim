/*
 * Entry: 005cd27e
 * Name: `dynamic_atexit_destructor_for_'nullmodem_portlist''
 * Namespace: Global
 * Signature: void `dynamic_atexit_destructor_for_'nullmodem_portlist''(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _dynamic_atexit_destructor_for__nullmodem_portlist__(void)

{
  std::vector<PortData_*,std::allocator<PortData_*>_>::_Tidy(&nullmodem_portlist);
  operator_delete((void *)nullmodem_portlist._padding_);
  return;
}
