/*
 * Entry: 005c78fc
 * Name: __sse2_available_init
 * Namespace: Global
 * Signature: int __sse2_available_init(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl __sse2_available_init(void)

{
  __sse2_available = _get_sse2_info();
  return 0;
}
