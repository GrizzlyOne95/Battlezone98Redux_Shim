
int FUN_0061ea90(undefined4 *param_1,int param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  uint local_20;
  undefined *local_1c;
  int local_18;
  int local_8;
  
  iVar1 = DAT_0091a430;
  local_8 = 0;
  do {
    if (DAT_0091a430 <= local_8) {
      DAT_0091a430 = DAT_0091a430 + 1;
      if (DAT_0091a430 < 0x15) {
        if (param_2 == 0) {
          local_18 = -1;
        }
        else {
          local_18 = FUN_0061e1c0(param_2);
        }
        *(int *)(&DAT_00919904 + iVar1 * 0x84) = local_18;
        *(int *)(&DAT_00919908 + iVar1 * 0x84) = param_3;
        uVar2 = FUN_0061e5d0(param_1);
        *(undefined4 *)(&DAT_00919918 + iVar1 * 0x84) = uVar2;
        if (local_18 < 0) {
          local_1c = (undefined *)0x0;
        }
        else {
          local_1c = &DAT_02a142e0 + param_3 * 4 + local_18 * 0x50;
        }
        *(undefined **)(&DAT_0091990c + iVar1 * 0x84) = local_1c;
        iVar3 = strncmp((char *)*param_1,"menu_",5);
        local_20 = (uint)(iVar3 == 0);
        *(uint *)(&DAT_00919980 + iVar1 * 0x84) = local_20;
      }
      else {
        FUN_007d6830("Too many analog controls: line %d",DAT_0091fef8);
        iVar1 = -1;
      }
      return iVar1;
    }
    if ((*(int *)(&DAT_00919918 + local_8 * 0x84) != 0) &&
       (**(int **)(&DAT_00919918 + local_8 * 0x84) == param_1[1])) {
      if (param_2 == 0) {
        return local_8;
      }
      if (*(int *)(&DAT_0091990c + local_8 * 0x84) == 0) {
        iVar1 = FUN_0061e1c0(param_2);
        *(undefined **)(&DAT_0091990c + local_8 * 0x84) = &DAT_02a142e0 + param_3 * 4 + iVar1 * 0x50
        ;
        *(undefined4 *)(&DAT_00919900 + local_8 * 0x84) = *param_1;
        *(int *)(&DAT_00919904 + local_8 * 0x84) = iVar1;
        *(int *)(&DAT_00919908 + local_8 * 0x84) = param_3;
        return local_8;
      }
    }
    local_8 = local_8 + 1;
  } while( true );
}

