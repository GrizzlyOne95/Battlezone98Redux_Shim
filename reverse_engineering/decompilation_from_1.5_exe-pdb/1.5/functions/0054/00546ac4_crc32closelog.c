/*
 * Entry: 00546ac4
 * Name: crc32closelog
 * Namespace: Global
 * Signature: void crc32closelog(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl crc32closelog(void)

{
  if (crc32log != (_iobuf *)0x0) {
    fclose((FILE *)crc32log);
    crc32log = (_iobuf *)0x0;
  }
  return;
}
