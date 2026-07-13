/*
 * Entry: 004b23e5
 * Name: dump_tcache_contents
 * Namespace: Global
 * Signature: void dump_tcache_contents(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl dump_tcache_contents(void)

{
  _texcache **pp_Var1;
  _texcache *p_Var2;
  
  DEBUG_setOutputMethod(4);
  DEBUG_setLogFileName("texcache.txt");
  DEBUG_openLogFile();
  DEBUG_printf("Contents of texture cache:\n\n");
  pp_Var1 = texcache;
  do {
    for (p_Var2 = *pp_Var1; p_Var2 != (_texcache *)0x0; p_Var2 = p_Var2->next) {
      DEBUG_printf("Name: %30s Addr: %x Size: %7d\n");
    }
    pp_Var1 = pp_Var1 + 1;
  } while ((int)pp_Var1 < 0xb0d04c);
  DEBUG_printf("\nTotal allocated: %d\n");
  return;
}
