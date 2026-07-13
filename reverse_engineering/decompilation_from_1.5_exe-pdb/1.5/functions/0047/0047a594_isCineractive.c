/*
 * Entry: 0047a594
 * Name: isCineractive
 * Namespace: Global
 * Signature: int isCineractive(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl isCineractive(void)

{
  return (uint)(Camera_Stack_Index < 8);
}
