
undefined4 __thiscall FUN_005f2650(int param_1,undefined4 param_2)

{
  char cVar1;
  char extraout_AL;
  uint uVar2;
  undefined3 uVar3;
  undefined3 extraout_var;
  undefined4 local_14;
  undefined4 local_10;
  int local_c;
  undefined1 local_6;
  char local_5;
  
  local_6 = 0;
  local_14 = 0;
  local_c = param_1;
  cVar1 = FUN_004cd360(param_2,*(int *)(param_1 + 0xf8) + 0x5f0,4,"undeffloat");
  uVar2 = 0;
  if (cVar1 != '\0') {
    cVar1 = FUN_004cd360(param_2,&local_14,4,"undeffloat");
    uVar2 = 0;
    if (cVar1 != '\0') {
      uVar2 = FUN_004cd360(param_2,*(int *)(local_c + 0xf8) + 0x5f4,4,"undeffloat");
      if ((uVar2 & 0xff) != 0) {
        uVar2 = FUN_004cd360(param_2,*(int *)(local_c + 0xf8) + 0x5f8,4,"undeffloat");
        if ((uVar2 & 0xff) != 0) {
          uVar2 = FUN_0045c3c0(param_2,local_c + 0x228,4,"undefraw");
          if ((uVar2 & 0xff) != 0) {
            uVar2 = FUN_004cd360(param_2,local_c + 0x308,4,"undeffloat");
            if ((uVar2 & 0xff) != 0) {
              uVar2 = FUN_004ccf20(param_2,&local_6,1,"undefbool");
              if ((uVar2 & 0xff) != 0) {
                local_10 = 1;
                goto LAB_005f2785;
              }
            }
          }
        }
      }
    }
  }
  local_10 = 0;
LAB_005f2785:
  uVar3 = (undefined3)(uVar2 >> 8);
  local_5 = (char)local_10;
  if ((char)local_10 != '\0') {
    FUN_004ea280(param_2);
    uVar3 = extraout_var;
    local_5 = extraout_AL;
  }
  return CONCAT31(uVar3,local_5);
}

