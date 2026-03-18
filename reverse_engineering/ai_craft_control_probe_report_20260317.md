# AI Craft Control Probe

- Process: `battlezone98redux.exe` PID `19772`
- Exe: `C:\Program Files (x86)\Steam\steamapps\common\Battlezone 98 Redux\battlezone98redux.exe`
- Advisory PDB: `C:\Program Files (x86)\GOG Galaxy\Games\Battlezone 98 Redux\battlezone98redux.pdb`
- Image base: `0x00400000`

## Direct Disp Hits

- `0x0041D611` `mov dword ptr [ecx + 0xbc], edx` -> `control.steer?` nearest `class GameObject * __cdecl GetEmptyVehicle(class GameObject *,float &,class GameObject *)` (+/- 81 bytes)
- `0x0041D61A` `mov dword ptr [ecx + 0xc0], eax` -> `control.braccel?` nearest `class GameObject * __cdecl GetEmptyVehicle(class GameObject *,float &,class GameObject *)` (+/- 90 bytes)
- `0x0044DF72` `mov dword ptr [ecx + 0xd8], edx` -> `control.deploy?` nearest `public: virtual void __thiscall Craft::PostSimulate(float)` (+/- 1086 bytes)
- `0x0044DF8C` `mov dword ptr [ecx + 0xd4], eax` -> `control.eject?` nearest `public: virtual void __thiscall Craft::PostSimulate(float)` (+/- 1060 bytes)
- `0x00450E7C` `mov dword ptr [ecx + 0xd4], eax` -> `control.eject?` nearest `public: virtual void __thiscall DayWrecker::Simulate(float)` (+/- 44 bytes)
- `0x00450E9C` `mov dword ptr [ecx + 0xd8], edx` -> `control.deploy?` nearest `public: virtual void __thiscall DayWrecker::Simulate(float)` (+/- 76 bytes)
- `0x00450F8D` `mov dword ptr [ecx + 0xdc], eax` -> `control.abandon?` nearest `public: virtual bool __thiscall DayWrecker::RegCollision(struct _OBJ76 *,struct CLSN_INFO *,struct CLSN_INFO *)` (+/- 67 bytes)
- `0x004515D2` `cmp dword ptr [edx + 0xdc], 0` -> `control.abandon?` nearest `public: virtual class GameObject * __thiscall DayWreckerClass::Build(struct _OBJ76 *)` (+/- 126 bytes)
- `0x004515F0` `mov eax, dword ptr [edx + 0xdc]` -> `control.abandon?` nearest `public: virtual class GameObject * __thiscall DayWreckerClass::Build(struct _OBJ76 *)` (+/- 96 bytes)
- `0x004515FB` `mov ecx, dword ptr [ecx + 0xdc]` -> `control.abandon?` nearest `public: virtual class GameObject * __thiscall DayWreckerClass::Build(struct _OBJ76 *)` (+/- 85 bytes)
- `0x00451612` `mov eax, dword ptr [edx + 0xdc]` -> `control.abandon?` nearest `public: virtual class GameObject * __thiscall DayWreckerClass::Build(struct _OBJ76 *)` (+/- 62 bytes)
- `0x0045161D` `mov ecx, dword ptr [ecx + 0xdc]` -> `control.abandon?` nearest `public: virtual class GameObject * __thiscall DayWreckerClass::Build(struct _OBJ76 *)` (+/- 51 bytes)
- `0x00452064` `cmp ecx, dword ptr [eax + 0xd8]` -> `control.deploy?` nearest `public: virtual bool __thiscall DemoMission::Load(struct _iobuf *)` (+/- 84 bytes)
- `0x0045213F` `cmp eax, dword ptr [edx + 0xd8]` -> `control.deploy?` nearest `public: virtual bool __thiscall DemoMission::Save(struct _iobuf *)` (+/- 17 bytes)
- `0x0045CC91` `mov ecx, dword ptr [eax + 0xd4]` -> `control.eject?` nearest `protected: void __thiscall EditTerrain::CmdBlur(unsigned short *,int,int,int)` (+/- 287 bytes)
- `0x0045CCA5` `mov ecx, dword ptr [eax + 0xd0]` -> `control.jump?` nearest `protected: void __thiscall EditTerrain::CmdBlur(unsigned short *,int,int,int)` (+/- 267 bytes)
- `0x0046CFEA` `mov eax, dword ptr [eax + 0xdc]` -> `control.abandon?` nearest `public: virtual bool __thiscall GameObject::PostLoad(void)` (+/- 90 bytes)
- `0x0046D00A` `mov eax, dword ptr [eax + 0xd8]` -> `control.deploy?` nearest `public: virtual bool __thiscall GameObject::PostLoad(void)` (+/- 122 bytes)
- `0x0046D537` `movss dword ptr [eax + 0xd8], xmm0` -> `control.deploy?` nearest `public: virtual bool __thiscall GameObject::Load(struct _iobuf *)` (+/- 471 bytes)
- `0x0046D54A` `movss dword ptr [ecx + 0xd0], xmm0` -> `control.jump?` nearest `public: virtual bool __thiscall GameObject::Load(struct _iobuf *)` (+/- 490 bytes)
- `0x0046D55D` `movss dword ptr [edx + 0xd4], xmm0` -> `control.eject?` nearest `public: virtual bool __thiscall GameObject::Load(struct _iobuf *)` (+/- 509 bytes)
- `0x0046D603` `movss xmm0, dword ptr [edx + 0xd0]` -> `control.jump?` nearest `public: virtual bool __thiscall GameObject::Load(struct _iobuf *)` (+/- 675 bytes)
- `0x0046D62F` `movss xmm0, dword ptr [ecx + 0xd4]` -> `control.eject?` nearest `public: virtual bool __thiscall GameObject::Load(struct _iobuf *)` (+/- 719 bytes)
- `0x0046D65C` `movss xmm0, dword ptr [eax + 0xd8]` -> `control.deploy?` nearest `public: virtual bool __thiscall GameObject::Load(struct _iobuf *)` (+/- 764 bytes)
- `0x0046D9AE` `movss xmm0, dword ptr [edx + 0xd0]` -> `control.jump?` nearest `public: virtual bool __thiscall GameObject::Save(struct _iobuf *)` (+/- 642 bytes)
- `0x0046DAE0` `movss xmm0, dword ptr [eax + 0xd4]` -> `control.eject?` nearest `public: virtual bool __thiscall GameObject::Save(struct _iobuf *)` (+/- 336 bytes)
- `0x0046DCA5` `mov ecx, dword ptr [edx + 0xd8]` -> `control.deploy?` nearest `public: virtual bool __thiscall GameObject::Save(struct _iobuf *)` (+/- 117 bytes)
- `0x004706E1` `addss xmm0, dword ptr [eax + 0xbc]` -> `control.steer?` nearest `public: virtual void * __thiscall GechProcess::`vector deleting destructor'(unsigned int)` (+/- 49 bytes)
- `0x00470716` `addss xmm0, dword ptr [ecx + 0xc0]` -> `control.braccel?` nearest `protected: virtual bool __thiscall GechProcess::ShouldAttack(enum UnitProcess::State)` (+/- 58 bytes)
- `0x00471266` `movsx eax, byte ptr [edx + 0xcc]` -> `control.strafe?` nearest `public: virtual void __thiscall Geizer::Simulate(float)` (+/- 26 bytes)
- `0x00471275` `movsx edx, byte ptr [ecx + 0xcc]` -> `control.strafe?` nearest `public: virtual void __thiscall Geizer::Simulate(float)` (+/- 11 bytes)
- `0x00471684` `mov ecx, dword ptr [eax + 0xc8]` -> `control.pitch?` nearest `_GeoCache_AddRep` (+/- 20 bytes)
- `0x00471693` `mov dword ptr [eax + 0xc8], ecx` -> `control.pitch?` nearest `_GeoCache_AddRep` (+/- 35 bytes)

