
void __thiscall FUN_004a6a50(int param_1,int param_2)

{
  char cVar1;
  undefined4 uVar2;
  int *piVar3;
  undefined4 uVar4;
  int local_10;
  
  FUN_004a6d50();
  uVar2 = FUN_00462370();
  for (local_10 = *(int *)(&DAT_008e7994 + param_2 * 0xc);
      local_10 <= *(int *)(&DAT_008e7998 + param_2 * 0xc); local_10 = local_10 + 1) {
    piVar3 = (int *)FUN_005e0f70(local_10);
    if (piVar3 != (int *)0x0) {
      cVar1 = (**(code **)(*piVar3 + 0x38))(uVar2);
      if (cVar1 != '\0') {
        FUN_0049f3c0(1);
        uVar4 = FUN_00462380();
        *(undefined4 *)(param_1 + 0x1c + *(int *)(param_1 + 0x188) * 4) = uVar4;
        *(int *)(param_1 + 0x188) = *(int *)(param_1 + 0x188) + 1;
      }
    }
  }
  return;
}

