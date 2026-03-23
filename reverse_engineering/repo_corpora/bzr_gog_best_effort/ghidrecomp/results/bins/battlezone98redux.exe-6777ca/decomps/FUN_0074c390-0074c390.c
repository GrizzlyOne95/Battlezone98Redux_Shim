
void FUN_0074c390(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  undefined *puVar3;
  undefined1 local_10 [8];
  undefined1 local_8 [4];
  
  FUN_00578c20(local_8,param_1);
  uVar2 = FID_conflict_begin(local_10);
  cVar1 = FUN_00420f10(uVar2);
  if (cVar1 != '\0') {
    puVar3 = &DAT_0260b1c8;
    FUN_00422150(&DAT_0260b1c8);
    cVar1 = FUN_0056f780(puVar3);
    if (cVar1 != '\0') {
      uVar2 = param_2;
      FUN_00422150(param_2);
      FUN_0074d3d0(uVar2);
    }
  }
  get(param_1,param_2);
  FUN_006c6040(param_1,param_2);
  return;
}

