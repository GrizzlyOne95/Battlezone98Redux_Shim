
undefined4 FUN_005d94c0(int param_1)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int *piVar4;
  float10 fVar5;
  undefined1 local_28 [4];
  undefined1 local_24 [4];
  undefined1 local_20 [4];
  float local_1c;
  float local_18;
  undefined4 local_14;
  float local_10;
  float local_c;
  undefined4 local_8;
  
  local_10 = -1.0;
  local_14 = 0;
  if (DAT_00918338 != 0) {
    FUN_00422170();
    puVar2 = (undefined4 *)FID_conflict_begin(local_20);
    local_8 = *puVar2;
    while( true ) {
      uVar3 = FID_conflict_end(local_28);
      cVar1 = FID_conflict_operator__(uVar3);
      if (cVar1 == '\0') break;
      piVar4 = (int *)FUN_00421ec0();
      if (*(int *)(*piVar4 + 0x10) == 0) {
        piVar4 = (int *)FUN_00421ec0();
        if (*(int *)(*piVar4 + 0xc) != 0) {
          piVar4 = (int *)FUN_00421ec0();
          if (*(int *)(*piVar4 + 0xc) != param_1) goto LAB_005d9505;
        }
        puVar2 = (undefined4 *)FUN_00421ec0(param_1,0x7149f2ca);
        puVar2 = (undefined4 *)std::allocator<char>::allocator<char>((allocator<char> *)*puVar2);
        fVar5 = (float10)FUN_005d8f00(*puVar2,puVar2[1],puVar2[2]);
        local_1c = (float)fVar5;
        puVar2 = (undefined4 *)FUN_00421ec0(0x7149f2ca);
        puVar2 = (undefined4 *)std::allocator<char>::allocator<char>((allocator<char> *)*puVar2);
        fVar5 = (float10)FUN_005d9020(*puVar2,puVar2[1],puVar2[2]);
        local_18 = (float)fVar5;
        fVar5 = (float10)FUN_00456080(local_1c,local_18);
        local_c = (float)fVar5;
        if (local_10 < local_c) {
          local_10 = local_c;
          puVar2 = (undefined4 *)FUN_00421ec0();
          local_14 = *puVar2;
        }
      }
LAB_005d9505:
      FUN_0046b260(local_24,0);
    }
  }
  return local_14;
}

