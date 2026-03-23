
void FUN_007e5a80(undefined4 *param_1,undefined4 *param_2,int param_3)

{
  undefined4 uVar1;
  bool bVar2;
  void *pvVar3;
  undefined4 local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00863c4c;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  if (param_3 == 0) {
    uVar1 = *param_1;
    pvVar3 = operator_new(0x28);
    local_8 = 0;
    if (pvVar3 == (void *)0x0) {
      local_18 = 0;
    }
    else {
      local_18 = FUN_007dd690(uVar1);
    }
    *param_2 = local_18;
  }
  else if (param_3 == 1) {
    *param_2 = *param_1;
    *param_1 = 0;
  }
  else if (param_3 == 2) {
    operator_delete((void *)*param_2);
    *param_2 = 0;
  }
  else if (param_3 == 3) {
    bVar2 = type_info::operator==
                      ((type_info *)*param_2,
                       (type_info *)&.??@1701b513cb02cc8c4941a1b4e0b52557@::RTTI_Type_Descriptor);
    if (bVar2) {
      *param_2 = *param_1;
    }
    else {
      *param_2 = 0;
    }
  }
  else {
    *param_2 = &.??@1701b513cb02cc8c4941a1b4e0b52557@::RTTI_Type_Descriptor;
    *(undefined1 *)(param_2 + 1) = 0;
    *(undefined1 *)((int)param_2 + 5) = 0;
  }
  ExceptionList = local_10;
  return;
}

