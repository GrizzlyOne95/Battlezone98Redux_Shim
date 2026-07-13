/*
 * Entry: 005c71ba
 * Name: NtCurrentTeb
 * Namespace: Global
 * Signature: _TEB * NtCurrentTeb(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_TEB * __cdecl NtCurrentTeb(void)

{
  return (_TEB *)&ExceptionList;
}
