
void FUN_0068fe40(int param_1)

{
  undefined4 uVar1;
  
  if ((&DAT_02ce9b18)[*(char *)(param_1 + 0x10) * 0x1e0] != '\0') {
    uVar1 = *(undefined4 *)(DAT_00920f04 + *(char *)(param_1 + 0x10) * 4);
    FUN_006a5fd0("AI_BuildingStalled Team %d ptr %d\n",(int)*(char *)(param_1 + 0x10),param_1,uVar1)
    ;
    FUN_006905d0((int)*(char *)(param_1 + 0x10),*(undefined4 *)(param_1 + 0x30));
    FUN_00690920((int)*(char *)(param_1 + 0x10),*(undefined4 *)(param_1 + 0x3c));
    FUN_00690020((int)*(char *)(param_1 + 0x10),0,param_1);
    FUN_00690770(uVar1,param_1);
    std::_Destroy_range<struct_std::_Wrap_alloc<class_std::allocator<unsigned_char>_>_>(param_1);
    *(undefined4 *)(param_1 + 0x30) = 0;
    *(undefined4 *)(param_1 + 0x34) = 0;
    *(undefined4 *)(param_1 + 0x38) = 0;
    *(undefined4 *)(param_1 + 0x40) = 0;
    *(undefined4 *)(param_1 + 0x3c) = 0;
  }
  return;
}

