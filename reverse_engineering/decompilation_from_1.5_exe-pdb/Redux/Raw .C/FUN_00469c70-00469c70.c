
void FUN_00469c70(void)

{
  char cVar1;
  undefined4 uVar2;
  int *piVar3;
  int iVar4;
  undefined1 local_20 [4];
  undefined1 local_1c [4];
  undefined4 local_18;
  int *local_14;
  undefined1 local_10 [4];
  int local_c;
  int local_8;
  
  local_18 = DAT_00917a74;
  FID_conflict_begin(local_10);
  while( true ) {
    uVar2 = FID_conflict_end(local_20);
    cVar1 = FID_conflict_operator__(uVar2);
    if (cVar1 == '\0') break;
    piVar3 = (int *)FUN_00421ec0();
    local_8 = *piVar3;
    iVar4 = (*(code *)**(undefined4 **)(local_8 + 0x18))();
    local_14 = (int *)(iVar4 + 0x1c);
    iVar4 = (*(code *)**(undefined4 **)(local_8 + 0x18))();
    local_c = *(int *)(iVar4 + 0x14);
    if (((((*local_14 == 2) || (*local_14 == 10)) || (*local_14 == 5)) || (local_c == 0x54555252))
       && (((local_c != 0x50524f58 && (local_c != 0x4745495a)) &&
           ((local_c != 0x53464c44 &&
            ((local_c != 0x5350574e &&
             (iVar4 = (**(code **)(*(int *)(local_8 + 0x18) + 0x30))(),
             (*(uint *)(iVar4 + 0x14) & 0x200) == 0)))))))) {
      FUN_00468a70(local_8,1);
    }
    FUN_0046b260(local_1c,0);
  }
  return;
}

