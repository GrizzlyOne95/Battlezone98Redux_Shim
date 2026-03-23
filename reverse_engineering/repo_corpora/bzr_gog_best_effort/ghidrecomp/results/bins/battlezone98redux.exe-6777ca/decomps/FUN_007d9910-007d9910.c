
undefined4
FUN_007d9910(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  undefined1 local_30 [20];
  undefined1 local_1c [24];
  
  uVar2 = 0;
  uVar1 = make_input_adapter_character_source<>(local_30,param_2,param_3,param_4,param_5,0);
  FUN_007dad60(uVar1,uVar2);
  puVar3 = local_1c;
  uVar1 = FUN_007d9f90(puVar3);
  uVar1 = FUN_007da0a0(uVar1,puVar3);
  FUN_007dad80(param_1,uVar1);
  return param_1;
}

