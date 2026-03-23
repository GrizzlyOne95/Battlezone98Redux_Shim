
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00624210(void)

{
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_8c;
  char local_84 [40];
  undefined4 local_5c;
  undefined4 local_58;
  code *local_54;
  code *local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  char local_3c [40];
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  DAT_02ceb854 = FUN_0081cb40("multi_message","to_message");
  _DAT_02cebc9c = FUN_0081cb40("multi_message","from_message");
  DAT_02cebc98 = FUN_0081cb40("multi_message","to_allies_message");
  DAT_02ceb84c = FUN_0081cb40("multi_message","to_all_message");
  _DAT_02ceb850 = FUN_0081cb40("multi_message","broadcast_message");
  local_4c = 10;
  local_48 = 200;
  local_44 = 0x1cc;
  local_40 = 0x5a;
  local_14 = DAT_008ec718;
  builtin_strncpy(local_3c,"courier",8);
  local_c = 1;
  local_10 = 0x41f00000;
  DAT_00920168 = FUN_00821190(&local_4c);
  local_94 = 10;
  local_90 = 300;
  local_8c = 0x1cc;
  local_5c = DAT_008ec70c;
  builtin_strncpy(local_84,"courier",8);
  local_58 = 0x10;
  local_54 = FUN_00624780;
  local_50 = FUN_00625070;
  DAT_02a1748c = FUN_008231c0(&local_94);
  DAT_02a17488 = 1;
  FUN_00821340(DAT_00920168,1);
  FUN_0083e885();
  return;
}

