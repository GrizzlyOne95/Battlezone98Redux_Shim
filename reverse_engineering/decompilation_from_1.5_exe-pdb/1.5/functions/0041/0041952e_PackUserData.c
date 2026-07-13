/*
 * Entry: 0041952e
 * Name: PackUserData
 * Namespace: Global
 * Signature: bool PackUserData(char * * param_1, char * param_2, lua_State * param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

bool __cdecl PackUserData(char **param_1,char *param_2,lua_State *param_3,int param_4)

{
  undefined2 uVar1;
  undefined4 *puVar2;
  MAT_3D MVar3;
  int iVar4;
  char *pcVar5;
  MAT_3D *pMVar6;
  REDUCED_MAT *pRVar7;
  VECTOR_3D *pVVar8;
  lua_State *in_ECX;
  int *unaff_EBX;
  undefined4 unaff_EDI;
  float *pfVar9;
  float fStack_70;
  undefined1 in_stack_ffffff94 [40];
  undefined4 uVar10;
  lua_State *plVar11;
  undefined4 uVar12;
  uint uVar13;
  REDUCED_MAT local_28 [2];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  iVar4 = lua_getmetatable(in_ECX,(int)param_2);
  if (iVar4 != 0) {
    lua_getfield(in_ECX,-1,"__type");
    uVar13 = 0x811c9dc5;
    pcVar5 = luaL_checklstring(in_ECX,-1,(uint *)0x0);
    uVar13 = Hash(pcVar5,uVar13);
    uVar10 = 0x419587;
    plVar11 = in_ECX;
    lua_settop(in_ECX,-3);
    if (uVar13 == 0xe3f3088) {
      if (param_1 <= (char **)(*unaff_EBX + 0xcU)) {
        return false;
      }
      pcVar5 = (char *)(*unaff_EBX + -1);
      *pcVar5 = *pcVar5 + '\x01';
      pVVar8 = GetVector(in_ECX,(int)param_2);
      pfVar9 = (float *)*unaff_EBX;
      *pfVar9 = pVVar8->x;
      pfVar9[1] = pVVar8->y;
      pfVar9[2] = pVVar8->z;
      *unaff_EBX = *unaff_EBX + 0xc;
    }
    else if (uVar13 == 0x247e1851) {
      if (param_1 <= (char **)(*unaff_EBX + 0xfU)) {
        return false;
      }
      pcVar5 = (char *)(*unaff_EBX + -1);
      *pcVar5 = *pcVar5 + '\x02';
      uVar12 = 0x4195b1;
      pMVar6 = GetMatrix(in_ECX,(int)param_2);
      pfVar9 = &fStack_70;
      for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
        *pfVar9 = pMVar6->right_x;
        pMVar6 = (MAT_3D *)&pMVar6->right_y;
        pfVar9 = pfVar9 + 1;
      }
      MVar3.posit_x._0_4_ = uVar10;
      MVar3.right_x = (float)in_stack_ffffff94._0_4_;
      MVar3.right_y = (float)in_stack_ffffff94._4_4_;
      MVar3.right_z = (float)in_stack_ffffff94._8_4_;
      MVar3.up_x = (float)in_stack_ffffff94._12_4_;
      MVar3.up_y = (float)in_stack_ffffff94._16_4_;
      MVar3.up_z = (float)in_stack_ffffff94._20_4_;
      MVar3.front_x = (float)in_stack_ffffff94._24_4_;
      MVar3.front_y = (float)in_stack_ffffff94._28_4_;
      MVar3.front_z = (float)in_stack_ffffff94._32_4_;
      MVar3._36_4_ = in_stack_ffffff94._36_4_;
      MVar3.posit_x._4_4_ = plVar11;
      MVar3.posit_y._0_4_ = uVar12;
      MVar3.posit_y._4_4_ = in_ECX;
      MVar3.posit_z._0_4_ = param_2;
      MVar3.posit_z._4_4_ = unaff_EDI;
      pRVar7 = NetUtil_ReduceMatrix(local_28,MVar3);
      uVar10 = *(undefined4 *)(pRVar7->buf + 4);
      uVar12 = *(undefined4 *)(pRVar7->buf + 8);
      uVar1 = *(undefined2 *)(pRVar7->buf + 0xc);
      puVar2 = (undefined4 *)*unaff_EBX;
      *puVar2 = *(undefined4 *)pRVar7->buf;
      puVar2[1] = uVar10;
      puVar2[2] = uVar12;
      *(undefined2 *)(puVar2 + 3) = uVar1;
      *unaff_EBX = *unaff_EBX + 0xe;
    }
  }
  return true;
}
