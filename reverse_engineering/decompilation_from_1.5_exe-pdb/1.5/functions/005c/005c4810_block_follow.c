/*
 * Entry: 005c4810
 * Name: block_follow
 * Namespace: Global
 * Signature: int block_follow(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl block_follow(int param_1)

{
  int in_EAX;
  
  if ((0x103 < in_EAX) && (((in_EAX < 0x107 || (in_EAX == 0x114)) || (in_EAX == 0x11f)))) {
    return 1;
  }
  return 0;
}
