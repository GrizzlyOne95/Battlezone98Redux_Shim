/*
 * Entry: 0054d35e
 * Name: Mono_IsActive
 * Namespace: Global
 * Signature: int Mono_IsActive(long param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Mono_IsActive(long param_1)

{
  if ((param_1 != 0) && (param_1 == active_screen)) {
    return 1;
  }
  return 0;
}