## Vehicle-Like Patterns

- load `0x004706C7` `mov ecx, dword ptr [eax + 0xf4]` then `0x00470716` `addss xmm0, dword ptr [ecx + 0xc0]` -> `control.braccel?` nearest `protected: virtual bool __thiscall GechProcess::ShouldAttack(enum UnitProcess::State)` (+/- 58 bytes)
- load `0x004706D3` `mov eax, dword ptr [edx + 0xf4]` then `0x004706E1` `addss xmm0, dword ptr [eax + 0xbc]` -> `control.steer?` nearest `public: virtual void * __thiscall GechProcess::`vector deleting destructor'(unsigned int)` (+/- 49 bytes)
- load `0x00470708` `mov ecx, dword ptr [eax + 0xf4]` then `0x00470716` `addss xmm0, dword ptr [ecx + 0xc0]` -> `control.braccel?` nearest `protected: virtual bool __thiscall GechProcess::ShouldAttack(enum UnitProcess::State)` (+/- 58 bytes)

## Windows

### `0x00470716`

```text
   0x004706E6: add    byte ptr [eax], al
   0x004706E8: add    bl, dh
   0x004706EA: mulps  xmm0, xmmword ptr [0x8a2584]
   0x004706F1: movss  dword ptr [ebp - 0x28], xmm0
   0x004706F6: mov    ecx, dword ptr [ebp - 0x84]
   0x004706FC: mov    edx, dword ptr [ecx + 0xf4]
   0x00470702: mov    eax, dword ptr [ebp - 0x84]
   0x00470708: mov    ecx, dword ptr [eax + 0xf4]
   0x0047070E: movss  xmm0, dword ptr [edx + 0xb4]
>> 0x00470716: addss  xmm0, dword ptr [ecx + 0xc0]
   0x0047071E: mulss  xmm0, dword ptr [0x8a2584]
   0x00470726: movss  dword ptr [ebp - 0x24], xmm0
   0x0047072B: mov    edx, dword ptr [ebp - 0x84]
   0x00470731: mov    eax, dword ptr [edx + 0xf4]
   0x00470737: movss  xmm0, dword ptr [eax + 0xb8]
   0x0047073F: movss  dword ptr [ebp - 0x20], xmm0
```

