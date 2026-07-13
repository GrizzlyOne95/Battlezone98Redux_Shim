
void __fastcall FUN_005fb1e0(int param_1)

{
  int iVar1;
  undefined1 local_14;
  
  switch(*(undefined4 *)(param_1 + 0x20)) {
  case 4:
    *(undefined4 *)(param_1 + 0x10) = *(undefined4 *)(*(int *)(param_1 + 0x34) + 0xb4);
    *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(*(int *)(param_1 + 0x34) + 0xb0);
    iVar1 = *(int *)(*(int *)(param_1 + 0x34) + 0xc4);
    if ((iVar1 < 1) && ((iVar1 < 0 || (*(uint *)(*(int *)(param_1 + 0x34) + 0xc0) < 2)))) {
      local_14 = 1;
    }
    else {
      local_14 = 0;
    }
    *(undefined1 *)(param_1 + 0x40) = local_14;
    break;
  case 5:
    *(undefined4 *)(param_1 + 0x10) = *(undefined4 *)(*(int *)(param_1 + 0x34) + 0xb4);
    break;
  case 6:
    *(undefined4 *)(param_1 + 0x10) = *(undefined4 *)(*(int *)(param_1 + 0x34) + 0xb4);
    *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(*(int *)(param_1 + 0x34) + 0xb0);
    break;
  case 7:
  case 8:
    *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(*(int *)(param_1 + 0x34) + 0xb0);
    break;
  case 9:
    *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(*(int *)(param_1 + 0x34) + 0xb0);
    break;
  case 0xc:
    *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(*(int *)(param_1 + 0x34) + 0xb0);
  }
  *(undefined4 *)(param_1 + 0x24) = 0;
  *(undefined4 *)(param_1 + 0x28) = 0;
  *(undefined4 *)(param_1 + 0x2c) = 0;
  return;
}

