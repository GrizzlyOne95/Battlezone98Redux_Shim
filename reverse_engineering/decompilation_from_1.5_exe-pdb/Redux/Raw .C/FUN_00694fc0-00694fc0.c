
void FUN_00694fc0(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined4 local_c;
  undefined4 local_8;
  
  uVar1 = FUN_0069ef40(0,param_3,0,param_2);
  *(undefined4 *)(param_1 + 0x84) = uVar1;
  uVar1 = FUN_0069ef40(0,param_3,0,param_2);
  *(undefined4 *)(param_1 + 0x88) = uVar1;
  for (local_8 = 0; local_8 < *(int *)(param_1 + 0x78); local_8 = local_8 + 1) {
    for (local_c = 0; local_c < *(int *)(param_1 + 0x7c); local_c = local_c + 1) {
      *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x84) + local_8 * 4) + local_c * 4) = 0;
      *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x88) + local_8 * 4) + local_c * 4) =
           *(undefined4 *)(param_1 + 0x78);
    }
  }
  uVar1 = FUN_0069ef40(0,param_3,0,param_2);
  *(undefined4 *)(param_1 + 0x90) = uVar1;
  uVar1 = FUN_0069ef40(0,param_3,0,param_2);
  *(undefined4 *)(param_1 + 0x94) = uVar1;
  for (local_8 = 0; local_8 < *(int *)(param_1 + 0x78); local_8 = local_8 + 1) {
    for (local_c = 0; local_c < *(int *)(param_1 + 0x7c); local_c = local_c + 1) {
      *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x90) + local_8 * 4) + local_c * 4) = 0;
      *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x94) + local_8 * 4) + local_c * 4) =
           *(undefined4 *)(param_1 + 0x78);
    }
  }
  return;
}

