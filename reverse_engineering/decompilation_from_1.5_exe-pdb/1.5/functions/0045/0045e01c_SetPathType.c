/*
 * Entry: 0045e01c
 * Name: SetPathType
 * Namespace: Global
 * Signature: void SetPathType(char * param_1, PathType param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SetPathType(char *param_1,PathType param_2)

{
  AiPath *pAVar1;
  
  pAVar1 = AiPath::Find(param_1);
  if (pAVar1 != (AiPath *)0x0) {
    pAVar1->pathType = param_2;
  }
  return;
}
