
float10 FUN_005d9020(undefined4 param_1,undefined4 param_2,undefined4 param_3,float param_4)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int *piVar4;
  float10 fVar5;
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  float local_10;
  float local_c;
  undefined4 local_8;
  
  local_c = param_4;
  if (DAT_00918338 != 0) {
    FUN_00422170();
    puVar2 = (undefined4 *)FID_conflict_begin(local_14);
    local_8 = *puVar2;
    while( true ) {
      uVar3 = FID_conflict_end(local_1c);
      cVar1 = FID_conflict_operator__(uVar3);
      if (cVar1 == '\0') break;
      piVar4 = (int *)FUN_00421ec0();
      if (*(int *)(*piVar4 + 0x10) != 0) {
        puVar2 = (undefined4 *)FUN_00421ec0();
        puVar2 = (undefined4 *)std::allocator<char>::allocator<char>((allocator<char> *)*puVar2);
        fVar5 = (float10)FUN_004620b0(param_1,param_2,param_3,*puVar2,puVar2[1],puVar2[2]);
        local_10 = (float)fVar5;
        if (local_10 < local_c) {
          local_c = local_10;
        }
      }
      FUN_0046b260(local_18,0);
    }
  }
  return (float10)local_c;
}

