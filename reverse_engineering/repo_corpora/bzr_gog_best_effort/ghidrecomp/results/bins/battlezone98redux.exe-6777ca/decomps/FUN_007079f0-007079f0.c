
void FUN_007079f0(int *param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  undefined1 local_8;
  char local_7;
  undefined1 local_6;
  undefined1 local_5;
  
  uVar1 = _Val_type<>();
  FUN_006d8860(&param_2,uVar1);
  do {
    local_c = FUN_006d6700(&param_2);
    local_10 = FUN_006d6700(&local_c);
    if (local_c == *param_1) {
LAB_00707bdc:
      local_28 = FUN_006d6700(param_1);
      uVar1 = FUN_00434910();
      FUN_006d8860(&local_28,uVar1);
      return;
    }
    iVar2 = FUN_00708500(&local_c);
    iVar3 = FUN_00434910();
    if ((iVar2 == iVar3) || (local_10 == *param_1)) goto LAB_00707bdc;
    uVar1 = _Val_type<>();
    FUN_006d8860(&local_10,uVar1);
    local_18 = FUN_006d6720(&local_10);
    local_7 = local_c == local_18;
    iVar2 = local_18;
    local_5 = local_7;
    if ((bool)local_7) {
      iVar2 = FUN_006d6730(&local_10);
    }
    local_1c = iVar2;
    local_14 = local_1c;
    if (local_1c == 0) {
LAB_00707b0e:
      iVar2 = FUN_006d6720(&local_c);
      local_8 = iVar2 == param_2;
      local_6 = local_8;
      if (local_7 == '\0') {
        if ((bool)local_8) {
          FUN_00708430(&local_c,&param_2);
          local_c = param_2;
        }
        local_24 = FUN_006d6700(&local_10);
        FUN_007083c0(&local_10,&local_c,&local_24,param_1);
      }
      else {
        if (!(bool)local_8) {
          FUN_00708360(&local_c,&param_2);
          local_c = param_2;
        }
        local_20 = FUN_006d6700(&local_10);
        FUN_00708490(&local_10,&local_c,&local_20,param_1);
      }
      uVar1 = FUN_00434910();
      FUN_006d8860(&local_c,uVar1);
      goto LAB_00707bdc;
    }
    iVar2 = FUN_00708500(&local_14);
    iVar3 = _Val_type<>();
    if (iVar2 != iVar3) goto LAB_00707b0e;
    uVar1 = FUN_00434910();
    FUN_006d8860(&local_14,uVar1);
    uVar1 = FUN_00434910();
    FUN_006d8860(&local_c,uVar1);
    param_2 = local_10;
  } while( true );
}

