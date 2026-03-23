
void __fastcall FUN_005c3ec0(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  int local_10;
  
  iVar1 = FUN_00572a70();
  if (((iVar1 == 0) && (uVar4 = 1, *(int *)(param_1 + 0x4c) != 1)) &&
     (*(int *)(param_1 + 0x54) != 0)) {
    for (local_10 = 0; local_10 < *(int *)(*(int *)(param_1 + 0x54) + 8); local_10 = local_10 + 1) {
      uVar2 = FUN_0069d590(*(undefined4 *)(param_1 + 0x54),local_10);
      iVar1 = FUN_00462630(uVar2,uVar4,uVar2);
      if (iVar1 == 0) {
        FUN_005c4080(uVar2);
      }
      else if (((*(int *)(iVar1 + 0xac) != 5) ||
               (iVar3 = FUN_00477590(*(undefined4 *)(param_1 + 0x28)),
               *(int *)(iVar1 + 0xb0) != iVar3)) &&
              ((*(int *)(iVar1 + 0xcc) != 5 ||
               (iVar3 = FUN_00477590(*(undefined4 *)(param_1 + 0x28)),
               *(int *)(iVar1 + 0xd0) != iVar3)))) {
        FUN_005c4080(uVar2);
      }
    }
  }
  return;
}

