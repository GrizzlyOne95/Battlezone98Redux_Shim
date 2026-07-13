
void __fastcall FUN_005c53b0(int param_1)

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
  if (*(int *)(param_1 + 0x58) == 0) {
    *(undefined4 *)(param_1 + 0x20) = 1;
  }
  else {
    if (*(int *)(param_1 + 0x24) == 0) {
      iVar2 = FUN_00462d50(*(undefined4 *)(param_1 + 0x28),0x524b4954,0xffffffff,0x41f00000);
      if (iVar2 != 0) {
        uVar3 = FUN_00462380();
        *(undefined4 *)(param_1 + 0x24) = uVar3;
        if (*(undefined4 **)(param_1 + 0x58) != (undefined4 *)0x0) {
          (**(code **)**(undefined4 **)(param_1 + 0x58))(1);
        }
        pvVar4 = operator_new(0x15c);
        local_8 = 0;
        if (pvVar4 == (void *)0x0) {
          local_2c = 0;
        }
        else {
          local_2c = FUN_004e7830(*(undefined4 *)(param_1 + 0x28),iVar2);
        }
        local_8 = 0xffffffff;
        *(undefined4 *)(param_1 + 0x58) = local_2c;
        if (*(int *)(param_1 + 0x58) == 0) {
          *(undefined4 *)(param_1 + 0x20) = 1;
          ExceptionList = local_10;
          return;
        }
      }
    }
    else {
      iVar2 = FUN_00462630(*(undefined4 *)(param_1 + 0x24),DAT_008e7000 ^ (uint)&stack0xfffffffc);
      if (iVar2 == 0) {
        *(undefined4 *)(param_1 + 0x20) = 1;
        ExceptionList = local_10;
        return;
      }
      iVar2 = FUN_0045bba0();
      if ((iVar2 < 0x3c) || (iVar2 = FUN_0045bba0(), 0x40 < iVar2)) {
        iVar2 = FUN_0045bba0();
        if (iVar2 == 3) {
          cVar1 = FUN_00472700();
          if ((cVar1 == '\0') || (iVar2 = FUN_00473890(), iVar2 != 0)) {
            cVar1 = FUN_00472700();
            if ((cVar1 == '\0') && (cVar1 = FUN_004723d0(), cVar1 == '\0')) {
              *(undefined4 *)(param_1 + 0x20) = 1;
              ExceptionList = local_10;
              return;
            }
          }
          else {
            FUN_004dbd60(10,*(undefined4 *)(param_1 + 0x28));
            *(undefined4 *)(param_1 + 0x24) = 0;
          }
        }
        else {
          cVar1 = (**(code **)(**(int **)(param_1 + 0x58) + 0x18))();
          if (cVar1 != '\0') {
            *(undefined4 *)(param_1 + 0x20) = 1;
            ExceptionList = local_10;
            return;
          }
        }
      }
      else {
        fVar5 = (float10)(**(code **)(*(int *)(*(int *)(param_1 + 0x28) + 0x18) + 0x1c))();
        if (1.0 <= (float)fVar5) {
          *(undefined4 *)(param_1 + 0x20) = 1;
          ExceptionList = local_10;
          return;
        }
      }
    }
    (**(code **)(**(int **)(param_1 + 0x58) + 0x1c))();
  }
  ExceptionList = local_10;
  return;
}

