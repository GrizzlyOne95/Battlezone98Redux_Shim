
void FUN_0074c0c0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  undefined4 uVar2;
  undefined *puVar3;
  undefined4 uVar4;
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
      uVar4 = param_3;
      FUN_00422150(param_2,param_3);
      FUN_006ca810(uVar2);
      FID_conflict_operator_(uVar4);
    }
  }
  get(param_2,param_3);
  FUN_006c4c50(param_2,param_3);
  return;
}

