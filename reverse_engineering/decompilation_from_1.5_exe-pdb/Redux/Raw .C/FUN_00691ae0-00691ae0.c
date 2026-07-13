
undefined4 FUN_00691ae0(int param_1,int param_2,int param_3,int param_4)

{
  undefined4 uVar1;
  int iVar2;
  int local_c;
  int local_8;
  
  if ((((param_1 < 0) || (DAT_008eda24 < param_1 + param_3)) || (param_2 < 0)) ||
     (DAT_008eda20 < param_2 + param_4)) {
    uVar1 = 0;
  }
  else {
    for (local_8 = 0; local_8 < param_4; local_8 = local_8 + 1) {
      for (local_c = 0; local_c < param_3; local_c = local_c + 1) {
        iVar2 = FUN_006a6120(param_1 + local_c,param_2 + local_8,"Schedule\\Aibuild.cpp",0x654);
        if (*(int *)(iVar2 + 0x10) != 0) {
          return 0;
        }
      }
    }
    uVar1 = 1;
  }
  return uVar1;
}

