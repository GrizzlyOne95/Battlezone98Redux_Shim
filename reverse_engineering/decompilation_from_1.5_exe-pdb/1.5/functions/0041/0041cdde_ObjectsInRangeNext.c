/*
 * Entry: 0041cdde
 * Name: ObjectsInRangeNext
 * Namespace: Global
 * Signature: int ObjectsInRangeNext(lua_State * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl ObjectsInRangeNext(lua_State *param_1)

{
  int *piVar1;
  GameObject *this;
  float fVar2;
  float fVar3;
  VECTOR_3D *pVVar4;
  GameObject **ppGVar5;
  int iVar6;
  float *pfVar7;
  double dVar8;
  uint local_8;
  
  dVar8 = lua_tonumber(param_1,-0x2713);
  pVVar4 = RequireVector(param_1,-0x2714);
  local_8 = lua_tointeger(param_1,-0x2715);
  do {
    if ((uint)((int)GameObject::objectList->_Mylast - (int)GameObject::objectList->_Myfirst >> 2) <=
        local_8) {
      return 0;
    }
    ppGVar5 = std::vector<GameObject_*,std::allocator<GameObject_*>_>::at
                        (GameObject::objectList,local_8);
    this = *ppGVar5;
    local_8 = local_8 + 1;
    piVar1 = &this->_padding_;
    iVar6 = (**(code **)(*piVar1 + 0x30))();
  } while (((*(uint *)(iVar6 + 0x14) & 0x200) != 0) ||
          (pfVar7 = (float *)(**(code **)(*piVar1 + 0xc))(), fVar2 = pVVar4->x - *pfVar7,
          fVar3 = pVVar4->z - pfVar7[2],
          (float)((float10)dVar8 * (float10)dVar8) < fVar3 * fVar3 + fVar2 * fVar2));
  lua_pushinteger(param_1,local_8);
  lua_replace(param_1,-0x2715);
  iVar6 = GameObject::GetHandle(this);
  PushHandle(param_1,iVar6);
  return 1;
}
