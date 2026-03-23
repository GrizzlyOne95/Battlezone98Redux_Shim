
undefined4
FUN_007d9a00(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  undefined1 local_12 [5];
  undefined1 local_d [9];
  
  uVar2 = 0;
  uVar1 = make_input_adapter_character_source<>(local_12,param_2,param_3,param_4,param_5,0);
  FUN_007dae20(uVar1,uVar2);
  puVar3 = local_d;
  uVar1 = FUN_007d9f90(puVar3);
  uVar1 = FUN_007da140(uVar1,puVar3);
  FUN_007dae40(param_1,uVar1);
  return param_1;
}