### `0x004706E1`

```text
   0x004706B1: clc    
   0x004706B2: add    byte ptr [eax], al
   0x004706B4: add    byte ptr [ebx + 0x5f891], cl
   0x004706BA: add    byte ptr [ecx - 0xcb6b], cl
   0x004706C0: dec    dword ptr [ebx - 0x837b]
   0x004706C6: dec    dword ptr [ebx + 0xf488]
   0x004706CC: add    byte ptr [ebx - 0x836b], cl
   0x004706D2: dec    dword ptr [ebx + 0xf482]
   0x004706D8: add    bl, dh
   0x004706DA: movups xmm0, xmmword ptr [ecx + 0xb0]
>> 0x004706E1: addss  xmm0, dword ptr [eax + 0xbc]
   0x004706E9: mulss  xmm0, dword ptr [0x8a2584]
   0x004706F1: movss  dword ptr [ebp - 0x28], xmm0
   0x004706F6: mov    ecx, dword ptr [ebp - 0x84]
   0x004706FC: mov    edx, dword ptr [ecx + 0xf4]
   0x00470702: mov    eax, dword ptr [ebp - 0x84]
   0x00470708: mov    ecx, dword ptr [eax + 0xf4]
```

### `0x0046CFEA`

```text
   0x0046CFBA: int3   
   0x0046CFBB: int3   
   0x0046CFBC: int3   
   0x0046CFBD: int3   
   0x0046CFBE: int3   
   0x0046CFBF: int3   
   0x0046CFC0: push   ebp
   0x0046CFC1: mov    ebp, esp
   0x0046CFC3: push   ecx
   0x0046CFC4: mov    dword ptr [ebp - 4], ecx
   0x0046CFC7: mov    eax, dword ptr [ebp - 4]
   0x0046CFCA: mov    byte ptr [eax + 0x61], 1
   0x0046CFCE: mov    esp, ebp
   0x0046CFD0: pop    ebp
   0x0046CFD1: ret    
   0x0046CFD2: int3   
   0x0046CFD3: int3   
   0x0046CFD4: int3   
   0x0046CFD5: int3   
   0x0046CFD6: int3   
   0x0046CFD7: int3   
   0x0046CFD8: int3   
   0x0046CFD9: int3   
   0x0046CFDA: int3   
   0x0046CFDB: int3   
   0x0046CFDC: int3   
   0x0046CFDD: int3   
   0x0046CFDE: int3   
   0x0046CFDF: int3   
   0x0046CFE0: push   ebp
   0x0046CFE1: mov    ebp, esp
   0x0046CFE3: push   ecx
   0x0046CFE4: mov    dword ptr [ebp - 4], ecx
   0x0046CFE7: mov    eax, dword ptr [ebp - 4]
>> 0x0046CFEA: mov    eax, dword ptr [eax + 0xdc]
   0x0046CFF0: mov    esp, ebp
   0x0046CFF2: pop    ebp
   0x0046CFF3: ret    
   0x0046CFF4: int3   
   0x0046CFF5: int3   
   0x0046CFF6: int3   
   0x0046CFF7: int3   
   0x0046CFF8: int3   
   0x0046CFF9: int3   
   0x0046CFFA: int3   
   0x0046CFFB: int3   
   0x0046CFFC: int3   
   0x0046CFFD: int3   
   0x0046CFFE: int3   
   0x0046CFFF: int3   
   0x0046D000: push   ebp
   0x0046D001: mov    ebp, esp
   0x0046D003: push   ecx
   0x0046D004: mov    dword ptr [ebp - 4], ecx
   0x0046D007: mov    eax, dword ptr [ebp - 4]
   0x0046D00A: mov    eax, dword ptr [eax + 0xd8]
   0x0046D010: mov    esp, ebp
   0x0046D012: pop    ebp
   0x0046D013: ret    
   0x0046D014: int3   
   0x0046D015: int3   
   0x0046D016: int3   
   0x0046D017: int3   
   0x0046D018: int3   
   0x0046D019: int3   
```

