
uint FUN_00835e4f(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  iVar1 = tolower(param_2);
  if (iVar1 < 0x74) {
    if (iVar1 == 0x73) {
      uVar2 = isspace(param_1);
    }
    else if (iVar1 == 0x61) {
      uVar2 = isalpha(param_1);
    }
    else if (iVar1 == 99) {
      uVar2 = iscntrl(param_1);
    }
    else if (iVar1 == 100) {
      uVar2 = isdigit(param_1);
    }
    else if (iVar1 == 0x6c) {
      uVar2 = islower(param_1);
    }
    else {
      if (iVar1 != 0x70) goto LAB_00835ece;
      uVar2 = ispunct(param_1);
    }
  }
  else if (iVar1 == 0x75) {
    uVar2 = isupper(param_1);
  }
  else if (iVar1 == 0x77) {
    uVar2 = isalnum(param_1);
  }
  else if (iVar1 == 0x78) {
    uVar2 = isxdigit(param_1);
  }
  else {
    if (iVar1 != 0x7a) {
LAB_00835ece:
      return (uint)(param_2 == param_1);
    }
    uVar2 = (uint)(param_1 == 0);
  }
  iVar1 = islower(param_2);
  uVar3 = (uint)(uVar2 == 0);
  if (iVar1 != 0) {
    uVar3 = uVar2;
  }
  return uVar3;
}

