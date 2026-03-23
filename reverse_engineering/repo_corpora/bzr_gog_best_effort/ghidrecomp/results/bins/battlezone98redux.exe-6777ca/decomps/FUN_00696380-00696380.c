
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint FUN_00696380(int param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = *(uint *)(param_1 + param_2 * 4);
  uVar2 = DAT_00931014 / 0x10;
  if ((DAT_00931014 % 0x10 == param_2) &&
     (uVar2 = *(uint *)(uVar1 + 0x60),
     *(int *)(uVar2 + 0x84) <= (int)(DAT_00931014 - *(int *)(*(int *)(uVar1 + 0x60) + 0x88)))) {
    if (*(int *)(uVar1 + 0x9c) == 0) {
      if ((*(int *)(uVar1 + 0x60) != 0) &&
         (uVar2 = uVar1, 0 < *(int *)(*(int *)(uVar1 + 0x60) + 0x408))) {
        _DAT_009310bc = "Schedule\\ai_team.cpp";
        _DAT_009310c0 = 0x520;
        uVar2 = FUN_006a5f50(0x800,"AI_Team_Compute_Mapgrid.");
      }
      if (*(int *)(uVar1 + 4) != 0) {
        uVar2 = FUN_00695ff0(param_1,uVar1);
      }
      *(undefined4 *)(uVar1 + 0x9c) = 1;
    }
    else if (*(int *)(uVar1 + 0x10) == 0) {
      *(uint *)(*(int *)(uVar1 + 0x60) + 0x88) = DAT_00931014;
      FUN_006a7f10();
      uVar2 = FUN_006a7e90();
    }
    else if (*(int *)(uVar1 + 0x98) == 0) {
      if ((*(int *)(uVar1 + 0x60) != 0) && (0 < *(int *)(*(int *)(uVar1 + 0x60) + 0x408))) {
        _DAT_009310bc = "Schedule\\ai_team.cpp";
        _DAT_009310c0 = 0x554;
        FUN_006a5f50(0x800,"AI_Team_Update_Squads.");
      }
      FUN_00696170(param_1,uVar1);
      *(undefined4 *)(uVar1 + 0x98) = 1;
      uVar2 = uVar1;
    }
    else if (*(int *)(*(int *)(uVar1 + 0xa4) + 0x9c) == 0) {
      if ((*(int *)(uVar1 + 0x60) != 0) && (0 < *(int *)(*(int *)(uVar1 + 0x60) + 0x408))) {
        _DAT_009310bc = "Schedule\\ai_team.cpp";
        _DAT_009310c0 = 0x568;
        FUN_006a5f50(0x800,"the_team->scheduler->Allocate_Remaining_Troops.");
      }
      uVar2 = FUN_006a8300();
    }
    else if (*(int *)(*(int *)(uVar1 + 0xa4) + 0x98) == 0) {
      if ((*(int *)(uVar1 + 0x60) != 0) && (0 < *(int *)(*(int *)(uVar1 + 0x60) + 0x408))) {
        _DAT_009310bc = "Schedule\\ai_team.cpp";
        _DAT_009310c0 = 0x57c;
        FUN_006a5f50(0x800,"the_team->scheduler->Send_Groups_On_Missions.");
      }
      std::_Destroy_range<struct_std::_Wrap_alloc<class_std::allocator<unsigned_char>_>_>(uVar1);
      FUN_006a3300(uVar1);
      uVar2 = FUN_006a8420();
    }
    else {
      *(uint *)(*(int *)(uVar1 + 0x60) + 0x88) = DAT_00931014;
      FUN_006a7e90();
      FUN_00694cc0(uVar1);
      uVar2 = FUN_00697290(uVar1);
    }
  }
  return uVar2;
}