### `0x0046D00A`

```text
   0x0046CFDA: int3   
   0x0046CFDB: int3   
   0x0046CFDC: int3   
   0x0046CFDD: int3   
   0x0046CFDE: int3   
   0x0046CFDF: int3   
   0x0046CFE0: push   ebp
   0x0046CFE1: mov    ebp, esp
   0x0046CFE3: push   ecx
   0x0046CFE4: mov    dword ptr [ebp - 4], ecx
   0x0046CFE7: mov    eax, dword ptr [ebp - 4]
   0x0046CFEA: mov    eax, dword ptr [eax + 0xdc]
   0x0046CFF0: mov    esp, ebp
   0x0046CFF2: pop    ebp
   0x0046CFF3: ret    
   0x0046CFF4: int3   
   0x0046CFF5: int3   
   0x0046CFF6: int3   
   0x0046CFF7: int3   
   0x0046CFF8: int3   
   0x0046CFF9: int3   
   0x0046CFFA: int3   
   0x0046CFFB: int3   
   0x0046CFFC: int3   
   0x0046CFFD: int3   
   0x0046CFFE: int3   
   0x0046CFFF: int3   
   0x0046D000: push   ebp
   0x0046D001: mov    ebp, esp
   0x0046D003: push   ecx
   0x0046D004: mov    dword ptr [ebp - 4], ecx
   0x0046D007: mov    eax, dword ptr [ebp - 4]
>> 0x0046D00A: mov    eax, dword ptr [eax + 0xd8]
   0x0046D010: mov    esp, ebp
   0x0046D012: pop    ebp
   0x0046D013: ret    
   0x0046D014: int3   
   0x0046D015: int3   
   0x0046D016: int3   
   0x0046D017: int3   
   0x0046D018: int3   
   0x0046D019: int3   
   0x0046D01A: int3   
   0x0046D01B: int3   
   0x0046D01C: int3   
   0x0046D01D: int3   
   0x0046D01E: int3   
   0x0046D01F: int3   
   0x0046D020: push   ebp
   0x0046D021: mov    ebp, esp
   0x0046D023: push   ecx
   0x0046D024: mov    dword ptr [ebp - 4], ecx
   0x0046D027: mov    eax, dword ptr [ebp - 4]
   0x0046D02A: add    eax, 0xf0
   0x0046D02F: mov    esp, ebp
   0x0046D031: pop    ebp
   0x0046D032: ret    
   0x0046D033: int3   
   0x0046D034: int3   
   0x0046D035: int3   
   0x0046D036: int3   
   0x0046D037: int3   
   0x0046D038: int3   
   0x0046D039: int3   
```

