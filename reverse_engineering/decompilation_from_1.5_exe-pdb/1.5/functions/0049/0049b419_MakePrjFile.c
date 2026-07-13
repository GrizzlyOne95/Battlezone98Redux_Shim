/*
 * Entry: 0049b419
 * Name: MakePrjFile
 * Namespace: Global
 * Signature: void MakePrjFile(char * param_1, long64 param_2, long param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl MakePrjFile(char *param_1,long64 param_2,long param_3)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  iVar1 = -(int)param_1;
  do {
    if (param_1[(int)(&stack0x00000008 + iVar1)] == '\0') break;
    *param_1 = param_1[(int)(&stack0x00000008 + iVar1)];
    param_1 = param_1 + 1;
    iVar2 = iVar2 + 1;
  } while (iVar2 < 8);
  *(undefined4 *)param_1 = param_2._4_4_;
  param_1[4] = '\0';
  return;
}
