/*
 * Entry: 005c00c0
 * Name: match_class
 * Namespace: Global
 * Signature: int match_class(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl match_class(int param_1,int param_2)

{
  int in_EAX;
  int iVar1;
  uint uVar2;
  bool bVar3;
  
  iVar1 = tolower(param_1);
  if (iVar1 < 0x74) {
    if (iVar1 == 0x73) {
      uVar2 = isspace(in_EAX);
    }
    else if (iVar1 == 0x61) {
      uVar2 = isalpha(in_EAX);
    }
    else if (iVar1 == 99) {
      uVar2 = iscntrl(in_EAX);
    }
    else if (iVar1 == 100) {
      uVar2 = isdigit(in_EAX);
    }
    else if (iVar1 == 0x6c) {
      uVar2 = islower(in_EAX);
    }
    else {
      if (iVar1 != 0x70) goto LAB_005c0134;
      uVar2 = ispunct(in_EAX);
    }
  }
  else if (iVar1 == 0x75) {
    uVar2 = isupper(in_EAX);
  }
  else if (iVar1 == 0x77) {
    uVar2 = isalnum(in_EAX);
  }
  else if (iVar1 == 0x78) {
    uVar2 = isxdigit(in_EAX);
  }
  else {
    if (iVar1 != 0x7a) {
LAB_005c0134:
      bVar3 = param_1 == in_EAX;
      goto LAB_005c0174;
    }
    uVar2 = (uint)(in_EAX == 0);
  }
  iVar1 = islower(param_1);
  if (iVar1 != 0) {
    return uVar2;
  }
  bVar3 = uVar2 == 0;
LAB_005c0174:
  return (uint)bVar3;
}
