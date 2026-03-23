
void __fastcall FUN_0079de20(int param_1)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  undefined4 uVar5;
  int *piVar6;
  char *_Str;
  int iVar7;
  int iVar8;
  undefined4 *puVar9;
  undefined1 *puVar10;
  undefined1 local_74 [24];
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085fc30;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar2;
  iVar3 = FUN_006cc050(uVar2);
  if (((iVar3 == 2) || (iVar3 = FUN_006cc050(uVar2), iVar3 == 4)) &&
     (iVar3 = FUN_007cb0a0(), iVar3 != -1)) {
    piVar4 = (int *)FUN_004200d0(iVar3);
    cVar1 = (**(code **)(**(int **)(param_1 + 0x1c4) + 0x54))(*piVar4 + 0x10);
    if (cVar1 == '\x01') {
      uVar5 = FUN_0081cb40("multi_popup","lobbylocked");
      basic_string<>(uVar5);
      local_8 = 0;
      FUN_00745770(local_5c);
      local_8 = 0xffffffff;
      ~basic_string<>();
    }
    else {
      basic_string<>("userCount");
      local_8 = 1;
      piVar4 = (int *)FUN_00764760();
      puVar10 = local_74;
      piVar6 = (int *)FUN_004200d0(iVar3);
      _Str = (char *)(**(code **)(*piVar4 + 0x2c))(*piVar6 + 0x10,puVar10);
      iVar7 = atoi(_Str);
      piVar4 = (int *)FUN_004200d0(iVar3);
      iVar8 = *(int *)(*piVar4 + 0x120);
      local_8 = 0xffffffff;
      ~basic_string<>();
      if (iVar8 == iVar7) {
        uVar5 = FUN_0081cb40("multi_popup","lobbyfull");
        basic_string<>(uVar5);
        local_8 = 2;
        FUN_00745770(local_44);
        local_8 = 0xffffffff;
        ~basic_string<>();
      }
      else {
        piVar4 = (int *)FUN_004200d0(iVar3);
        if (*(char *)(*piVar4 + 0xb3) == '\0') {
          *(undefined1 *)(param_1 + 0x1fd) = 0;
          FUN_0079e920(1);
          *(undefined1 *)(param_1 + 0x1ff) = 1;
          puVar9 = (undefined4 *)FUN_004200d0(iVar3);
          FUN_0079e1d0(*puVar9);
          *(undefined4 *)(param_1 + 0x380) = 0;
        }
        else {
          iVar8 = FUN_004344a0();
          if (iVar8 == 2) {
            uVar5 = FUN_0081cb40("multi_popup","lobbylocked");
            basic_string<>(uVar5);
            local_8 = 3;
            FUN_00745770(local_2c);
            local_8 = 0xffffffff;
            ~basic_string<>();
          }
          else {
            FUN_007d0520(FUN_0079d730,FUN_0079d740,FUN_0079d750);
            *(undefined1 *)(param_1 + 0x1fc) = 1;
            *(undefined1 *)(param_1 + 0x1fe) = 1;
            *(undefined1 *)(param_1 + 0x1fd) = 0;
            FUN_007d3f20(4);
            uVar5 = FUN_0081cb40("multi_popup","password");
            FUN_007d0570(uVar5);
            (**(code **)(**(int **)(param_1 + 0x1c0) + 0x24))(1);
            FUN_007d05c0(0);
            CMFCToolBarsCustomizeDialog::EnableUserDefinedToolbars
                      (*(CMFCToolBarsCustomizeDialog **)(param_1 + 0x1c0),0x1e);
            (**(code **)(**(int **)(param_1 + 0x1bc) + 0x24))(0);
            FUN_007d04a0();
            puVar9 = (undefined4 *)FUN_004200d0(iVar3);
            FUN_0079e1d0(*puVar9);
          }
        }
      }
    }
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

