/*
 * Entry: 00483d83
 * Name: dump_cache_contents
 * Namespace: Global
 * Signature: void dump_cache_contents(MULTICACHE * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl dump_cache_contents(MULTICACHE *param_1)

{
  int iVar1;
  int iVar2;
  int *unaff_EDI;
  
  DEBUG_setOutputMethod(4);
  DEBUG_setLogFileName("prjcache.txt");
  DEBUG_openLogFile();
  DEBUG_printf("Size: %d Items: %d\n\n");
  DEBUG_printf("Contents of project file cache:\n\n");
  iVar1 = 0;
  do {
    for (iVar2 = *(int *)(iVar1 + *unaff_EDI); iVar2 != 0; iVar2 = *(int *)(iVar2 + 0x1c)) {
      DEBUG_printf("Name: %30s Size: %7d\n");
    }
    iVar1 = iVar1 + 4;
  } while (iVar1 < 0x2000);
  DEBUG_printf("\nTotal allocated: %d\n");
  return;
}
