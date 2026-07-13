/*
 * Entry: 005149c1
 * Name: Mutils_FatalError
 * Namespace: Global
 * Signature: void Mutils_FatalError(char * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Mutils_FatalError(char *param_1,int param_2)

{
  puts(param_1);
  printf("Error number  %d",param_2);
                    /* WARNING: Subroutine does not return */
  exit(0x6f);
}
