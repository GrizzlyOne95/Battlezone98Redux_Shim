
void FUN_0082f0d6(int param_1,int param_2,undefined4 param_3)

{
  code *pcVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int local_6c [5];
  undefined4 local_58;
  int local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  pcVar1 = *(code **)(param_1 + 0x44);
  if ((pcVar1 != (code *)0x0) && (*(char *)(param_1 + 0x39) != '\0')) {
    iVar2 = *(int *)(param_1 + 8);
    iVar3 = *(int *)(*(int *)(param_1 + 0x14) + 8);
    iVar4 = *(int *)(param_1 + 0x20);
    iVar5 = *(int *)(param_1 + 0x20);
    local_6c[0] = param_2;
    local_58 = param_3;
    if (param_2 == 4) {
      local_c = 0;
    }
    else {
      local_c = (*(int *)(param_1 + 0x14) - *(int *)(param_1 + 0x28)) / 0x18;
    }
    if (*(int *)(param_1 + 0x1c) - *(int *)(param_1 + 8) < 0x141) {
      FUN_0082f194(param_1,0x14);
    }
    *(int *)(*(int *)(param_1 + 0x14) + 8) = *(int *)(param_1 + 8) + 0x140;
    *(undefined1 *)(param_1 + 0x39) = 0;
    (*pcVar1)(param_1,local_6c);
    *(undefined1 *)(param_1 + 0x39) = 1;
    *(int *)(*(int *)(param_1 + 0x14) + 8) = *(int *)(param_1 + 0x20) + (iVar3 - iVar4);
    *(int *)(param_1 + 8) = *(int *)(param_1 + 0x20) + (iVar2 - iVar5);
  }
  FUN_0083e885();
  return;
}

