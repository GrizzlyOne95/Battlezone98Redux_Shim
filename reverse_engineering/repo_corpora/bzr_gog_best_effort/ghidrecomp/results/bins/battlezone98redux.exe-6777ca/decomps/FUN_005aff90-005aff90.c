
char __thiscall FUN_005aff90(int param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  undefined8 local_18;
  undefined4 local_10;
  int local_c;
  char local_5;
  
  local_c = param_1;
  uVar2 = FUN_00462630(*(undefined4 *)(param_1 + 0x30c));
  *(undefined4 *)(local_c + 0x310) = uVar2;
  if (*(int *)(local_c + 0x300) == 0) {
    local_18 = 0;
  }
  else {
    local_18 = *(undefined8 *)(*(int *)(local_c + 0x300) + 0x30);
  }
  cVar1 = FUN_004cd360(param_2,*(int *)(local_c + 0xf8) + 0x5f0,4,"timeDeploy");
  if (cVar1 != '\0') {
    cVar1 = FUN_004cd360(param_2,*(int *)(local_c + 0xf8) + 0x5f4,4,"timeUndeploy");
    if (cVar1 != '\0') {
      cVar1 = FUN_004cf520(param_2,local_c + 0x310,4,"undefptr");
      if (cVar1 != '\0') {
        cVar1 = FUN_0045c3c0(param_2,local_c + 0x228,4,"state");
        if (cVar1 != '\0') {
          cVar1 = FUN_004cd360(param_2,local_c + 0x318,4,"delayTimer");
          if (cVar1 != '\0') {
            cVar1 = FUN_004cd360(param_2,local_c + 0x31c,4,"nextRepair");
            if (cVar1 != '\0') {
              cVar1 = FUN_004cda70(param_2,&local_18,8,"buildClass");
              if (cVar1 != '\0') {
                cVar1 = FUN_004cd360(param_2,local_c + 0x304,4,"buildDoneTime");
                if (cVar1 != '\0') {
                  local_10 = 1;
                  goto LAB_005b0125;
                }
              }
            }
          }
        }
      }
    }
  }
  local_10 = 0;
LAB_005b0125:
  local_5 = (char)local_10;
  if ((char)local_10 != '\0') {
    local_5 = FUN_004ea280(param_2);
  }
  return local_5;
}

