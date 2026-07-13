/*
 * Entry: 0044e930
 * Name: CleanStrip
 * Namespace: Global
 * Signature: void CleanStrip(Strip * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl CleanStrip(Strip *param_1)

{
  int in_EAX;
  
  *(undefined4 *)(in_EAX + 0x30) = 0;
  *(undefined1 *)(in_EAX + 0x21) = 0;
  *(undefined1 *)(in_EAX + 0x22) = 0;
  *(undefined1 *)(in_EAX + 0x23) = 0;
  *(undefined1 *)(in_EAX + 0x24) = 0;
  *(undefined1 *)(in_EAX + 0x25) = 0;
  *(undefined4 *)(in_EAX + 0x34) = 0;
  *(undefined4 *)(in_EAX + 0x38) = 0;
  return;
}
