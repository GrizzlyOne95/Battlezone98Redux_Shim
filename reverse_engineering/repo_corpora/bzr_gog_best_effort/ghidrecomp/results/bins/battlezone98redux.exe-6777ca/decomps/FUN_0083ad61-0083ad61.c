
void FUN_0083ad61(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 local_20 [24];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  uVar1 = *(undefined4 *)(param_1 + 0x30);
  if (*(int *)(param_1 + 0x10) == 0x28) {
    uVar2 = *(undefined4 *)(param_1 + 4);
    FUN_00838ffd(param_1);
    FUN_0083b5a6(param_1,param_2,0);
    FUN_00839b38(param_1,0x29,0x28,uVar2);
    FUN_0083c667(*(undefined4 *)(param_1 + 0x30),param_2);
  }
  else if (*(int *)(param_1 + 0x10) == 0x11d) {
    FUN_0083b36f(param_1,param_2);
  }
  else {
    FUN_008390b7(param_1,"unexpected symbol");
  }
LAB_0083add7:
  do {
    while (iVar3 = *(int *)(param_1 + 0x10), iVar3 == 0x28) {
LAB_0083adfa:
      FUN_0083c800(uVar1,param_2);
      FUN_0083a565(param_1,param_2);
    }
    if (iVar3 == 0x2e) {
      FUN_0083a1ce(param_1,param_2);
      goto LAB_0083add7;
    }
    if (iVar3 == 0x3a) {
      FUN_00838ffd(param_1);
      FUN_00839b96(param_1,local_20);
      FUN_0083cd68(uVar1,param_2,local_20);
      FUN_0083a565(param_1,param_2);
    }
    else {
      if (iVar3 != 0x5b) {
        if ((iVar3 != 0x7b) && (iVar3 != 0x11e)) {
          FUN_0083e885();
          return;
        }
        goto LAB_0083adfa;
      }
      FUN_0083c7b7(uVar1,param_2);
      FUN_0083b767(param_1,local_20);
      FUN_0083c93c(uVar1,param_2,local_20);
    }
  } while( true );
}

