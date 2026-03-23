
void FUN_00695b00(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_14;
  undefined4 local_c;
  undefined4 local_8;
  
  for (local_8 = 0; local_8 < *(int *)(param_1 + 0x78); local_8 = local_8 + 1) {
    for (local_c = 0; local_c < *(int *)(param_1 + 0x7c); local_c = local_c + 1) {
      iVar1 = *(int *)(*(int *)(*(int *)(param_1 + 0x80) + local_8 * 4) + local_c * 4);
      *(undefined4 *)(iVar1 + 0x4c) = *(undefined4 *)(iVar1 + 0x48);
    }
  }
  for (local_14 = 0; local_14 < *(int *)(*(int *)(param_1 + 0x60) + 0x78); local_14 = local_14 + 1)
  {
    for (local_8 = 0; local_8 < *(int *)(param_1 + 0x78); local_8 = local_8 + 1) {
      for (local_c = 0; local_c < *(int *)(param_1 + 0x7c); local_c = local_c + 1) {
        uVar2 = *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x80) + local_8 * 4) + local_c * 4);
        FUN_00695a70(param_1,uVar2,local_8 + -1,local_c,0x3f800000);
        FUN_00695a70(param_1,uVar2,local_8 + 1,local_c,0x3f800000);
        FUN_00695a70(param_1,uVar2,local_8,local_c + -1,0x3f800000);
        FUN_00695a70(param_1,uVar2,local_8,local_c + 1,0x3f800000);
        FUN_00695a70(param_1,uVar2,local_8 + -1,local_c + -1,0x3fb47ae1);
        FUN_00695a70(param_1,uVar2,local_8 + -1,local_c + 1,0x3fb47ae1);
        FUN_00695a70(param_1,uVar2,local_8 + 1,local_c + -1,0x3fb47ae1);
        FUN_00695a70(param_1,uVar2,local_8 + 1,local_c + 1,0x3fb47ae1);
      }
    }
    for (local_8 = 0; local_8 < *(int *)(param_1 + 0x78); local_8 = local_8 + 1) {
      for (local_c = 0; local_c < *(int *)(param_1 + 0x7c); local_c = local_c + 1) {
        iVar1 = *(int *)(*(int *)(*(int *)(param_1 + 0x80) + local_8 * 4) + local_c * 4);
        *(undefined4 *)(iVar1 + 0x48) = *(undefined4 *)(iVar1 + 0x4c);
      }
    }
  }
  return;
}