### `0x0046D537`

```text
   0x0046D507: mov    ecx, dword ptr [ebp - 4]
   0x0046D50A: call   0x5be1b0
   0x0046D50F: mov    eax, dword ptr [ebp - 4]
   0x0046D512: mov    dword ptr [eax], 0x875690
   0x0046D518: mov    ecx, dword ptr [ebp - 4]
   0x0046D51B: mov    dword ptr [ecx + 0xc], 0x414e4348
   0x0046D522: mov    edx, dword ptr [ebp - 4]
   0x0046D525: mov    dword ptr [edx + 0x10], 0x8756c4
   0x0046D52C: mov    eax, dword ptr [ebp - 4]
   0x0046D52F: movss  xmm0, dword ptr [0x8a28ac]
>> 0x0046D537: movss  dword ptr [eax + 0xd8], xmm0
   0x0046D53F: mov    ecx, dword ptr [ebp - 4]
   0x0046D542: movss  xmm0, dword ptr [0x8a28ac]
   0x0046D54A: movss  dword ptr [ecx + 0xd0], xmm0
   0x0046D552: mov    edx, dword ptr [ebp - 4]
   0x0046D555: movss  xmm0, dword ptr [0x8a285c]
   0x0046D55D: movss  dword ptr [edx + 0xd4], xmm0
```

### `0x0046D54A`

```text
   0x0046D51A: cld    
   0x0046D51B: mov    dword ptr [ecx + 0xc], 0x414e4348
   0x0046D522: mov    edx, dword ptr [ebp - 4]
   0x0046D525: mov    dword ptr [edx + 0x10], 0x8756c4
   0x0046D52C: mov    eax, dword ptr [ebp - 4]
   0x0046D52F: movss  xmm0, dword ptr [0x8a28ac]
   0x0046D537: movss  dword ptr [eax + 0xd8], xmm0
   0x0046D53F: mov    ecx, dword ptr [ebp - 4]
   0x0046D542: movss  xmm0, dword ptr [0x8a28ac]
>> 0x0046D54A: movss  dword ptr [ecx + 0xd0], xmm0
   0x0046D552: mov    edx, dword ptr [ebp - 4]
   0x0046D555: movss  xmm0, dword ptr [0x8a285c]
   0x0046D55D: movss  dword ptr [edx + 0xd4], xmm0
   0x0046D565: mov    eax, dword ptr [ebp - 4]
   0x0046D568: mov    esp, ebp
   0x0046D56A: pop    ebp
   0x0046D56B: ret    
   0x0046D56C: int3   
   0x0046D56D: int3   
   0x0046D56E: int3   
   0x0046D56F: int3   
   0x0046D570: push   ebp
   0x0046D571: mov    ebp, esp
   0x0046D573: push   ecx
   0x0046D574: mov    dword ptr [ebp - 4], ecx
   0x0046D577: mov    ecx, dword ptr [ebp - 4]
```

### `0x0046D55D`

```text
   0x0046D52D: inc    ebp
   0x0046D52E: cld    
   0x0046D52F: movss  xmm0, dword ptr [0x8a28ac]
   0x0046D537: movss  dword ptr [eax + 0xd8], xmm0
   0x0046D53F: mov    ecx, dword ptr [ebp - 4]
   0x0046D542: movss  xmm0, dword ptr [0x8a28ac]
   0x0046D54A: movss  dword ptr [ecx + 0xd0], xmm0
   0x0046D552: mov    edx, dword ptr [ebp - 4]
   0x0046D555: movss  xmm0, dword ptr [0x8a285c]
>> 0x0046D55D: movss  dword ptr [edx + 0xd4], xmm0
   0x0046D565: mov    eax, dword ptr [ebp - 4]
   0x0046D568: mov    esp, ebp
   0x0046D56A: pop    ebp
   0x0046D56B: ret    
   0x0046D56C: int3   
   0x0046D56D: int3   
   0x0046D56E: int3   
   0x0046D56F: int3   
   0x0046D570: push   ebp
   0x0046D571: mov    ebp, esp
   0x0046D573: push   ecx
   0x0046D574: mov    dword ptr [ebp - 4], ecx
   0x0046D577: mov    ecx, dword ptr [ebp - 4]
   0x0046D57A: call   0x46d6b0
   0x0046D57F: mov    eax, dword ptr [ebp + 8]
   0x0046D582: and    eax, 1
   0x0046D585: je     0x46d594
   0x0046D587: mov    ecx, dword ptr [ebp - 4]
   0x0046D58A: push   ecx
```

