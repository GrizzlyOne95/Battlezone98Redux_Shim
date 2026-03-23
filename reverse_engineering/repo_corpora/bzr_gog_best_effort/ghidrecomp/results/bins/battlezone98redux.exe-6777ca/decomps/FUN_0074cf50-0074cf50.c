
void FUN_0074cf50(undefined4 param_1,undefined4 param_2,char param_3)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 *puVar4;
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  undefined1 local_10 [4];
  undefined1 local_c [8];
  
  FUN_0073eeb0(param_1,param_2,0,param_3,0,0);
  FUN_00578c20(local_c,param_1);
  uVar2 = FID_conflict_begin(local_14);
  cVar1 = FUN_004221b0(uVar2);
  if (cVar1 == '\0') {
    puVar4 = local_10;
    uVar2 = param_2;
    FUN_00422150(puVar4,param_2);
    FUN_00578c20(puVar4,uVar2);
    iVar3 = get();
    if (*(int *)(iVar3 + 0xc3c) != 0) {
      if (param_3 == '\0') {
        puVar4 = local_18;
        FUN_00422150(puVar4);
        uVar2 = FID_conflict_begin(puVar4);
        cVar1 = FUN_00420f10(uVar2);
        if (cVar1 != '\0') {
          iVar3 = FUN_00422150();
          iVar3 = iVar3 + 0x10;
          get(param_1,iVar3);
          FUN_0075d090(param_1,iVar3);
        }
      }
      else {
        get(param_1,param_2);
        FUN_0075d590(param_1,param_2);
      }
    }
  }
  return;
}

