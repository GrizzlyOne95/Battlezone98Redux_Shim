/*
 * Entry: 005c79d0
 * Name: _ValidateImageBase
 * Namespace: Global
 * Signature: int _ValidateImageBase(uchar * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl _ValidateImageBase(uchar *param_1)

{
  if ((*(short *)param_1 == 0x5a4d) && (*(int *)(param_1 + *(int *)(param_1 + 0x3c)) == 0x4550)) {
    return (uint)((short)*(int *)((int)(param_1 + *(int *)(param_1 + 0x3c)) + 0x18) == 0x10b);
  }
  return 0;
}
