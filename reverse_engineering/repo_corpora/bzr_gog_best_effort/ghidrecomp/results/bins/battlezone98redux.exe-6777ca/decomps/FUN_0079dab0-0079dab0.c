
void __fastcall FUN_0079dab0(int param_1)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_0085fbb0;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  cVar1 = operator!=<>(&stack0x00000004,&DAT_008a1ad8,local_14);
  if (cVar1 != '\0') {
    if (*(char *)(param_1 + 0x1fe) == '\0') {
      if (*(char *)(param_1 + 0x1fd) == '\0') {
        iVar2 = FUN_006cc050();
        if (iVar2 == 4) {
          FUN_00740a90(0);
        }
        basic_string<>(&DAT_008a1ad8);
        local_8._0_1_ = 1;
        (**(code **)(**(int **)(param_1 + 0x1c4) + 0x14))(0,local_2c,&stack0x00000004);
        local_8 = (uint)local_8._1_3_ << 8;
        ~basic_string<>();
        FUN_007d04a0();
      }
      else {
        cVar1 = FUN_007d05f0();
        if (cVar1 == '\0') {
          *(undefined1 *)(param_1 + 0x1fe) = 1;
          uVar3 = FUN_0081cb40("multi_popup","password");
          FUN_007d0570(uVar3);
          FUN_007d05c0(0);
          CMFCToolBarsCustomizeDialog::EnableUserDefinedToolbars
                    (*(CMFCToolBarsCustomizeDialog **)(param_1 + 0x1c0),0x1e);
          FUN_007d04a0();
          FID_conflict_operator_(&stack0x00000004);
        }
        else {
          iVar2 = FUN_006cc050();
          if (iVar2 == 4) {
            FUN_00740a90(0);
          }
          *(undefined1 *)(param_1 + 0x1ff) = 1;
          FUN_0079e920(1);
          *(undefined4 *)(param_1 + 0x380) = 0;
          FID_conflict_operator_(&stack0x00000004);
        }
      }
    }
    else {
      iVar2 = FUN_006cc050();
      if (iVar2 == 4) {
        FUN_00740a90(0);
      }
      *(undefined1 *)(param_1 + 0x1ff) = 1;
      FUN_0079e920(1);
      *(undefined4 *)(param_1 + 0x380) = 0;
      FID_conflict_operator_(&stack0x00000004);
    }
  }
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

