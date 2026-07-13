/*
 * Entry: 00510d75
 * Name: IParse_Report
 * Namespace: Global
 * Signature: void IParse_Report(char * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl IParse_Report(char *param_1,int param_2)

{
  if ((param_2 != 0) && (param_2 != 1)) {
    if (param_2 == 2) {
      DEBUG_systemWarning("IParse FATAL ERROR: %s\n");
                    /* WARNING: Subroutine does not return */
      exit(0x6e);
    }
    printf("MESSAGE: %s\n",param_1);
  }
  return;
}
