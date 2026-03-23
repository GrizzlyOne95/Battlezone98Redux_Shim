
void __thiscall FUN_00766410(int param_1,int param_2,undefined4 param_3)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  uint local_c;
  
  *(undefined4 *)(param_1 + 0x60) = 0;
  *(undefined4 *)(param_1 + 0x3c) = 0;
  if ((param_2 < 5) && (iVar2 = FUN_00766f80(), iVar2 != 0)) {
    *(int *)(param_1 + 0x60) = param_2;
  }
  while ((*(int *)(param_1 + 0x60) < 5 && (iVar2 = FUN_00766f80(), iVar2 == 0))) {
    *(int *)(param_1 + 0x60) = *(int *)(param_1 + 0x60) + 1;
  }
  if (*(int *)(param_1 + 0x60) == 5) {
    *(undefined4 *)(param_1 + 0x60) = 0;
  }
  local_c = 0;
  while( true ) {
    uVar3 = FUN_00766f80();
    if (uVar3 <= local_c) {
      return;
    }
    uVar5 = param_3;
    uVar4 = FUN_00766fa0(local_c);
    cVar1 = FUN_00427310(uVar4,uVar5);
    if (cVar1 != '\0') break;
    local_c = local_c + 1;
  }
  *(uint *)(param_1 + 0x3c) = local_c;
  return;
}

