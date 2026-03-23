
void FUN_00584d30(undefined4 param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined1 local_14 [4];
  undefined1 local_10 [4];
  int *local_c;
  undefined1 local_8 [4];
  
  FUN_0042d8c0(local_8);
  while( true ) {
    uVar2 = FID_conflict_begin(local_10);
    cVar1 = FUN_00420f10(uVar2);
    if (cVar1 == '\0') break;
    FUN_00438c10(local_14,0);
    puVar3 = (undefined4 *)FUN_0042de50();
    local_c = (int *)*puVar3;
    (**(code **)(*local_c + 0x18))(param_1);
  }
  return;
}

