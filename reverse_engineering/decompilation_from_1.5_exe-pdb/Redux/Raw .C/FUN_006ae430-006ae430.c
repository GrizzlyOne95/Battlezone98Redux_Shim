
undefined4 FUN_006ae430(undefined4 param_1,undefined4 param_2,uint param_3)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 local_8;
  
  uVar1 = FUN_006ae390(param_2);
  if (uVar1 < param_3) {
    local_8 = FUN_006ae390(param_2);
  }
  else {
    local_8 = param_3;
  }
  uVar2 = FUN_006d8ca0(param_2,local_8);
  uVar2 = FUN_00416430(uVar2,local_8);
  FUN_006ae310(uVar2);
  return param_1;
}

