
bool FUN_00807870(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined1 local_38 [24];
  undefined1 local_20 [20];
  undefined4 local_c;
  undefined4 local_8;
  
  FUN_007ff1f0(param_5);
  local_8 = *param_1;
  uVar2 = make_input_adapter_character_source<>(local_20,&local_8,param_2,param_3,param_4,param_5);
  puVar3 = (undefined4 *)FUN_00806c70(local_38,uVar2);
  cVar1 = FUN_00808800(local_c,*puVar3,puVar3[1],puVar3[2],puVar3[3],puVar3[4],puVar3[5]);
  if (cVar1 == '\0') {
    *param_1 = local_8;
  }
  return cVar1 == '\0';
}

