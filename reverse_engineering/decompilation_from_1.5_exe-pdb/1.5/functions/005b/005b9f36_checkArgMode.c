/*
 * Entry: 005b9f36
 * Name: checkArgMode
 * Namespace: Global
 * Signature: int checkArgMode(Proto * param_1, int param_2, OpArgMask param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl checkArgMode(Proto *param_1,int param_2,OpArgMask param_3)

{
  int iVar1;
  uint in_EAX;
  int in_ECX;
  int in_EDX;
  bool bVar2;
  
  if (in_EDX == 0) {
    if (in_EAX != 0) {
      return 0;
    }
  }
  else if (in_EDX == 2) {
    if ((int)(uint)*(byte *)(in_ECX + 0x4b) <= (int)in_EAX) {
      return 0;
    }
  }
  else if (in_EDX == 3) {
    if ((in_EAX & 0x100) == 0) {
      bVar2 = SBORROW4(in_EAX,(uint)*(byte *)(in_ECX + 0x4b));
      iVar1 = in_EAX - *(byte *)(in_ECX + 0x4b);
    }
    else {
      bVar2 = SBORROW4(in_EAX & 0xfffffeff,*(int *)(in_ECX + 0x28));
      iVar1 = (in_EAX & 0xfffffeff) - *(int *)(in_ECX + 0x28);
    }
    if (bVar2 == iVar1 < 0) {
      return 0;
    }
  }
  return 1;
}
