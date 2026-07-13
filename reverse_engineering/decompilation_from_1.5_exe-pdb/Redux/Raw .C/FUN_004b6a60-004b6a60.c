
void FUN_004b6a60(int param_1,int param_2)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined1 local_34 [4];
  undefined1 local_30 [4];
  undefined1 local_2c [4];
  undefined1 local_28 [4];
  undefined1 local_24 [4];
  undefined4 local_20;
  int local_1c;
  int local_18;
  int *local_14;
  int *local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  local_c = *(undefined4 *)(&DAT_0260d79c + param_1 * 4);
  local_14 = operator_new(8);
  *local_14 = param_2;
  local_14[1] = local_18;
  local_10 = local_14;
  FUN_00430590();
  local_1c = -0x8000;
  puVar2 = (undefined4 *)FUN_0042d8c0(local_24);
  local_8 = *puVar2;
  do {
    uVar3 = FID_conflict_begin(local_2c);
    cVar1 = FUN_00420f10(uVar3);
    if (cVar1 == '\0') {
LAB_004b6b1e:
      uVar3 = FID_conflict_begin(local_34);
      cVar1 = FUN_004221b0(uVar3);
      if (cVar1 != '\0') {
        FUN_00438be0(&local_10);
      }
      return;
    }
    if (local_1c <= param_2) {
      puVar2 = (undefined4 *)FUN_0042de50();
      if (param_2 < *(int *)*puVar2) {
        local_20 = local_8;
        FUN_004613b0(local_30,local_8,&local_10);
        goto LAB_004b6b1e;
      }
    }
    FUN_00438c10(local_28,0);
  } while( true );
}

