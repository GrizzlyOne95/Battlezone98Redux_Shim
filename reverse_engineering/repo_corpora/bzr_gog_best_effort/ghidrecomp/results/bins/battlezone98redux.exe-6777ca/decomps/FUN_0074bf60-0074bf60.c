
void FUN_0074bf60(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  undefined *puVar4;
  undefined4 uVar5;
  undefined1 local_18 [4];
  undefined1 local_14 [8];
  undefined1 local_c [4];
  undefined1 local_8 [4];
  
  FUN_00578c20(local_8,param_1);
  uVar2 = FID_conflict_begin(local_14);
  cVar1 = FUN_00420f10(uVar2);
  if (cVar1 != '\0') {
    puVar4 = &DAT_0260b1c8;
    puVar3 = local_c;
    FUN_00422150(puVar3,&DAT_0260b1c8);
    FUN_00578c20(puVar3,puVar4);
    puVar3 = local_18;
    FUN_00422150(puVar3);
    uVar2 = FID_conflict_begin(puVar3);
    cVar1 = FUN_00420f10(uVar2);
    if (cVar1 != '\0') {
      uVar2 = param_2;
      uVar5 = param_3;
      FUN_00422150(param_2,param_3);
      FUN_006ca810(uVar2);
      FID_conflict_operator_(uVar5);
    }
  }
  get(param_2,param_3);
  FUN_006c4f70(param_2,param_3);
  return;
}

