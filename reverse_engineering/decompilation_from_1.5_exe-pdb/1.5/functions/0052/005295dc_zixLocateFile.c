/*
 * Entry: 005295dc
 * Name: zixLocateFile
 * Namespace: Global
 * Signature: char * zixLocateFile(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl zixLocateFile(char *param_1)

{
  char *pcVar1;
  ZIX_PATH_TYPE *unaff_ESI;
  char *unaff_retaddr;
  
  locate_file(unaff_ESI->name);
  pcVar1 = resolve_path(unaff_ESI,unaff_retaddr);
  return pcVar1;
}
