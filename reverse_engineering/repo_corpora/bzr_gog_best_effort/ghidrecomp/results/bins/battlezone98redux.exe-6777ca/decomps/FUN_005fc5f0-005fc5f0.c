
void __fastcall FUN_005fc5f0(int param_1)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  void *pvVar4;
  float10 fVar5;
  undefined4 local_2c;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084a17c;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  if (*(int *)(param_1 + 0x38) == 0) {
    *(undefined4 *)(param_1 + 0x20) = 3;
  }
  else {
    if (*(int *)(param_1 + 0x3c) == 0) {
      iVar2 = FUN_00462d50(*(undefined4 *)(param_1 + 0x34),0x414d4d4f,0xffffffff,0x41f00000);
      if (iVar2 != 0) {
        uVar3 = FUN_00462380();
        *(undefined4 *)(param_1 + 0x3c) = uVar3;
        if (*(undefined4 **)(param_1 + 0x38) != (undefined4 *)0x0) {
          (**(code **)**(undefined4 **)(param_1 + 0x38))(1);
        }
        pvVar4 = operator_new(0x15c);
        local_8 = 0;
        if (pvVar4 == (void *)0x0) {
          local_2c = 0;
        }
        else {
          local_2c = FUN_004e7830(*(undefined4 *)(param_1 + 0x34),iVar2);
        }
        local_8 = 0xffffffff;
        *(undefined4 *)(param_1 + 0x38) = local_2c;
        if (*(int *)(param_1 + 0x38) == 0) {
          *(undefined4 *)(param_1 + 0x20) = 3;
          ExceptionList = local_10;
          return;
        }
      }
    }
    else {
      iVar2 = FUN_00462630(*(undefined4 *)(param_1 + 0x3c),DAT_008e7000 ^ (uint)&stack0xfffffffc);
      if (iVar2 == 0) {
        *(undefined4 *)(param_1 + 0x20) = 3;
        ExceptionList = local_10;
        return;
      }
      iVar2 = FUN_0045bba0();
      if ((iVar2 < 0x41) || (iVar2 = FUN_0045bba0(), 0x41 < iVar2)) {
        iVar2 = FUN_0045bba0();
        if (iVar2 == 3) {
          cVar1 = FUN_00472680();
          if ((cVar1 == '\0') || (iVar2 = FUN_00473890(), iVar2 != 0)) {
            cVar1 = FUN_00472680();
            if ((cVar1 == '\0') && (cVar1 = FUN_004723d0(), cVar1 == '\0')) {
              *(undefined4 *)(param_1 + 0x20) = 3;
              ExceptionList = local_10;
              return;
            }
          }
          else {
            FUN_004dbd60(0xb,*(undefined4 *)(param_1 + 0x34));
            *(undefined4 *)(param_1 + 0x3c) = 0;
          }
        }
        else {
          cVar1 = (**(code **)(**(int **)(param_1 + 0x38) + 0x18))();
          if (cVar1 != '\0') {
            *(undefined4 *)(param_1 + 0x20) = 3;
            ExceptionList = local_10;
            return;
          }
        }
      }
      else {
        fVar5 = (float10)FUN_0046d080();
        if (1.0 <= (float)fVar5) {
          *(undefined4 *)(param_1 + 0x20) = 3;
          ExceptionList = local_10;
          return;
        }
      }
    }
    (**(code **)(**(int **)(param_1 + 0x38) + 0x1c))();
  }
  ExceptionList = local_10;
  return;
}

