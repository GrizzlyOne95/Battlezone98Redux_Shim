/*
 * Entry: 005c5ada
 * Name: isnumeral
 * Namespace: Global
 * Signature: int isnumeral(expdesc * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl isnumeral(expdesc *param_1)

{
  int *in_EAX;
  
  if (((*in_EAX == 5) && (in_EAX[4] == -1)) && (in_EAX[5] == -1)) {
    return 1;
  }
  return 0;
}