### `0x0046D603`

```text
   0x0046D5D3: push   edx
   0x0046D5D4: mov    ecx, dword ptr [ebp - 0x10]
   0x0046D5D7: call   0x5be350
   0x0046D5DC: mov    dword ptr [ebp - 4], 0
   0x0046D5E3: mov    eax, dword ptr [ebp - 0x10]
   0x0046D5E6: mov    dword ptr [eax], 0x875690
   0x0046D5EC: mov    ecx, dword ptr [ebp - 0x10]
   0x0046D5EF: add    ecx, 0x20
   0x0046D5F2: push   ecx
   0x0046D5F3: lea    ecx, [ebp - 0x14]
   0x0046D5F6: call   0x589430
   0x0046D5FB: mov    byte ptr [ebp - 4], 1
   0x0046D5FF: mov    edx, dword ptr [ebp + 8]
   0x0046D602: push   ecx
>> 0x0046D603: movss  xmm0, dword ptr [edx + 0xd0]
   0x0046D60B: movss  dword ptr [esp], xmm0
   0x0046D610: mov    eax, dword ptr [ebp - 0x10]
   0x0046D613: add    eax, 0xd0
   0x0046D618: push   eax
   0x0046D619: push   0x27bac631
   0x0046D61E: push   0xec437ec4
   0x0046D623: lea    ecx, [ebp - 0x14]
   0x0046D626: call   0x589800
   0x0046D62B: mov    ecx, dword ptr [ebp + 8]
   0x0046D62E: push   ecx
```

### `0x0046D62F`

```text
   0x0046D5FF: mov    edx, dword ptr [ebp + 8]
   0x0046D602: push   ecx
   0x0046D603: movss  xmm0, dword ptr [edx + 0xd0]
   0x0046D60B: movss  dword ptr [esp], xmm0
   0x0046D610: mov    eax, dword ptr [ebp - 0x10]
   0x0046D613: add    eax, 0xd0
   0x0046D618: push   eax
   0x0046D619: push   0x27bac631
   0x0046D61E: push   0xec437ec4
   0x0046D623: lea    ecx, [ebp - 0x14]
   0x0046D626: call   0x589800
   0x0046D62B: mov    ecx, dword ptr [ebp + 8]
   0x0046D62E: push   ecx
>> 0x0046D62F: movss  xmm0, dword ptr [ecx + 0xd4]
   0x0046D637: movss  dword ptr [esp], xmm0
   0x0046D63C: mov    edx, dword ptr [ebp - 0x10]
   0x0046D63F: add    edx, 0xd4
   0x0046D645: push   edx
   0x0046D646: push   0xc0783809
   0x0046D64B: push   0xec437ec4
   0x0046D650: lea    ecx, [ebp - 0x14]
   0x0046D653: call   0x589800
   0x0046D658: mov    eax, dword ptr [ebp + 8]
   0x0046D65B: push   ecx
```

### `0x0046D65C`

```text
   0x0046D62C: dec    ebp
   0x0046D62D: or     byte ptr [ecx - 0xd], dl
   0x0046D630: movups xmm0, xmmword ptr [ecx + 0xd4]
   0x0046D637: movss  dword ptr [esp], xmm0
   0x0046D63C: mov    edx, dword ptr [ebp - 0x10]
   0x0046D63F: add    edx, 0xd4
   0x0046D645: push   edx
   0x0046D646: push   0xc0783809
   0x0046D64B: push   0xec437ec4
   0x0046D650: lea    ecx, [ebp - 0x14]
   0x0046D653: call   0x589800
   0x0046D658: mov    eax, dword ptr [ebp + 8]
   0x0046D65B: push   ecx
>> 0x0046D65C: movss  xmm0, dword ptr [eax + 0xd8]
   0x0046D664: movss  dword ptr [esp], xmm0
   0x0046D669: mov    ecx, dword ptr [ebp - 0x10]
   0x0046D66C: add    ecx, 0xd8
   0x0046D672: push   ecx
   0x0046D673: push   0x10d7bd55
   0x0046D678: push   0xec437ec4
   0x0046D67D: lea    ecx, [ebp - 0x14]
   0x0046D680: call   0x589800
   0x0046D685: mov    byte ptr [ebp - 4], 0
   0x0046D689: lea    ecx, [ebp - 0x14]
```

