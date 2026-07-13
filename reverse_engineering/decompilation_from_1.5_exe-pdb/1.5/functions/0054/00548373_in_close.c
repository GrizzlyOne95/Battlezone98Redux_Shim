/*
 * Entry: 00548373
 * Name: in_close
 * Namespace: Global
 * Signature: _iobuf * in_close(_iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_iobuf * __cdecl in_close(_iobuf *param_1)

{
  inBuffer = (char *)0x0;
  inCurrent = (char *)0x0;
  inLast = (char *)0x0;
  inIsOpen = false;
  return inFile;
}
