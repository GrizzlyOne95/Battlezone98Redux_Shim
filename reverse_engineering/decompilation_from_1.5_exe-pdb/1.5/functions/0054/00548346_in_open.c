/*
 * Entry: 00548346
 * Name: in_open
 * Namespace: Global
 * Signature: _iobuf * in_open(_iobuf * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_iobuf * __cdecl in_open(_iobuf *param_1,int param_2)

{
  inSize = param_2;
  inBuffer = (char *)param_1;
  inLast = (char *)((int)&param_1->_ptr + param_2);
  inCurrent = (char *)param_1;
  inIsOpen = true;
  inFile = param_1;
  return param_1;
}
