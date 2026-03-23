
undefined4
FUN_0069b4e0(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4,undefined4 param_5
            ,int param_6,undefined4 param_7)

{
  void *pvVar1;
  undefined1 local_24 [4];
  undefined4 local_20;
  int local_1c;
  undefined4 local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  local_18 = 0;
  local_c = 3;
  local_10 = FUN_00699800(param_1,param_2);
  for (; *(char *)(local_c * 0x50 + param_6) != ']'; local_c = local_c + 1) {
  }
  FUN_006978d0(param_1,2,local_c + -1,param_4,param_5,param_6,param_7,local_24,&local_1c,&local_18);
  local_8 = FUN_006994c0(8,param_6);
  *(int *)(local_8 + 0x18) = local_10;
  pvVar1 = malloc(*(int *)(local_10 + 4) * local_1c);
  *(void **)(local_8 + 8) = pvVar1;
  local_20 = *(undefined4 *)(local_8 + 8);
  local_14 = local_c + 4;
  while (local_14 < param_3 + -1) {
    FUN_0069b480(param_1,local_10,&local_20,param_4,param_5,param_6,param_7,&local_14);
    *(int *)(local_8 + 0x1c) = *(int *)(local_8 + 0x1c) + 1;
  }
  FUN_00699650(param_1,local_8);
  return local_18;
}

