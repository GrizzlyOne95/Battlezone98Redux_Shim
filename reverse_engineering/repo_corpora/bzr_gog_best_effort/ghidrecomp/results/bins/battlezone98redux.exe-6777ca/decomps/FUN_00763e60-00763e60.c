
undefined4 FUN_00763e60(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 local_18 [12];
  undefined4 local_c;
  undefined4 *local_8;
  
  local_8 = (undefined4 *)FUN_007508e0();
  if (local_8 == (undefined4 *)0x0) {
    uVar2 = 0;
  }
  else {
    if (param_4 == 0) {
      local_c = 0;
    }
    else {
      local_c = 2;
    }
    uVar3 = 0;
    uVar2 = local_c;
    puVar1 = (undefined4 *)FUN_0073a970(local_18);
    uVar2 = (**(code **)*local_8)(*puVar1,puVar1[1],param_2,param_3,uVar2,uVar3);
  }
  return uVar2;
}

