
int FUN_006924a0(int param_1,uint param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int local_8;
  
  FUN_006a5fd0("AIBuild_FindFacilityLocation Begins\n");
  local_8 = 0;
  iVar1 = FUN_006a0670(param_2 & 0xffff);
  if (*(int *)(iVar1 + 0x2c) == 0) {
    if (*(int *)(iVar1 + 0x30) == 0) {
      if ((*(int *)(param_1 + 0x594) == 0) &&
         (local_8 = FUN_00692200(param_1,param_2,param_3,param_4), local_8 == 0)) {
        *(undefined4 *)(param_1 + 0x594) = 300;
      }
    }
    else if ((*(int *)(param_1 + 0x58c) == 0) &&
            (local_8 = FUN_00692030(param_1,1,iVar1,*(undefined4 *)(param_1 + 0x244),
                                    *(undefined4 *)(param_1 + 0x248),param_3,param_4), local_8 == 0)
            ) {
      *(undefined4 *)(param_1 + 0x58c) = 300;
    }
  }
  else if ((*(int *)(param_1 + 0x590) == 0) &&
          (local_8 = FUN_00692030(param_1,0,iVar1,*(undefined4 *)(param_1 + 0x244),
                                  *(undefined4 *)(param_1 + 0x248),param_3,param_4), local_8 == 0))
  {
    *(undefined4 *)(param_1 + 0x590) = 300;
  }
  return local_8;
}

