
void FUN_00679610(int *param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined1 local_14 [4];
  int *local_10;
  undefined1 local_8 [4];
  
  FID_conflict_begin(local_8);
  while( true ) {
    uVar2 = FID_conflict_end(local_14);
    cVar1 = FID_conflict_operator__(uVar2);
    if (cVar1 == '\0') break;
    puVar3 = (undefined4 *)FUN_00421ec0();
    local_10 = (int *)*puVar3;
    (**(code **)(*local_10 + 4))();
    cVar1 = FUN_004c85a0();
    if (cVar1 == '\0') {
      puVar3 = (undefined4 *)FUN_00421ec0(0,0,0);
      (**(code **)(*param_1 + 4))(*puVar3);
    }
    FUN_00421ee0();
  }
  return;
}

