/*
 * Entry: 00529acf
 * Name: zixReleaseFileHandle
 * Namespace: Global
 * Signature: void zixReleaseFileHandle(_iobuf * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl zixReleaseFileHandle(_iobuf *param_1,int param_2)

{
  if (param_2 != 0) {
    fclose((FILE *)param_1);
  }
  return;
}