### `0x0046D9AE`

```text
   0x0046D97E: mov    ecx, dword ptr [ebp - 0x84]
   0x0046D984: call   0x45c490
   0x0046D989: mov    dword ptr [ebp - 0x80], eax
   0x0046D98C: mov    edx, dword ptr [ebp - 0x80]
   0x0046D98F: add    edx, 0x18
   0x0046D992: mov    dword ptr [ebp - 0x88], edx
   0x0046D998: mov    eax, dword ptr [ebp - 0x80]
   0x0046D99B: movss  xmm0, dword ptr [eax + 8]
   0x0046D9A0: movss  dword ptr [ebp - 0x90], xmm0
   0x0046D9A8: mov    ecx, dword ptr [ebp - 0x78]
   0x0046D9AB: mov    edx, dword ptr [ecx + 0xc]
>> 0x0046D9AE: movss  xmm0, dword ptr [edx + 0xd0]
   0x0046D9B6: mulss  xmm0, dword ptr [ebp + 8]
   0x0046D9BB: movss  dword ptr [ebp - 0x94], xmm0
   0x0046D9C3: movss  xmm0, dword ptr [ebp - 0x90]
   0x0046D9CB: comiss xmm0, dword ptr [ebp - 0x94]
   0x0046D9D2: jbe    0x46da4a
   0x0046D9D4: mov    eax, dword ptr [ebp - 0x88]
   0x0046D9DA: sub    esp, 0xc
```

### `0x0046DAE0`

```text
   0x0046DAB0: and    al, 0x89
   0x0046DAB2: inc    ebp
   0x0046DAB3: test   byte ptr [ebx - 0x137c7bb3], cl
   0x0046DAB9: or     al, 0x8b
   0x0046DABB: aam    0x8b
   0x0046DABD: add    dword ptr [ecx + 0x4418b02], ecx
   0x0046DAC3: mov    dword ptr [edx + 4], eax
   0x0046DAC6: mov    ecx, dword ptr [ecx + 8]
   0x0046DAC9: mov    dword ptr [edx + 8], ecx
   0x0046DACC: call   0x45c420
   0x0046DAD1: add    esp, 0xc
   0x0046DAD4: fstp   dword ptr [ebp - 0x98]
   0x0046DADA: mov    edx, dword ptr [ebp - 0x78]
   0x0046DADD: mov    eax, dword ptr [edx + 0xc]
>> 0x0046DAE0: movss  xmm0, dword ptr [eax + 0xd4]
   0x0046DAE8: mulss  xmm0, dword ptr [ebp + 8]
   0x0046DAED: movss  dword ptr [ebp - 0x8c], xmm0
   0x0046DAF5: movss  xmm0, dword ptr [ebp - 0x98]
   0x0046DAFD: comiss xmm0, dword ptr [ebp - 0x8c]
   0x0046DB04: jbe    0x46db76
   0x0046DB06: mov    ecx, dword ptr [ebp - 0x7c]
   0x0046DB09: sub    esp, 0xc
   0x0046DB0C: mov    edx, esp
   0x0046DB0E: mov    eax, dword ptr [ecx]
```

### `0x0046DCA5`

```text
   0x0046DC75: add    byte ptr [eax], al
   0x0046DC77: add    byte ptr [ebx - 0xc76b], cl
   0x0046DC7D: dec    dword ptr [ebx + 0x488b1442]
   0x0046DC83: adc    al, 0x81
   0x0046DC85: loope  0x46dc86
   0x0046DC87: std    
```
