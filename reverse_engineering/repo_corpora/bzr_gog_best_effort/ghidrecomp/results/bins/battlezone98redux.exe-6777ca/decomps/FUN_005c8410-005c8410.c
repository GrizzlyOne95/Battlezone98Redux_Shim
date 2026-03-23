
undefined1 FUN_005c8410(undefined4 param_1,char *param_2)

{
  int iVar1;
  int local_18 [2];
  undefined1 local_10;
  int local_8;
  
  local_8 = FUN_00462630(param_1);
  if (local_8 == 0) {
    local_10 = 0;
  }
  else {
    local_18[0] = 0;
    local_18[1] = 0;
    strncpy((char *)local_18,param_2,8);
    iVar1 = (*(code *)**(undefined4 **)(local_8 + 0x18))();
    if ((*(int *)(iVar1 + 0x30) == local_18[0]) && (*(int *)(iVar1 + 0x34) == local_18[1])) {
      local_10 = 1;
    }
    else {
      local_10 = 0;
    }
  }
  return local_10;
}

