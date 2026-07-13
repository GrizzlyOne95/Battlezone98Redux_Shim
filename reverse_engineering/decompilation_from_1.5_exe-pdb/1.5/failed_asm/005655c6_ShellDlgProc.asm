; Entry: 005655c6
; Name: ShellDlgProc
; Signature: int ShellDlgProc(HWND__ * param_1, uint param_2, uint param_3, long param_4)
; Stop: 0x00568ffe
; Reason: Exception while decompiling 005655c6: process: timeout 
; Command: C:\Program Files\LLVM\bin\llvm-objdump.EXE -d --no-show-raw-insn --start-address=0x005655c6 --stop-address=0x00568ffe C:\Users\istuart\Downloads\bzone15227\extracted\bzone.exe


C:\Users\istuart\Downloads\bzone15227\extracted\bzone.exe:	file format coff-i386

Disassembly of section .text:

00401000 <.text>:
  5655c6:      	pushl	%ebp
  5655c7:      	leal	-0x73c(%esp), %ebp
  5655ce:      	subl	$0x7b8, %esp            # imm = 0x7B8
  5655d4:      	movl	0x64d8e0, %eax
  5655d9:      	xorl	%ebp, %eax
  5655db:      	movl	%eax, 0x738(%ebp)
  5655e1:      	movl	0x748(%ebp), %ecx
  5655e7:      	pushl	%ebx
  5655e8:      	movl	0x750(%ebp), %ebx
  5655ee:      	pushl	%esi
  5655ef:      	movl	0x744(%ebp), %esi
  5655f5:      	movl	$0x113, %eax            # imm = 0x113
  5655fa:      	pushl	%edi
  5655fb:      	movl	0x74c(%ebp), %edi
  565601:      	movl	%esi, -0x2c(%ebp)
  565604:      	cmpl	%eax, %ecx
  565606:      	ja	0x56787c <.text+0x16687c>
  56560c:      	je	0x567663 <.text+0x166663>
  565612:      	cmpl	$0x2b, %ecx
  565615:      	ja	0x566721 <.text+0x165721>
  56561b:      	je	0x565bb7 <.text+0x164bb7>
  565621:      	decl	%ecx
  565622:      	decl	%ecx
  565623:      	je	0x565820 <.text+0x164820>
  565629:      	subl	$0xd, %ecx
  56562c:      	je	0x565657 <.text+0x164657>
  56562e:      	subl	$0x5, %ecx
  565631:      	je	0x567785 <.text+0x166785>
  565637:      	subl	$0xc, %ecx
  56563a:      	jne	0x567650 <.text+0x166650>
  565640:      	pushl	%ecx
  565641:      	calll	0x571075 <.text+0x170075>
  565646:      	popl	%ecx
  565647:      	pushl	$0x1
  565649:      	pushl	$0x0
  56564b:      	pushl	%esi
  56564c:      	calll	*0x5ce564
  565652:      	jmp	0x567785 <.text+0x166785>
  565657:      	leal	-0x24(%ebp), %eax
  56565a:      	pushl	%eax
  56565b:      	pushl	%esi
  56565c:      	calll	*0x5ce5e4
  565662:      	movl	0xc70354, %ecx
  565668:      	movl	%eax, %edi
  56566a:      	pushl	%edi
  56566b:      	calll	0x56f834 <.text+0x16e834>
  565670:      	movl	0xc70350, %ecx
  565676:      	pushl	%edi
  565677:      	calll	0x571711 <.text+0x170711>
  56567c:      	movl	0xc7034c, %ecx
  565682:      	pushl	%edi
  565683:      	calll	0x571711 <.text+0x170711>
  565688:      	movl	0xc70348, %ecx
  56568e:      	pushl	%edi
  56568f:      	calll	0x571711 <.text+0x170711>
  565694:      	movl	0xc70344, %ecx
  56569a:      	pushl	%edi
  56569b:      	calll	0x571711 <.text+0x170711>
  5656a0:      	movl	0xc70340, %ecx
  5656a6:      	pushl	%edi
  5656a7:      	calll	0x571711 <.text+0x170711>
  5656ac:      	movl	0xc7033c, %ecx
  5656b2:      	pushl	%edi
  5656b3:      	calll	0x571711 <.text+0x170711>
  5656b8:      	movl	0xc70338, %ecx
  5656be:      	pushl	%edi
  5656bf:      	calll	0x571711 <.text+0x170711>
  5656c4:      	movl	0xc70334, %ecx
  5656ca:      	pushl	%edi
  5656cb:      	calll	0x571711 <.text+0x170711>
  5656d0:      	movl	0xc70330, %ecx
  5656d6:      	xorl	%ebx, %ebx
  5656d8:      	cmpl	%ebx, %ecx
  5656da:      	je	0x5656e2 <.text+0x1646e2>
  5656dc:      	pushl	%edi
  5656dd:      	calll	0x571711 <.text+0x170711>
  5656e2:      	movl	0xc7032c, %ecx
  5656e8:      	cmpl	%ebx, %ecx
  5656ea:      	je	0x5656f2 <.text+0x1646f2>
  5656ec:      	pushl	%edi
  5656ed:      	calll	0x571711 <.text+0x170711>
  5656f2:      	movl	0xc70328, %ecx
  5656f8:      	pushl	%edi
  5656f9:      	calll	0x571711 <.text+0x170711>
  5656fe:      	movl	0xc70324, %ecx
  565704:      	pushl	%edi
  565705:      	calll	0x571711 <.text+0x170711>
  56570a:      	movl	0xc70320, %ecx
  565710:      	pushl	%edi
  565711:      	calll	0x571711 <.text+0x170711>
  565716:      	movl	0xc7031c, %ecx
  56571c:      	pushl	%edi
  56571d:      	calll	0x571711 <.text+0x170711>
  565722:      	movl	0xc70318, %ecx
  565728:      	pushl	%edi
  565729:      	calll	0x571711 <.text+0x170711>
  56572e:      	movl	0xc70314, %ecx
  565734:      	pushl	%edi
  565735:      	calll	0x571711 <.text+0x170711>
  56573a:      	movl	0xc70310, %ecx
  565740:      	pushl	%edi
  565741:      	calll	0x571711 <.text+0x170711>
  565746:      	movl	0xc7030c, %ecx
  56574c:      	pushl	%edi
  56574d:      	calll	0x571711 <.text+0x170711>
  565752:      	movl	0xc70308, %ecx
  565758:      	pushl	%edi
  565759:      	calll	0x571711 <.text+0x170711>
  56575e:      	movl	0xc70304, %ecx
  565764:      	pushl	%edi
  565765:      	calll	0x571711 <.text+0x170711>
  56576a:      	movl	0xc70300, %ecx
  565770:      	pushl	%edi
  565771:      	calll	0x571711 <.text+0x170711>
  565776:      	movl	0xc702fc, %ecx
  56577c:      	pushl	%ebx
  56577d:      	pushl	%ebx
  56577e:      	pushl	%edi
  56577f:      	calll	0x570320 <.text+0x16f320>
  565784:      	movl	0xc702f8, %ecx
  56578a:      	pushl	%ebx
  56578b:      	pushl	%ebx
  56578c:      	pushl	%edi
  56578d:      	calll	0x570320 <.text+0x16f320>
  565792:      	movl	0xc702f4, %ecx
  565798:      	pushl	%ebx
  565799:      	pushl	%ebx
  56579a:      	pushl	%edi
  56579b:      	calll	0x570320 <.text+0x16f320>
  5657a0:      	movl	0xc702f0, %ecx
  5657a6:      	pushl	%ebx
  5657a7:      	pushl	%ebx
  5657a8:      	pushl	%edi
  5657a9:      	calll	0x570320 <.text+0x16f320>
  5657ae:      	movl	0xc702ec, %ecx
  5657b4:      	pushl	%ebx
  5657b5:      	pushl	%ebx
  5657b6:      	pushl	%edi
  5657b7:      	calll	0x570320 <.text+0x16f320>
  5657bc:      	movl	0xc702e8, %ecx
  5657c2:      	pushl	%ebx
  5657c3:      	pushl	%ebx
  5657c4:      	pushl	%edi
  5657c5:      	calll	0x570320 <.text+0x16f320>
  5657ca:      	movl	0xc702e4, %ecx
  5657d0:      	pushl	%ebx
  5657d1:      	pushl	%ebx
  5657d2:      	pushl	%edi
  5657d3:      	calll	0x570320 <.text+0x16f320>
  5657d8:      	movl	0xc702e0, %ecx
  5657de:      	pushl	%ebx
  5657df:      	pushl	%ebx
  5657e0:      	pushl	%edi
  5657e1:      	calll	0x570320 <.text+0x16f320>
  5657e6:      	movl	0xc702dc, %ecx
  5657ec:      	pushl	%ebx
  5657ed:      	pushl	%ebx
  5657ee:      	pushl	%edi
  5657ef:      	calll	0x570320 <.text+0x16f320>
  5657f4:      	pushl	%ebx
  5657f5:      	pushl	%ebx
  5657f6:      	pushl	%edi
  5657f7:      	movl	0xc702d8, %ecx
  5657fd:      	calll	0x570320 <.text+0x16f320>
  565802:      	movl	0xc702d4, %ecx
  565808:      	pushl	%ebx
  565809:      	pushl	%ebx
  56580a:      	pushl	%edi
  56580b:      	calll	0x570320 <.text+0x16f320>
  565810:      	leal	-0x24(%ebp), %eax
  565813:      	pushl	%eax
  565814:      	pushl	%esi
  565815:      	calll	*0x5ce5e8
  56581b:      	jmp	0x567650 <.text+0x166650>
  565820:      	movl	0xc702d0, %eax
  565825:      	xorl	%ebx, %ebx
  565827:      	cmpl	%ebx, %eax
  565829:      	je	0x565839 <.text+0x164839>
  56582b:      	pushl	%eax
  56582c:      	pushl	%esi
  56582d:      	calll	*0x5ce538
  565833:      	movl	%ebx, 0xc702d0
  565839:      	movl	0xc702cc, %ecx
  56583f:      	cmpl	%ebx, %ecx
  565841:      	je	0x565850 <.text+0x164850>
  565843:      	pushl	$0x1
  565845:      	calll	0x5570f0 <.text+0x1560f0>
  56584a:      	movl	%ebx, 0xc702cc
  565850:      	pushl	0xc702c8
  565856:      	movl	0x5ce054, %esi
  56585c:      	calll	*%esi
  56585e:      	pushl	0xc702c4
  565864:      	calll	*%esi
  565866:      	pushl	0xc702c0
  56586c:      	calll	*%esi
  56586e:      	xorl	%edi, %edi
  565870:      	pushl	0xc702ac(%edi)
  565876:      	calll	*%esi
  565878:      	addl	$0x4, %edi
  56587b:      	cmpl	$0x14, %edi
  56587e:      	jb	0x565870 <.text+0x164870>
  565880:      	calll	0x570daa <.text+0x16fdaa>
  565885:      	calll	0x570d92 <.text+0x16fd92>
  56588a:      	movl	0xc70354, %ecx
  565890:      	movl	%ecx, %esi
  565892:      	cmpl	%ebx, %ecx
  565894:      	je	0x5658a2 <.text+0x1648a2>
  565896:      	calll	0x56f7bb <.text+0x16e7bb>
  56589b:      	pushl	%esi
  56589c:      	calll	0x5c6d00 <.text+0x1c5d00>
  5658a1:      	popl	%ecx
  5658a2:      	movl	0xc70350, %ecx
  5658a8:      	movl	%ecx, %esi
  5658aa:      	cmpl	%ebx, %ecx
  5658ac:      	je	0x5658ba <.text+0x1648ba>
  5658ae:      	calll	0x56f3bb <.text+0x16e3bb>
  5658b3:      	pushl	%esi
  5658b4:      	calll	0x5c6d00 <.text+0x1c5d00>
  5658b9:      	popl	%ecx
  5658ba:      	movl	0xc7034c, %ecx
  5658c0:      	movl	%ecx, %esi
  5658c2:      	cmpl	%ebx, %ecx
  5658c4:      	je	0x5658d2 <.text+0x1648d2>
  5658c6:      	calll	0x56f3bb <.text+0x16e3bb>
  5658cb:      	pushl	%esi
  5658cc:      	calll	0x5c6d00 <.text+0x1c5d00>
  5658d1:      	popl	%ecx
  5658d2:      	movl	0xc70344, %ecx
  5658d8:      	movl	%ecx, %esi
  5658da:      	cmpl	%ebx, %ecx
  5658dc:      	je	0x5658ea <.text+0x1648ea>
  5658de:      	calll	0x56f3bb <.text+0x16e3bb>
  5658e3:      	pushl	%esi
  5658e4:      	calll	0x5c6d00 <.text+0x1c5d00>
  5658e9:      	popl	%ecx
  5658ea:      	movl	0xc70348, %ecx
  5658f0:      	movl	%ecx, %esi
  5658f2:      	cmpl	%ebx, %ecx
  5658f4:      	je	0x565902 <.text+0x164902>
  5658f6:      	calll	0x56f3bb <.text+0x16e3bb>
  5658fb:      	pushl	%esi
  5658fc:      	calll	0x5c6d00 <.text+0x1c5d00>
  565901:      	popl	%ecx
  565902:      	movl	0xc70340, %ecx
  565908:      	movl	%ecx, %esi
  56590a:      	cmpl	%ebx, %ecx
  56590c:      	je	0x56591a <.text+0x16491a>
  56590e:      	calll	0x56f3bb <.text+0x16e3bb>
  565913:      	pushl	%esi
  565914:      	calll	0x5c6d00 <.text+0x1c5d00>
  565919:      	popl	%ecx
  56591a:      	movl	0xc7033c, %ecx
  565920:      	movl	%ecx, %esi
  565922:      	cmpl	%ebx, %ecx
  565924:      	je	0x565932 <.text+0x164932>
  565926:      	calll	0x56f3bb <.text+0x16e3bb>
  56592b:      	pushl	%esi
  56592c:      	calll	0x5c6d00 <.text+0x1c5d00>
  565931:      	popl	%ecx
  565932:      	movl	0xc70338, %ecx
  565938:      	movl	%ecx, %esi
  56593a:      	cmpl	%ebx, %ecx
  56593c:      	je	0x56594a <.text+0x16494a>
  56593e:      	calll	0x56f3bb <.text+0x16e3bb>
  565943:      	pushl	%esi
  565944:      	calll	0x5c6d00 <.text+0x1c5d00>
  565949:      	popl	%ecx
  56594a:      	movl	0xc70334, %ecx
  565950:      	movl	%ecx, %esi
  565952:      	cmpl	%ebx, %ecx
  565954:      	je	0x565962 <.text+0x164962>
  565956:      	calll	0x56f3bb <.text+0x16e3bb>
  56595b:      	pushl	%esi
  56595c:      	calll	0x5c6d00 <.text+0x1c5d00>
  565961:      	popl	%ecx
  565962:      	movl	0xc70330, %ecx
  565968:      	cmpl	%ebx, %ecx
  56596a:      	je	0x56597a <.text+0x16497a>
  56596c:      	movl	%ecx, %esi
  56596e:      	calll	0x56f3bb <.text+0x16e3bb>
  565973:      	pushl	%esi
  565974:      	calll	0x5c6d00 <.text+0x1c5d00>
  565979:      	popl	%ecx
  56597a:      	movl	0xc7032c, %ecx
  565980:      	movl	%ebx, 0xc70330
  565986:      	cmpl	%ebx, %ecx
  565988:      	je	0x565998 <.text+0x164998>
  56598a:      	movl	%ecx, %esi
  56598c:      	calll	0x56f3bb <.text+0x16e3bb>
  565991:      	pushl	%esi
  565992:      	calll	0x5c6d00 <.text+0x1c5d00>
  565997:      	popl	%ecx
  565998:      	movl	0xc70328, %ecx
  56599e:      	movl	%ebx, 0xc7032c
  5659a4:      	movl	%ecx, %esi
  5659a6:      	cmpl	%ebx, %ecx
  5659a8:      	je	0x5659b6 <.text+0x1649b6>
  5659aa:      	calll	0x56f3bb <.text+0x16e3bb>
  5659af:      	pushl	%esi
  5659b0:      	calll	0x5c6d00 <.text+0x1c5d00>
  5659b5:      	popl	%ecx
  5659b6:      	movl	0xc70324, %ecx
  5659bc:      	movl	%ecx, %esi
  5659be:      	cmpl	%ebx, %ecx
  5659c0:      	je	0x5659ce <.text+0x1649ce>
  5659c2:      	calll	0x56f3bb <.text+0x16e3bb>
  5659c7:      	pushl	%esi
  5659c8:      	calll	0x5c6d00 <.text+0x1c5d00>
  5659cd:      	popl	%ecx
  5659ce:      	movl	0xc70320, %ecx
  5659d4:      	movl	%ecx, %esi
  5659d6:      	cmpl	%ebx, %ecx
  5659d8:      	je	0x5659e6 <.text+0x1649e6>
  5659da:      	calll	0x56f3bb <.text+0x16e3bb>
  5659df:      	pushl	%esi
  5659e0:      	calll	0x5c6d00 <.text+0x1c5d00>
  5659e5:      	popl	%ecx
  5659e6:      	movl	0xc7031c, %ecx
  5659ec:      	movl	%ecx, %esi
  5659ee:      	cmpl	%ebx, %ecx
  5659f0:      	je	0x5659fe <.text+0x1649fe>
  5659f2:      	calll	0x56f3bb <.text+0x16e3bb>
  5659f7:      	pushl	%esi
  5659f8:      	calll	0x5c6d00 <.text+0x1c5d00>
  5659fd:      	popl	%ecx
  5659fe:      	movl	0xc70318, %ecx
  565a04:      	movl	%ecx, %esi
  565a06:      	cmpl	%ebx, %ecx
  565a08:      	je	0x565a16 <.text+0x164a16>
  565a0a:      	calll	0x56f3bb <.text+0x16e3bb>
  565a0f:      	pushl	%esi
  565a10:      	calll	0x5c6d00 <.text+0x1c5d00>
  565a15:      	popl	%ecx
  565a16:      	movl	0xc70314, %ecx
  565a1c:      	movl	%ecx, %esi
  565a1e:      	cmpl	%ebx, %ecx
  565a20:      	je	0x565a2e <.text+0x164a2e>
  565a22:      	calll	0x56f3bb <.text+0x16e3bb>
  565a27:      	pushl	%esi
  565a28:      	calll	0x5c6d00 <.text+0x1c5d00>
  565a2d:      	popl	%ecx
  565a2e:      	movl	0xc70310, %ecx
  565a34:      	movl	%ecx, %esi
  565a36:      	cmpl	%ebx, %ecx
  565a38:      	je	0x565a46 <.text+0x164a46>
  565a3a:      	calll	0x56f3bb <.text+0x16e3bb>
  565a3f:      	pushl	%esi
  565a40:      	calll	0x5c6d00 <.text+0x1c5d00>
  565a45:      	popl	%ecx
  565a46:      	movl	0xc7030c, %ecx
  565a4c:      	movl	%ecx, %esi
  565a4e:      	cmpl	%ebx, %ecx
  565a50:      	je	0x565a5e <.text+0x164a5e>
  565a52:      	calll	0x56f3bb <.text+0x16e3bb>
  565a57:      	pushl	%esi
  565a58:      	calll	0x5c6d00 <.text+0x1c5d00>
  565a5d:      	popl	%ecx
  565a5e:      	movl	0xc70308, %ecx
  565a64:      	movl	%ecx, %esi
  565a66:      	cmpl	%ebx, %ecx
  565a68:      	je	0x565a76 <.text+0x164a76>
  565a6a:      	calll	0x56f3bb <.text+0x16e3bb>
  565a6f:      	pushl	%esi
  565a70:      	calll	0x5c6d00 <.text+0x1c5d00>
  565a75:      	popl	%ecx
  565a76:      	movl	0xc70304, %ecx
  565a7c:      	movl	%ecx, %esi
  565a7e:      	cmpl	%ebx, %ecx
  565a80:      	je	0x565a8e <.text+0x164a8e>
  565a82:      	calll	0x56f3bb <.text+0x16e3bb>
  565a87:      	pushl	%esi
  565a88:      	calll	0x5c6d00 <.text+0x1c5d00>
  565a8d:      	popl	%ecx
  565a8e:      	movl	0xc70300, %ecx
  565a94:      	movl	%ecx, %esi
  565a96:      	cmpl	%ebx, %ecx
  565a98:      	je	0x565aa6 <.text+0x164aa6>
  565a9a:      	calll	0x56f3bb <.text+0x16e3bb>
  565a9f:      	pushl	%esi
  565aa0:      	calll	0x5c6d00 <.text+0x1c5d00>
  565aa5:      	popl	%ecx
  565aa6:      	movl	0xc702fc, %ecx
  565aac:      	movl	%ecx, %esi
  565aae:      	cmpl	%ebx, %ecx
  565ab0:      	je	0x565abe <.text+0x164abe>
  565ab2:      	calll	0x570263 <.text+0x16f263>
  565ab7:      	pushl	%esi
  565ab8:      	calll	0x5c6d00 <.text+0x1c5d00>
  565abd:      	popl	%ecx
  565abe:      	movl	0xc702f8, %ecx
  565ac4:      	movl	%ecx, %esi
  565ac6:      	cmpl	%ebx, %ecx
  565ac8:      	je	0x565ad6 <.text+0x164ad6>
  565aca:      	calll	0x570263 <.text+0x16f263>
  565acf:      	pushl	%esi
  565ad0:      	calll	0x5c6d00 <.text+0x1c5d00>
  565ad5:      	popl	%ecx
  565ad6:      	movl	0xc702f4, %ecx
  565adc:      	movl	%ecx, %esi
  565ade:      	cmpl	%ebx, %ecx
  565ae0:      	je	0x565aee <.text+0x164aee>
  565ae2:      	calll	0x570263 <.text+0x16f263>
  565ae7:      	pushl	%esi
  565ae8:      	calll	0x5c6d00 <.text+0x1c5d00>
  565aed:      	popl	%ecx
  565aee:      	movl	0xc702f0, %ecx
  565af4:      	movl	%ecx, %esi
  565af6:      	cmpl	%ebx, %ecx
  565af8:      	je	0x565b06 <.text+0x164b06>
  565afa:      	calll	0x570263 <.text+0x16f263>
  565aff:      	pushl	%esi
  565b00:      	calll	0x5c6d00 <.text+0x1c5d00>
  565b05:      	popl	%ecx
  565b06:      	movl	0xc702ec, %ecx
  565b0c:      	movl	%ecx, %esi
  565b0e:      	cmpl	%ebx, %ecx
  565b10:      	je	0x565b1e <.text+0x164b1e>
  565b12:      	calll	0x570263 <.text+0x16f263>
  565b17:      	pushl	%esi
  565b18:      	calll	0x5c6d00 <.text+0x1c5d00>
  565b1d:      	popl	%ecx
  565b1e:      	movl	0xc702e8, %ecx
  565b24:      	movl	%ecx, %esi
  565b26:      	cmpl	%ebx, %ecx
  565b28:      	je	0x565b36 <.text+0x164b36>
  565b2a:      	calll	0x570263 <.text+0x16f263>
  565b2f:      	pushl	%esi
  565b30:      	calll	0x5c6d00 <.text+0x1c5d00>
  565b35:      	popl	%ecx
  565b36:      	movl	0xc702e4, %ecx
  565b3c:      	movl	%ecx, %esi
  565b3e:      	cmpl	%ebx, %ecx
  565b40:      	je	0x565b4e <.text+0x164b4e>
  565b42:      	calll	0x570263 <.text+0x16f263>
  565b47:      	pushl	%esi
  565b48:      	calll	0x5c6d00 <.text+0x1c5d00>
  565b4d:      	popl	%ecx
  565b4e:      	movl	0xc702e0, %ecx
  565b54:      	movl	%ecx, %esi
  565b56:      	cmpl	%ebx, %ecx
  565b58:      	je	0x565b66 <.text+0x164b66>
  565b5a:      	calll	0x570263 <.text+0x16f263>
  565b5f:      	pushl	%esi
  565b60:      	calll	0x5c6d00 <.text+0x1c5d00>
  565b65:      	popl	%ecx
  565b66:      	movl	0xc702dc, %ecx
  565b6c:      	movl	%ecx, %esi
  565b6e:      	cmpl	%ebx, %ecx
  565b70:      	je	0x565b7e <.text+0x164b7e>
  565b72:      	calll	0x570263 <.text+0x16f263>
  565b77:      	pushl	%esi
  565b78:      	calll	0x5c6d00 <.text+0x1c5d00>
  565b7d:      	popl	%ecx
  565b7e:      	movl	0xc702d8, %ecx
  565b84:      	movl	%ecx, %esi
  565b86:      	cmpl	%ebx, %ecx
  565b88:      	je	0x565b96 <.text+0x164b96>
  565b8a:      	calll	0x570263 <.text+0x16f263>
  565b8f:      	pushl	%esi
  565b90:      	calll	0x5c6d00 <.text+0x1c5d00>
  565b95:      	popl	%ecx
  565b96:      	movl	0xc702d4, %ecx
  565b9c:      	movl	%ecx, %esi
  565b9e:      	cmpl	%ebx, %ecx
  565ba0:      	je	0x567650 <.text+0x166650>
  565ba6:      	calll	0x570263 <.text+0x16f263>
  565bab:      	pushl	%esi
  565bac:      	calll	0x5c6d00 <.text+0x1c5d00>
  565bb1:      	popl	%ecx
  565bb2:      	jmp	0x567650 <.text+0x166650>
  565bb7:      	cmpl	$-0x1, 0x8(%ebx)
  565bbb:      	je	0x567650 <.text+0x166650>
  565bc1:      	movl	0xc(%ebx), %eax
  565bc4:      	decl	%eax
  565bc5:      	cmpl	$0x1, %eax
  565bc8:      	ja	0x567785 <.text+0x166785>
  565bce:      	movl	0x14(%ebx), %eax
  565bd1:      	movl	0x5ce53c, %edi
  565bd7:      	pushl	$0x437                  # imm = 0x437
  565bdc:      	pushl	%esi
  565bdd:      	movl	%eax, -0x28(%ebp)
  565be0:      	calll	*%edi
  565be2:      	cmpl	%eax, -0x28(%ebp)
  565be5:      	jne	0x565f4d <.text+0x164f4d>
  565beb:      	xorl	%edi, %edi
  565bed:      	pushl	%edi
  565bee:      	pushl	0x8(%ebx)
  565bf1:      	pushl	$0x199                  # imm = 0x199
  565bf6:      	pushl	-0x28(%ebp)
  565bf9:      	calll	*0x5ce558
  565bff:      	pushl	%eax
  565c00:      	movl	$0xc6fdec, %ecx         # imm = 0xC6FDEC
  565c05:      	calll	0x558bff <.text+0x157bff>
  565c0a:      	movl	%eax, -0x3c(%ebp)
  565c0d:      	cmpl	%edi, %eax
  565c0f:      	je	0x567785 <.text+0x166785>
  565c15:      	leal	-0x1c(%ebp), %eax
  565c18:      	pushl	%eax
  565c19:      	pushl	0x18(%ebx)
  565c1c:      	calll	*0x5ce084
  565c22:      	movl	0x20(%ebx), %esi
  565c25:      	movl	0x28(%ebx), %ecx
  565c28:      	movl	%esi, %eax
  565c2a:      	subl	-0x1c(%ebp), %eax
  565c2d:      	addl	%ecx, %eax
  565c2f:      	cltd
  565c30:      	subl	%edx, %eax
  565c32:      	sarl	%eax
  565c34:      	testb	$0x1, 0x10(%ebx)
  565c38:      	movl	%eax, -0x38(%ebp)
  565c3b:      	movl	0x1c(%ebx), %eax
  565c3e:      	je	0x565c86 <.text+0x164c86>
  565c40:      	movl	%eax, -0x4c(%ebp)
  565c43:      	movl	0x24(%ebx), %eax
  565c46:      	movl	%eax, -0x44(%ebp)
  565c49:      	leal	-0x4c(%ebp), %eax
  565c4c:      	pushl	%eax
  565c4d:      	pushl	0x18(%ebx)
  565c50:      	movl	%esi, -0x48(%ebp)
  565c53:      	movl	%ecx, -0x40(%ebp)
  565c56:      	calll	*0x5ce524
  565c5c:      	leal	0x72c(%ebp), %eax
  565c62:      	pushl	%eax
  565c63:      	movl	%edi, 0x72c(%ebp)
  565c69:      	movl	$0x6400, 0x730(%ebp)    # imm = 0x6400
  565c73:      	movl	%edi, 0x734(%ebp)
  565c79:      	calll	*0x5ce088
  565c7f:      	movl	%eax, %esi
  565c81:      	leal	-0x4c(%ebp), %eax
  565c84:      	jmp	0x565cb9 <.text+0x164cb9>
  565c86:      	movl	%eax, -0x6c(%ebp)
  565c89:      	movl	0x24(%ebx), %eax
  565c8c:      	movl	%eax, -0x64(%ebp)
  565c8f:      	leal	0x72c(%ebp), %eax
  565c95:      	pushl	%eax
  565c96:      	movl	%esi, -0x68(%ebp)
  565c99:      	movl	%ecx, -0x60(%ebp)
  565c9c:      	movl	%edi, 0x72c(%ebp)
  565ca2:      	movl	%edi, 0x730(%ebp)
  565ca8:      	movl	%edi, 0x734(%ebp)
  565cae:      	calll	*0x5ce088
  565cb4:      	movl	%eax, %esi
  565cb6:      	leal	-0x6c(%ebp), %eax
  565cb9:      	pushl	%esi
  565cba:      	pushl	%eax
  565cbb:      	pushl	0x18(%ebx)
  565cbe:      	calll	*0x5ce528
  565cc4:      	cmpl	%edi, %esi
  565cc6:      	je	0x565ccf <.text+0x164ccf>
  565cc8:      	pushl	%esi
  565cc9:      	calll	*0x5ce054
  565ccf:      	movl	-0x3c(%ebp), %eax
  565cd2:      	movzwl	0x22(%eax), %eax
  565cd6:      	pushl	%eax
  565cd7:      	movl	$0xc6fdec, %ecx         # imm = 0xC6FDEC
  565cdc:      	calll	0x558c66 <.text+0x157c66>
  565ce1:      	movl	0x5ce050, %esi
  565ce7:      	movl	$0xcc0020, %edi         # imm = 0xCC0020
  565cec:      	testb	%al, %al
  565cee:      	je	0x565d45 <.text+0x164d45>
  565cf0:      	pushl	0x18(%ebx)
  565cf3:      	calll	*0x5ce0d0
  565cf9:      	pushl	0xc702c4
  565cff:      	movl	%eax, -0x28(%ebp)
  565d02:      	pushl	%eax
  565d03:      	calll	*%esi
  565d05:      	movl	0x28(%ebx), %edx
  565d08:      	movl	0x1c(%ebx), %ecx
  565d0b:      	pushl	%edi
  565d0c:      	pushl	$0x0
  565d0e:      	pushl	$0x0
  565d10:      	pushl	-0x28(%ebp)
  565d13:      	movl	%eax, -0x2c(%ebp)
  565d16:      	movl	0x20(%ebx), %eax
  565d19:      	subl	%eax, %edx
  565d1b:      	subl	$0x3, %edx
  565d1e:      	pushl	%edx
  565d1f:      	movl	0x24(%ebx), %edx
  565d22:      	subl	%ecx, %edx
  565d24:      	decl	%edx
  565d25:      	pushl	%edx
  565d26:      	addl	$0x3, %eax
  565d29:      	pushl	%eax
  565d2a:      	pushl	%ecx
  565d2b:      	pushl	0x18(%ebx)
  565d2e:      	calll	*0x5ce08c
  565d34:      	pushl	-0x2c(%ebp)
  565d37:      	pushl	-0x28(%ebp)
  565d3a:      	calll	*%esi
  565d3c:      	pushl	-0x28(%ebp)
  565d3f:      	calll	*0x5ce03c
  565d45:      	movl	-0x3c(%ebp), %eax
  565d48:      	movzwl	0x22(%eax), %eax
  565d4c:      	pushl	%eax
  565d4d:      	movl	$0xc6fdec, %ecx         # imm = 0xC6FDEC
  565d52:      	calll	0x558d24 <.text+0x157d24>
  565d57:      	testb	%al, %al
  565d59:      	je	0x565db0 <.text+0x164db0>
  565d5b:      	pushl	0x18(%ebx)
  565d5e:      	calll	*0x5ce0d0
  565d64:      	pushl	0xc702c0
  565d6a:      	movl	%eax, -0x28(%ebp)
  565d6d:      	pushl	%eax
  565d6e:      	calll	*%esi
  565d70:      	movl	0x28(%ebx), %edx
  565d73:      	movl	0x1c(%ebx), %ecx
  565d76:      	pushl	%edi
  565d77:      	pushl	$0x0
  565d79:      	pushl	$0x0
  565d7b:      	pushl	-0x28(%ebp)
  565d7e:      	movl	%eax, -0x2c(%ebp)
  565d81:      	movl	0x20(%ebx), %eax
  565d84:      	subl	%eax, %edx
  565d86:      	subl	$0x3, %edx
  565d89:      	pushl	%edx
  565d8a:      	movl	0x24(%ebx), %edx
  565d8d:      	subl	%ecx, %edx
  565d8f:      	decl	%edx
  565d90:      	pushl	%edx
  565d91:      	addl	$0x3, %eax
  565d94:      	pushl	%eax
  565d95:      	pushl	%ecx
  565d96:      	pushl	0x18(%ebx)
  565d99:      	calll	*0x5ce08c
  565d9f:      	pushl	-0x2c(%ebp)
  565da2:      	pushl	-0x28(%ebp)
  565da5:      	calll	*%esi
  565da7:      	pushl	-0x28(%ebp)
  565daa:      	calll	*0x5ce03c
  565db0:      	pushl	0x18(%ebx)
  565db3:      	calll	*0x5ce090
  565db9:      	pushl	0x18(%ebx)
  565dbc:      	movl	%eax, -0x28(%ebp)
  565dbf:      	calll	*0x5ce098
  565dc5:      	pushl	$0xb
  565dc7:      	popl	%esi
  565dc8:      	movl	%eax, -0x34(%ebp)
  565dcb:      	movl	0x20(%ebx), %eax
  565dce:      	pushl	$0x0
  565dd0:      	pushl	0x18(%ebx)
  565dd3:      	movl	%eax, -0x58(%ebp)
  565dd6:      	movl	0x28(%ebx), %eax
  565dd9:      	movl	%esi, -0x5c(%ebp)
  565ddc:      	movl	$0x74, -0x54(%ebp)
  565de3:      	movl	%eax, -0x50(%ebp)
  565de6:      	calll	*0x5ce09c
  565dec:      	movl	-0x3c(%ebp), %edi
  565def:      	movl	%edi, %eax
  565df1:      	leal	0x1(%eax), %ecx
  565df4:      	movb	(%eax), %dl
  565df6:      	incl	%eax
  565df7:      	testb	%dl, %dl
  565df9:      	jne	0x565df4 <.text+0x164df4>
  565dfb:      	pushl	$0x0
  565dfd:      	subl	%ecx, %eax
  565dff:      	pushl	%eax
  565e00:      	pushl	%edi
  565e01:      	leal	-0x5c(%ebp), %eax
  565e04:      	pushl	%eax
  565e05:      	pushl	$0x4
  565e07:      	pushl	-0x38(%ebp)
  565e0a:      	pushl	%esi
  565e0b:      	pushl	0x18(%ebx)
  565e0e:      	calll	*0x5ce094
  565e14:      	movw	0x62aea4, %ax
  565e1a:      	cmpw	0x22(%edi), %ax
  565e1e:      	je	0x565f30 <.text+0x164f30>
  565e24:      	pushl	$0x2
  565e26:      	pushl	0x18(%ebx)
  565e29:      	calll	*0x5ce09c
  565e2f:      	movl	0x18(%edi), %eax
  565e32:      	movl	$0x5df2a4, %esi         # imm = 0x5DF2A4
  565e37:      	testl	%eax, %eax
  565e39:      	jle	0x565e7b <.text+0x164e7b>
  565e3b:      	cmpl	$0x3e8, %eax            # imm = 0x3E8
  565e40:      	jle	0x565e49 <.text+0x164e49>
  565e42:      	pushl	$0xff
  565e47:      	jmp	0x565e5c <.text+0x164e5c>
  565e49:      	cmpl	$0x1f4, %eax            # imm = 0x1F4
  565e4e:      	jle	0x565e57 <.text+0x164e57>
  565e50:      	pushl	$0xffff                 # imm = 0xFFFF
  565e55:      	jmp	0x565e5c <.text+0x164e5c>
  565e57:      	pushl	$0xff00                 # imm = 0xFF00
  565e5c:      	pushl	0x18(%ebx)
  565e5f:      	calll	*0x5ce04c
  565e65:      	pushl	0x18(%edi)
  565e68:      	leal	0x6b8(%ebp), %eax
  565e6e:      	pushl	%esi
  565e6f:      	pushl	%eax
  565e70:      	calll	*0x5ce49c
  565e76:      	addl	$0xc, %esp
  565e79:      	jmp	0x565e9d <.text+0x164e9d>
  565e7b:      	pushl	$0x7f7f7f               # imm = 0x7F7F7F
  565e80:      	pushl	0x18(%ebx)
  565e83:      	calll	*0x5ce04c
  565e89:      	leal	0x6b8(%ebp), %eax
  565e8f:      	pushl	$0x5f0db4               # imm = 0x5F0DB4
  565e94:      	pushl	%eax
  565e95:      	calll	*0x5ce49c
  565e9b:      	popl	%ecx
  565e9c:      	popl	%ecx
  565e9d:      	leal	0x6b8(%ebp), %eax
  565ea3:      	leal	0x1(%eax), %edx
  565ea6:      	movb	(%eax), %cl
  565ea8:      	incl	%eax
  565ea9:      	testb	%cl, %cl
  565eab:      	jne	0x565ea6 <.text+0x164ea6>
  565ead:      	subl	%edx, %eax
  565eaf:      	pushl	%eax
  565eb0:      	leal	0x6b8(%ebp), %eax
  565eb6:      	pushl	%eax
  565eb7:      	pushl	-0x38(%ebp)
  565eba:      	pushl	$0x84
  565ebf:      	pushl	0x18(%ebx)
  565ec2:      	calll	*0x5ce0a8
  565ec8:      	movl	0x1c(%edi), %eax
  565ecb:      	cmpl	$0x42, %eax
  565ece:      	jle	0x565ed7 <.text+0x164ed7>
  565ed0:      	pushl	$0xff
  565ed5:      	jmp	0x565ee8 <.text+0x164ee8>
  565ed7:      	cmpl	$0x21, %eax
  565eda:      	jle	0x565ee3 <.text+0x164ee3>
  565edc:      	pushl	$0xffff                 # imm = 0xFFFF
  565ee1:      	jmp	0x565ee8 <.text+0x164ee8>
  565ee3:      	pushl	$0xff00                 # imm = 0xFF00
  565ee8:      	pushl	0x18(%ebx)
  565eeb:      	calll	*0x5ce04c
  565ef1:      	pushl	0x1c(%edi)
  565ef4:      	leal	0x6b8(%ebp), %eax
  565efa:      	pushl	%esi
  565efb:      	pushl	%eax
  565efc:      	calll	*0x5ce49c
  565f02:      	leal	0x6b8(%ebp), %eax
  565f08:      	addl	$0xc, %esp
  565f0b:      	leal	0x1(%eax), %esi
  565f0e:      	movb	(%eax), %cl
  565f10:      	incl	%eax
  565f11:      	testb	%cl, %cl
  565f13:      	jne	0x565f0e <.text+0x164f0e>
  565f15:      	subl	%esi, %eax
  565f17:      	pushl	%eax
  565f18:      	leal	0x6b8(%ebp), %eax
  565f1e:      	pushl	%eax
  565f1f:      	pushl	-0x38(%ebp)
  565f22:      	pushl	$0x9e
  565f27:      	pushl	0x18(%ebx)
  565f2a:      	calll	*0x5ce0a8
  565f30:      	pushl	-0x34(%ebp)
  565f33:      	pushl	0x18(%ebx)
  565f36:      	calll	*0x5ce09c
  565f3c:      	pushl	-0x28(%ebp)
  565f3f:      	pushl	0x18(%ebx)
  565f42:      	calll	*0x5ce04c
  565f48:      	jmp	0x567785 <.text+0x166785>
  565f4d:      	movl	0x14(%ebx), %eax
  565f50:      	pushl	$0x810                  # imm = 0x810
  565f55:      	pushl	%esi
  565f56:      	movl	%eax, -0x28(%ebp)
  565f59:      	calll	*%edi
  565f5b:      	cmpl	%eax, -0x28(%ebp)
  565f5e:      	jne	0x5661b6 <.text+0x1651b6>
  565f64:      	pushl	$0x0
  565f66:      	pushl	0x8(%ebx)
  565f69:      	pushl	$0x199                  # imm = 0x199
  565f6e:      	pushl	-0x28(%ebp)
  565f71:      	calll	*0x5ce558
  565f77:      	pushl	%eax
  565f78:      	movl	$0xc6fe28, %ecx         # imm = 0xC6FE28
  565f7d:      	calll	0x55887b <.text+0x15787b>
  565f82:      	movl	%eax, %edi
  565f84:      	testl	%edi, %edi
  565f86:      	je	0x567785 <.text+0x166785>
  565f8c:      	leal	-0x1c(%ebp), %eax
  565f8f:      	pushl	%eax
  565f90:      	pushl	0x18(%ebx)
  565f93:      	calll	*0x5ce084
  565f99:      	movl	0x20(%ebx), %esi
  565f9c:      	movl	0x28(%ebx), %ecx
  565f9f:      	movl	%esi, %eax
  565fa1:      	subl	-0x1c(%ebp), %eax
  565fa4:      	addl	%ecx, %eax
  565fa6:      	cltd
  565fa7:      	subl	%edx, %eax
  565fa9:      	sarl	%eax
  565fab:      	testb	$0x1, 0x10(%ebx)
  565faf:      	movl	%eax, -0x38(%ebp)
  565fb2:      	movl	0x1c(%ebx), %eax
  565fb5:      	je	0x565fff <.text+0x164fff>
  565fb7:      	movl	%eax, -0x4c(%ebp)
  565fba:      	movl	0x24(%ebx), %eax
  565fbd:      	movl	%eax, -0x44(%ebp)
  565fc0:      	leal	-0x4c(%ebp), %eax
  565fc3:      	pushl	%eax
  565fc4:      	pushl	0x18(%ebx)
  565fc7:      	movl	%esi, -0x48(%ebp)
  565fca:      	movl	%ecx, -0x40(%ebp)
  565fcd:      	calll	*0x5ce524
  565fd3:      	andl	$0x0, 0x72c(%ebp)
  565fda:      	andl	$0x0, 0x734(%ebp)
  565fe1:      	leal	0x72c(%ebp), %eax
  565fe7:      	pushl	%eax
  565fe8:      	movl	$0x6400, 0x730(%ebp)    # imm = 0x6400
  565ff2:      	calll	*0x5ce088
  565ff8:      	movl	%eax, %esi
  565ffa:      	leal	-0x4c(%ebp), %eax
  565ffd:      	jmp	0x566034 <.text+0x165034>
  565fff:      	movl	%eax, -0x5c(%ebp)
  566002:      	movl	0x24(%ebx), %eax
  566005:      	movl	%eax, -0x54(%ebp)
  566008:      	xorl	%eax, %eax
  56600a:      	movl	%eax, 0x72c(%ebp)
  566010:      	movl	%eax, 0x730(%ebp)
  566016:      	movl	%eax, 0x734(%ebp)
  56601c:      	leal	0x72c(%ebp), %eax
  566022:      	pushl	%eax
  566023:      	movl	%esi, -0x58(%ebp)
  566026:      	movl	%ecx, -0x50(%ebp)
  566029:      	calll	*0x5ce088
  56602f:      	movl	%eax, %esi
  566031:      	leal	-0x5c(%ebp), %eax
  566034:      	pushl	%esi
  566035:      	pushl	%eax
  566036:      	pushl	0x18(%ebx)
  566039:      	calll	*0x5ce528
  56603f:      	testl	%esi, %esi
  566041:      	je	0x56604a <.text+0x16504a>
  566043:      	pushl	%esi
  566044:      	calll	*0x5ce054
  56604a:      	cmpb	$0x0, 0x41(%edi)
  56604e:      	je	0x56609c <.text+0x16509c>
  566050:      	pushl	0x18(%ebx)
  566053:      	calll	*0x5ce0d0
  566059:      	pushl	0xc702c8
  56605f:      	movl	%eax, -0x28(%ebp)
  566062:      	pushl	%eax
  566063:      	calll	*0x5ce050
  566069:      	movl	0x28(%ebx), %edx
  56606c:      	movl	0x1c(%ebx), %ecx
  56606f:      	pushl	$0xcc0020               # imm = 0xCC0020
  566074:      	pushl	$0x0
  566076:      	pushl	$0x0
  566078:      	pushl	-0x28(%ebp)
  56607b:      	movl	%eax, -0x2c(%ebp)
  56607e:      	movl	0x20(%ebx), %eax
  566081:      	subl	%eax, %edx
  566083:      	subl	$0x3, %edx
  566086:      	pushl	%edx
  566087:      	movl	0x24(%ebx), %edx
  56608a:      	subl	%ecx, %edx
  56608c:      	decl	%edx
  56608d:      	pushl	%edx
  56608e:      	addl	$0x3, %eax
  566091:      	pushl	%eax
  566092:      	pushl	%ecx
  566093:      	pushl	0x18(%ebx)
  566096:      	calll	*0x5ce08c
  56609c:      	movl	0x20(%ebx), %eax
  56609f:      	pushl	$0xb
  5660a1:      	popl	%esi
  5660a2:      	pushl	0x18(%ebx)
  5660a5:      	movl	%eax, -0x68(%ebp)
  5660a8:      	movl	0x28(%ebx), %eax
  5660ab:      	movl	%esi, -0x6c(%ebp)
  5660ae:      	movl	$0x85, -0x64(%ebp)
  5660b5:      	movl	%eax, -0x60(%ebp)
  5660b8:      	calll	*0x5ce098
  5660be:      	pushl	$0x0
  5660c0:      	pushl	0x18(%ebx)
  5660c3:      	movl	%eax, -0x3c(%ebp)
  5660c6:      	calll	*0x5ce09c
  5660cc:      	leal	0x17(%edi), %ecx
  5660cf:      	movl	%ecx, %eax
  5660d1:      	leal	0x1(%eax), %edx
  5660d4:      	movl	%edx, -0x34(%ebp)
  5660d7:      	movb	(%eax), %dl
  5660d9:      	incl	%eax
  5660da:      	testb	%dl, %dl
  5660dc:      	jne	0x5660d7 <.text+0x1650d7>
  5660de:      	subl	-0x34(%ebp), %eax
  5660e1:      	pushl	$0x0
  5660e3:      	pushl	%eax
  5660e4:      	pushl	%ecx
  5660e5:      	leal	-0x6c(%ebp), %eax
  5660e8:      	pushl	%eax
  5660e9:      	pushl	$0x4
  5660eb:      	pushl	-0x38(%ebp)
  5660ee:      	pushl	%esi
  5660ef:      	pushl	0x18(%ebx)
  5660f2:      	calll	*0x5ce094
  5660f8:      	pushl	$0x2
  5660fa:      	pushl	0x18(%ebx)
  5660fd:      	calll	*0x5ce09c
  566103:      	movswl	0x13(%edi), %eax
  566107:      	pushl	%eax
  566108:      	movl	$0x5df2a4, %esi         # imm = 0x5DF2A4
  56610d:      	leal	0x6b8(%ebp), %eax
  566113:      	pushl	%esi
  566114:      	pushl	%eax
  566115:      	calll	*0x5ce49c
  56611b:      	leal	0x6b8(%ebp), %eax
  566121:      	addl	$0xc, %esp
  566124:      	leal	0x1(%eax), %ecx
  566127:      	movb	(%eax), %dl
  566129:      	incl	%eax
  56612a:      	testb	%dl, %dl
  56612c:      	jne	0x566127 <.text+0x165127>
  56612e:      	subl	%ecx, %eax
  566130:      	pushl	%eax
  566131:      	leal	0x6b8(%ebp), %eax
  566137:      	pushl	%eax
  566138:      	pushl	-0x38(%ebp)
  56613b:      	pushl	$0x8b
  566140:      	pushl	0x18(%ebx)
  566143:      	calll	*0x5ce0a8
  566149:      	movswl	0x11(%edi), %eax
  56614d:      	pushl	%eax
  56614e:      	leal	0x6b8(%ebp), %eax
  566154:      	pushl	%esi
  566155:      	pushl	%eax
  566156:      	calll	*0x5ce49c
  56615c:      	leal	0x6b8(%ebp), %eax
  566162:      	addl	$0xc, %esp
  566165:      	leal	0x1(%eax), %esi
  566168:      	movb	(%eax), %cl
  56616a:      	incl	%eax
  56616b:      	testb	%cl, %cl
  56616d:      	jne	0x566168 <.text+0x165168>
  56616f:      	subl	%esi, %eax
  566171:      	pushl	%eax
  566172:      	leal	0x6b8(%ebp), %eax
  566178:      	pushl	%eax
  566179:      	pushl	-0x38(%ebp)
  56617c:      	pushl	$0x9e
  566181:      	pushl	0x18(%ebx)
  566184:      	calll	*0x5ce0a8
  56618a:      	cmpb	$0x0, 0x41(%edi)
  56618e:      	je	0x5661a5 <.text+0x1651a5>
  566190:      	pushl	-0x2c(%ebp)
  566193:      	pushl	-0x28(%ebp)
  566196:      	calll	*0x5ce050
  56619c:      	pushl	-0x28(%ebp)
  56619f:      	calll	*0x5ce03c
  5661a5:      	pushl	-0x3c(%ebp)
  5661a8:      	pushl	0x18(%ebx)
  5661ab:      	calll	*0x5ce09c
  5661b1:      	jmp	0x567785 <.text+0x166785>
  5661b6:      	movl	0x14(%ebx), %eax
  5661b9:      	pushl	$0x436                  # imm = 0x436
  5661be:      	pushl	%esi
  5661bf:      	movl	%eax, -0x28(%ebp)
  5661c2:      	calll	*%edi
  5661c4:      	cmpl	%eax, -0x28(%ebp)
  5661c7:      	jne	0x566348 <.text+0x165348>
  5661cd:      	pushl	$0x0
  5661cf:      	pushl	0x8(%ebx)
  5661d2:      	pushl	$0x199                  # imm = 0x199
  5661d7:      	pushl	-0x28(%ebp)
  5661da:      	calll	*0x5ce558
  5661e0:      	movl	$0xc6fea8, %edi         # imm = 0xC6FEA8
  5661e5:      	pushl	%eax
  5661e6:      	movl	%edi, %ecx
  5661e8:      	calll	0x558bff <.text+0x157bff>
  5661ed:      	movl	%eax, -0x38(%ebp)
  5661f0:      	testl	%eax, %eax
  5661f2:      	je	0x567785 <.text+0x166785>
  5661f8:      	leal	-0x1c(%ebp), %eax
  5661fb:      	pushl	%eax
  5661fc:      	pushl	0x18(%ebx)
  5661ff:      	calll	*0x5ce084
  566205:      	movl	0x20(%ebx), %esi
  566208:      	movl	0x28(%ebx), %ecx
  56620b:      	movl	%esi, %eax
  56620d:      	subl	-0x1c(%ebp), %eax
  566210:      	addl	%ecx, %eax
  566212:      	cltd
  566213:      	subl	%edx, %eax
  566215:      	sarl	%eax
  566217:      	testb	$0x1, 0x10(%ebx)
  56621b:      	movl	%eax, -0x34(%ebp)
  56621e:      	movl	0x1c(%ebx), %eax
  566221:      	je	0x56626b <.text+0x16526b>
  566223:      	movl	%eax, -0x4c(%ebp)
  566226:      	movl	0x24(%ebx), %eax
  566229:      	movl	%eax, -0x44(%ebp)
  56622c:      	leal	-0x4c(%ebp), %eax
  56622f:      	pushl	%eax
  566230:      	pushl	0x18(%ebx)
  566233:      	movl	%esi, -0x48(%ebp)
  566236:      	movl	%ecx, -0x40(%ebp)
  566239:      	calll	*0x5ce524
  56623f:      	andl	$0x0, 0x72c(%ebp)
  566246:      	andl	$0x0, 0x734(%ebp)
  56624d:      	leal	0x72c(%ebp), %eax
  566253:      	pushl	%eax
  566254:      	movl	$0x6400, 0x730(%ebp)    # imm = 0x6400
  56625e:      	calll	*0x5ce088
  566264:      	movl	%eax, %esi
  566266:      	leal	-0x4c(%ebp), %eax
  566269:      	jmp	0x5662a0 <.text+0x1652a0>
  56626b:      	movl	%eax, -0x5c(%ebp)
  56626e:      	movl	0x24(%ebx), %eax
  566271:      	movl	%eax, -0x54(%ebp)
  566274:      	xorl	%eax, %eax
  566276:      	movl	%eax, 0x72c(%ebp)
  56627c:      	movl	%eax, 0x730(%ebp)
  566282:      	movl	%eax, 0x734(%ebp)
  566288:      	leal	0x72c(%ebp), %eax
  56628e:      	pushl	%eax
  56628f:      	movl	%esi, -0x58(%ebp)
  566292:      	movl	%ecx, -0x50(%ebp)
  566295:      	calll	*0x5ce088
  56629b:      	movl	%eax, %esi
  56629d:      	leal	-0x5c(%ebp), %eax
  5662a0:      	pushl	%esi
  5662a1:      	pushl	%eax
  5662a2:      	pushl	0x18(%ebx)
  5662a5:      	calll	*0x5ce528
  5662ab:      	testl	%esi, %esi
  5662ad:      	je	0x5662b6 <.text+0x1652b6>
  5662af:      	pushl	%esi
  5662b0:      	calll	*0x5ce054
  5662b6:      	movl	-0x38(%ebp), %eax
  5662b9:      	movzwl	0x22(%eax), %eax
  5662bd:      	pushl	%eax
  5662be:      	movl	%edi, %ecx
  5662c0:      	calll	0x5594b6 <.text+0x1584b6>
  5662c5:      	testb	%al, %al
  5662c7:      	je	0x566322 <.text+0x165322>
  5662c9:      	pushl	0x18(%ebx)
  5662cc:      	calll	*0x5ce0d0
  5662d2:      	pushl	0xc702c4
  5662d8:      	movl	0x5ce050, %edi
  5662de:      	movl	%eax, %esi
  5662e0:      	pushl	%esi
  5662e1:      	calll	*%edi
  5662e3:      	movl	0x28(%ebx), %edx
  5662e6:      	movl	0x1c(%ebx), %ecx
  5662e9:      	pushl	$0xcc0020               # imm = 0xCC0020
  5662ee:      	pushl	$0x0
  5662f0:      	pushl	$0x0
  5662f2:      	movl	%eax, -0x2c(%ebp)
  5662f5:      	movl	0x20(%ebx), %eax
  5662f8:      	subl	%eax, %edx
  5662fa:      	pushl	%esi
  5662fb:      	subl	$0x3, %edx
  5662fe:      	pushl	%edx
  5662ff:      	movl	0x24(%ebx), %edx
  566302:      	subl	%ecx, %edx
  566304:      	decl	%edx
  566305:      	pushl	%edx
  566306:      	addl	$0x3, %eax
  566309:      	pushl	%eax
  56630a:      	incl	%ecx
  56630b:      	pushl	%ecx
  56630c:      	pushl	0x18(%ebx)
  56630f:      	calll	*0x5ce08c
  566315:      	pushl	-0x2c(%ebp)
  566318:      	pushl	%esi
  566319:      	calll	*%edi
  56631b:      	pushl	%esi
  56631c:      	calll	*0x5ce03c
  566322:      	movl	-0x38(%ebp), %eax
  566325:      	leal	0x1(%eax), %edx
  566328:      	movb	(%eax), %cl
  56632a:      	incl	%eax
  56632b:      	testb	%cl, %cl
  56632d:      	jne	0x566328 <.text+0x165328>
  56632f:      	subl	%edx, %eax
  566331:      	pushl	%eax
  566332:      	pushl	-0x38(%ebp)
  566335:      	pushl	-0x34(%ebp)
  566338:      	pushl	$0xd
  56633a:      	pushl	0x18(%ebx)
  56633d:      	calll	*0x5ce0a8
  566343:      	jmp	0x567785 <.text+0x166785>
  566348:      	movl	0x14(%ebx), %eax
  56634b:      	pushl	$0x40c                  # imm = 0x40C
  566350:      	pushl	%esi
  566351:      	movl	%eax, -0x28(%ebp)
  566354:      	calll	*%edi
  566356:      	cmpl	%eax, -0x28(%ebp)
  566359:      	jne	0x567785 <.text+0x166785>
  56635f:      	pushl	$0x0
  566361:      	pushl	0x8(%ebx)
  566364:      	pushl	$0x199                  # imm = 0x199
  566369:      	pushl	-0x28(%ebp)
  56636c:      	calll	*0x5ce558
  566372:      	pushl	%eax
  566373:      	movl	$0xc6fe68, %ecx         # imm = 0xC6FE68
  566378:      	calll	0x55887b <.text+0x15787b>
  56637d:      	movl	%eax, %esi
  56637f:      	movl	%esi, -0x28(%ebp)
  566382:      	testl	%esi, %esi
  566384:      	je	0x567785 <.text+0x166785>
  56638a:      	leal	-0x1c(%ebp), %eax
  56638d:      	pushl	%eax
  56638e:      	pushl	0x18(%ebx)
  566391:      	calll	*0x5ce084
  566397:      	movl	0x20(%ebx), %eax
  56639a:      	subl	-0x1c(%ebp), %eax
  56639d:      	addl	0x28(%ebx), %eax
  5663a0:      	cltd
  5663a1:      	subl	%edx, %eax
  5663a3:      	sarl	%eax
  5663a5:      	movl	%eax, -0x34(%ebp)
  5663a8:      	xorl	%eax, %eax
  5663aa:      	movb	0x37(%eax,%esi), %cl
  5663ae:      	andb	$0x7f, %cl
  5663b1:      	movb	%cl, 0x71c(%ebp,%eax)
  5663b8:      	incl	%eax
  5663b9:      	cmpl	$0xa, %eax
  5663bc:      	jl	0x5663aa <.text+0x1653aa>
  5663be:      	leal	0x71c(%ebp), %edi
  5663c4:      	movb	$0x0, 0x726(%ebp)
  5663cb:      	decl	%edi
  5663cc:      	movb	0x1(%edi), %al
  5663cf:      	incl	%edi
  5663d0:      	testb	%al, %al
  5663d2:      	jne	0x5663cc <.text+0x1653cc>
  5663d4:      	movl	$0x5eec1c, %esi         # imm = 0x5EEC1C
  5663d9:      	movsl	(%esi), %es:(%edi)
  5663da:      	leal	0x71c(%ebp), %eax
  5663e0:      	pushl	%eax
  5663e1:      	movsb	(%esi), %es:(%edi)
  5663e2:      	calll	0x4839c7 <.text+0x829c7>
  5663e7:      	popl	%ecx
  5663e8:      	testl	%eax, %eax
  5663ea:      	jne	0x5663f8 <.text+0x1653f8>
  5663ec:      	pushl	$0x64
  5663ee:      	movl	$0xff, -0x3c(%ebp)
  5663f5:      	popl	%esi
  5663f6:      	jmp	0x566433 <.text+0x165433>
  5663f8:      	movl	-0x28(%ebp), %eax
  5663fb:      	testb	$0x4, 0x15(%eax)
  5663ff:      	jne	0x56640f <.text+0x16540f>
  566401:      	movl	$0x969696, -0x3c(%ebp)  # imm = 0x969696
  566408:      	movl	$0x323232, %esi         # imm = 0x323232
  56640d:      	jmp	0x566433 <.text+0x165433>
  56640f:      	movw	0x13(%eax), %cx
  566413:      	cmpw	0x11(%eax), %cx
  566417:      	jl	0x566427 <.text+0x165427>
  566419:      	movl	$0x9600, -0x3c(%ebp)    # imm = 0x9600
  566420:      	movl	$0x2800, %esi           # imm = 0x2800
  566425:      	jmp	0x566433 <.text+0x165433>
  566427:      	movl	$0xff00, -0x3c(%ebp)    # imm = 0xFF00
  56642e:      	movl	$0x6400, %esi           # imm = 0x6400
  566433:      	testb	$0x1, 0x10(%ebx)
  566437:      	movl	0x1c(%ebx), %eax
  56643a:      	je	0x566487 <.text+0x165487>
  56643c:      	movl	%eax, -0x6c(%ebp)
  56643f:      	movl	0x20(%ebx), %eax
  566442:      	movl	%eax, -0x68(%ebp)
  566445:      	movl	0x24(%ebx), %eax
  566448:      	movl	%eax, -0x64(%ebp)
  56644b:      	movl	0x28(%ebx), %eax
  56644e:      	movl	%eax, -0x60(%ebp)
  566451:      	leal	-0x6c(%ebp), %eax
  566454:      	pushl	%eax
  566455:      	pushl	0x18(%ebx)
  566458:      	calll	*0x5ce524
  56645e:      	andl	$0x0, -0x48(%ebp)
  566462:      	andl	$0x0, -0x40(%ebp)
  566466:      	leal	-0x48(%ebp), %eax
  566469:      	pushl	%eax
  56646a:      	movl	%esi, -0x44(%ebp)
  56646d:      	calll	*0x5ce088
  566473:      	movl	%eax, %esi
  566475:      	pushl	%esi
  566476:      	leal	-0x6c(%ebp), %eax
  566479:      	pushl	%eax
  56647a:      	pushl	0x18(%ebx)
  56647d:      	calll	*0x5ce528
  566483:      	testl	%esi, %esi
  566485:      	jmp	0x5664c3 <.text+0x1654c3>
  566487:      	movl	%eax, -0x5c(%ebp)
  56648a:      	movl	0x20(%ebx), %eax
  56648d:      	movl	%eax, -0x58(%ebp)
  566490:      	movl	0x24(%ebx), %eax
  566493:      	movl	%eax, -0x54(%ebp)
  566496:      	movl	0x28(%ebx), %eax
  566499:      	movl	%eax, -0x50(%ebp)
  56649c:      	xorl	%edi, %edi
  56649e:      	leal	-0x48(%ebp), %eax
  5664a1:      	pushl	%eax
  5664a2:      	movl	%edi, -0x48(%ebp)
  5664a5:      	movl	%edi, -0x44(%ebp)
  5664a8:      	movl	%edi, -0x40(%ebp)
  5664ab:      	calll	*0x5ce088
  5664b1:      	movl	%eax, %esi
  5664b3:      	pushl	%esi
  5664b4:      	leal	-0x5c(%ebp), %eax
  5664b7:      	pushl	%eax
  5664b8:      	pushl	0x18(%ebx)
  5664bb:      	calll	*0x5ce528
  5664c1:      	cmpl	%edi, %esi
  5664c3:      	je	0x5664cc <.text+0x1654cc>
  5664c5:      	pushl	%esi
  5664c6:      	calll	*0x5ce054
  5664cc:      	movl	-0x28(%ebp), %eax
  5664cf:      	cmpb	$0x0, 0x41(%eax)
  5664d3:      	movl	0x5ce050, %esi
  5664d9:      	movl	$0xcc0020, %edi         # imm = 0xCC0020
  5664de:      	je	0x566535 <.text+0x165535>
  5664e0:      	pushl	0x18(%ebx)
  5664e3:      	calll	*0x5ce0d0
  5664e9:      	pushl	0xc702c8
  5664ef:      	movl	%eax, -0x38(%ebp)
  5664f2:      	pushl	%eax
  5664f3:      	calll	*%esi
  5664f5:      	movl	0x28(%ebx), %edx
  5664f8:      	movl	0x1c(%ebx), %ecx
  5664fb:      	pushl	%edi
  5664fc:      	pushl	$0x0
  5664fe:      	pushl	$0x0
  566500:      	pushl	-0x38(%ebp)
  566503:      	movl	%eax, -0x2c(%ebp)
  566506:      	movl	0x20(%ebx), %eax
  566509:      	subl	%eax, %edx
  56650b:      	subl	$0x3, %edx
  56650e:      	pushl	%edx
  56650f:      	movl	0x24(%ebx), %edx
  566512:      	subl	%ecx, %edx
  566514:      	decl	%edx
  566515:      	pushl	%edx
  566516:      	addl	$0x3, %eax
  566519:      	pushl	%eax
  56651a:      	pushl	%ecx
  56651b:      	pushl	0x18(%ebx)
  56651e:      	calll	*0x5ce08c
  566524:      	pushl	-0x2c(%ebp)
  566527:      	pushl	-0x38(%ebp)
  56652a:      	calll	*%esi
  56652c:      	pushl	-0x38(%ebp)
  56652f:      	calll	*0x5ce03c
  566535:      	xorl	%eax, %eax
  566537:      	movl	-0x28(%ebp), %ecx
  56653a:      	movb	0x37(%ecx,%eax), %cl
  56653e:      	andb	$0x7f, %cl
  566541:      	movb	%cl, 0x72c(%ebp,%eax)
  566548:      	incl	%eax
  566549:      	cmpl	$0xa, %eax
  56654c:      	jl	0x566537 <.text+0x165537>
  56654e:      	movl	0xc702cc, %ecx
  566554:      	leal	0x72c(%ebp), %eax
  56655a:      	pushl	%eax
  56655b:      	movb	$0x0, 0x736(%ebp)
  566562:      	calll	0x551d7c <.text+0x150d7c>
  566567:      	movl	%eax, -0x38(%ebp)
  56656a:      	testl	%eax, %eax
  56656c:      	jl	0x566615 <.text+0x165615>
  566572:      	pushl	0x18(%ebx)
  566575:      	calll	*0x5ce0d0
  56657b:      	pushl	-0x38(%ebp)
  56657e:      	movl	0xc702cc, %ecx
  566584:      	movl	%eax, -0x2c(%ebp)
  566587:      	calll	0x551cf8 <.text+0x150cf8>
  56658c:      	xorl	%ecx, %ecx
  56658e:      	movl	$0x633b00, %edx         # imm = 0x633B00
  566593:      	cmpb	(%edx), %al
  566595:      	je	0x5665a2 <.text+0x1655a2>
  566597:      	incl	%ecx
  566598:      	addl	$0x10, %edx
  56659b:      	cmpl	$0x5, %ecx
  56659e:      	jb	0x566593 <.text+0x165593>
  5665a0:      	jmp	0x5665b1 <.text+0x1655b1>
  5665a2:      	pushl	0xc702ac(,%ecx,4)
  5665a9:      	pushl	-0x2c(%ebp)
  5665ac:      	calll	*%esi
  5665ae:      	movl	%eax, -0x30(%ebp)
  5665b1:      	movl	0x20(%ebx), %eax
  5665b4:      	movl	0x28(%ebx), %edx
  5665b7:      	movl	0x1c(%ebx), %ecx
  5665ba:      	pushl	%edi
  5665bb:      	pushl	$0x0
  5665bd:      	pushl	$0x0
  5665bf:      	pushl	-0x2c(%ebp)
  5665c2:      	subl	%eax, %edx
  5665c4:      	subl	$0x3, %edx
  5665c7:      	pushl	%edx
  5665c8:      	movl	0x24(%ebx), %edx
  5665cb:      	subl	%ecx, %edx
  5665cd:      	subl	$0xb, %edx
  5665d0:      	pushl	%edx
  5665d1:      	addl	$0x3, %eax
  5665d4:      	pushl	%eax
  5665d5:      	addl	$0xb, %ecx
  5665d8:      	pushl	%ecx
  5665d9:      	pushl	0x18(%ebx)
  5665dc:      	calll	*0x5ce08c
  5665e2:      	pushl	-0x30(%ebp)
  5665e5:      	pushl	-0x2c(%ebp)
  5665e8:      	calll	*%esi
  5665ea:      	pushl	-0x2c(%ebp)
  5665ed:      	calll	*0x5ce03c
  5665f3:      	pushl	-0x38(%ebp)
  5665f6:      	movl	0xc702cc, %ecx
  5665fc:      	calll	0x5520d1 <.text+0x1510d1>
  566601:      	movl	-0x28(%ebp), %ecx
  566604:      	movswl	0x11(%ecx), %ecx
  566608:      	cmpl	%eax, %ecx
  56660a:      	jg	0x56660e <.text+0x16560e>
  56660c:      	movl	%ecx, %eax
  56660e:      	movl	-0x28(%ebp), %ecx
  566611:      	movw	%ax, 0x11(%ecx)
  566615:      	movl	0x20(%ebx), %eax
  566618:      	pushl	-0x3c(%ebp)
  56661b:      	movl	%eax, -0x78(%ebp)
  56661e:      	movl	0x28(%ebx), %eax
  566621:      	pushl	0x18(%ebx)
  566624:      	movl	$0x16, -0x7c(%ebp)
  56662b:      	movl	$0x8a, -0x74(%ebp)
  566632:      	movl	%eax, -0x70(%ebp)
  566635:      	calll	*0x5ce04c
  56663b:      	pushl	0x18(%ebx)
  56663e:      	calll	*0x5ce098
  566644:      	movl	0x5ce09c, %edi
  56664a:      	pushl	$0x0
  56664c:      	pushl	0x18(%ebx)
  56664f:      	movl	%eax, -0x30(%ebp)
  566652:      	calll	*%edi
  566654:      	movl	-0x28(%ebp), %esi
  566657:      	addl	$0x17, %esi
  56665a:      	movl	%esi, %eax
  56665c:      	leal	0x1(%eax), %ecx
  56665f:      	movb	(%eax), %dl
  566661:      	incl	%eax
  566662:      	testb	%dl, %dl
  566664:      	jne	0x56665f <.text+0x16565f>
  566666:      	pushl	$0x0
  566668:      	subl	%ecx, %eax
  56666a:      	pushl	%eax
  56666b:      	pushl	%esi
  56666c:      	leal	-0x7c(%ebp), %eax
  56666f:      	pushl	%eax
  566670:      	pushl	$0x4
  566672:      	pushl	-0x34(%ebp)
  566675:      	pushl	$0x16
  566677:      	pushl	0x18(%ebx)
  56667a:      	calll	*0x5ce094
  566680:      	pushl	$0x2
  566682:      	pushl	0x18(%ebx)
  566685:      	calll	*%edi
  566687:      	movl	-0x28(%ebp), %eax
  56668a:      	movswl	0x13(%eax), %eax
  56668e:      	pushl	%eax
  56668f:      	movl	$0x5df2a4, %esi         # imm = 0x5DF2A4
  566694:      	leal	0x6b8(%ebp), %eax
  56669a:      	pushl	%esi
  56669b:      	pushl	%eax
  56669c:      	calll	*0x5ce49c
  5666a2:      	leal	0x6b8(%ebp), %eax
  5666a8:      	addl	$0xc, %esp
  5666ab:      	leal	0x1(%eax), %ecx
  5666ae:      	movb	(%eax), %dl
  5666b0:      	incl	%eax
  5666b1:      	testb	%dl, %dl
  5666b3:      	jne	0x5666ae <.text+0x1656ae>
  5666b5:      	subl	%ecx, %eax
  5666b7:      	pushl	%eax
  5666b8:      	leal	0x6b8(%ebp), %eax
  5666be:      	pushl	%eax
  5666bf:      	pushl	-0x34(%ebp)
  5666c2:      	pushl	$0x8e
  5666c7:      	pushl	0x18(%ebx)
  5666ca:      	calll	*0x5ce0a8
  5666d0:      	movl	-0x28(%ebp), %eax
  5666d3:      	movswl	0x11(%eax), %eax
  5666d7:      	pushl	%eax
  5666d8:      	leal	0x6b8(%ebp), %eax
  5666de:      	pushl	%esi
  5666df:      	pushl	%eax
  5666e0:      	calll	*0x5ce49c
  5666e6:      	leal	0x6b8(%ebp), %eax
  5666ec:      	addl	$0xc, %esp
  5666ef:      	leal	0x1(%eax), %esi
  5666f2:      	movb	(%eax), %cl
  5666f4:      	incl	%eax
  5666f5:      	testb	%cl, %cl
  5666f7:      	jne	0x5666f2 <.text+0x1656f2>
  5666f9:      	subl	%esi, %eax
  5666fb:      	pushl	%eax
  5666fc:      	leal	0x6b8(%ebp), %eax
  566702:      	pushl	%eax
  566703:      	pushl	-0x34(%ebp)
  566706:      	pushl	$0x9c
  56670b:      	pushl	0x18(%ebx)
  56670e:      	calll	*0x5ce0a8
  566714:      	pushl	-0x30(%ebp)
  566717:      	pushl	0x18(%ebx)
  56671a:      	calll	*%edi
  56671c:      	jmp	0x567785 <.text+0x166785>
  566721:      	subl	$0x2c, %ecx
  566724:      	je	0x567657 <.text+0x166657>
  56672a:      	subl	$0xe4, %ecx
  566730:      	je	0x566824 <.text+0x165824>
  566736:      	decl	%ecx
  566737:      	jne	0x567650 <.text+0x166650>
  56673d:      	movzwl	%di, %eax
  566740:      	decl	%eax
  566741:      	je	0x5667ef <.text+0x1657ef>
  566747:      	subl	$0x40b, %eax            # imm = 0x40B
  56674c:      	je	0x5667de <.text+0x1657de>
  566752:      	subl	$0x2a, %eax
  566755:      	je	0x5667b7 <.text+0x1657b7>
  566757:      	decl	%eax
  566758:      	je	0x5667a6 <.text+0x1657a6>
  56675a:      	subl	$0x3d9, %eax            # imm = 0x3D9
  56675f:      	jne	0x567650 <.text+0x166650>
  566765:      	shrl	$0x10, %edi
  566768:      	decl	%edi
  566769:      	jne	0x567650 <.text+0x166650>
  56676f:      	xorl	%ebx, %ebx
  566771:      	incl	%ebx
  566772:      	cmpl	%edi, 0xc6fda4
  566778:      	jne	0x56679f <.text+0x16579f>
  56677a:      	pushl	%edi
  56677b:      	movl	0x5ce530, %edi
  566781:      	pushl	%esi
  566782:      	calll	*%edi
  566784:      	andl	$0x0, 0xc702a8
  56678b:      	movl	$0xc6fe28, %ecx         # imm = 0xC6FE28
  566790:      	calll	0x55afc7 <.text+0x159fc7>
  566795:      	pushl	%ebx
  566796:      	pushl	%esi
  566797:      	calll	*%edi
  566799:      	movl	%ebx, 0xc702a8
  56679f:      	movl	%ebx, %eax
  5667a1:      	jmp	0x568fe4 <.text+0x167fe4>
  5667a6:      	shrl	$0x10, %edi
  5667a9:      	decl	%edi
  5667aa:      	jne	0x567650 <.text+0x166650>
  5667b0:      	movl	0xc6fdf8, %eax
  5667b5:      	jmp	0x5667c6 <.text+0x1657c6>
  5667b7:      	shrl	$0x10, %edi
  5667ba:      	decl	%edi
  5667bb:      	jne	0x567650 <.text+0x166650>
  5667c1:      	movl	0xc6feb4, %eax
  5667c6:      	testl	%eax, %eax
  5667c8:      	je	0x567785 <.text+0x166785>
  5667ce:      	pushl	$0x1
  5667d0:      	pushl	$0x0
  5667d2:      	pushl	%eax
  5667d3:      	calll	*0x5ce550
  5667d9:      	jmp	0x567785 <.text+0x166785>
  5667de:      	shrl	$0x10, %edi
  5667e1:      	xorl	%eax, %eax
  5667e3:      	decl	%edi
  5667e4:      	jne	0x568fe4 <.text+0x167fe4>
  5667ea:      	jmp	0x567787 <.text+0x166787>
  5667ef:      	movzwl	0x62aea4, %eax
  5667f6:      	pushl	$0xc6fdec               # imm = 0xC6FDEC
  5667fb:      	pushl	$0xc6f870               # imm = 0xC6F870
  566800:      	pushl	%eax
  566801:      	pushl	0xba7724
  566807:      	pushl	$0x3fd                  # imm = 0x3FD
  56680c:      	pushl	%esi
  56680d:      	calll	*0x5ce53c
  566813:      	movl	$0xc6f4a8, %edx         # imm = 0xC6F4A8
  566818:      	movl	%eax, %ecx
  56681a:      	calll	0x559a14 <.text+0x158a14>
  56681f:      	jmp	0x5689c2 <.text+0x1679c2>
  566824:      	pushl	%esi
  566825:      	calll	0x572080 <.text+0x171080>
  56682a:      	movl	$0x5f0da8, (%esp)       # imm = 0x5F0DA8
  566831:      	pushl	%esi
  566832:      	movl	$0x1, 0xc702a8
  56683c:      	movb	$0x0, 0xc6fca6
  566843:      	movb	$0x0, 0xc6f86f
  56684a:      	movb	$0x0, 0xc6f4b7
  566851:      	calll	0x571f12 <.text+0x170f12>
  566856:      	pushl	$0x5f06b0               # imm = 0x5F06B0
  56685b:      	pushl	%esi
  56685c:      	movl	%eax, 0xc702c8
  566861:      	calll	0x571f12 <.text+0x170f12>
  566866:      	pushl	$0x5f06a4               # imm = 0x5F06A4
  56686b:      	pushl	%esi
  56686c:      	movl	%eax, 0xc702c4
  566871:      	calll	0x571f12 <.text+0x170f12>
  566876:      	addl	$0x18, %esp
  566879:      	movl	%eax, 0xc702c0
  56687e:      	movl	$0xc702ac, %ebx         # imm = 0xC702AC
  566883:      	xorl	%edi, %edi
  566885:      	pushl	0x633b04(%edi)
  56688b:      	pushl	%esi
  56688c:      	calll	0x571f12 <.text+0x170f12>
  566891:      	popl	%ecx
  566892:      	popl	%ecx
  566893:      	movl	%eax, (%ebx)
  566895:      	testl	%eax, %eax
  566897:      	jne	0x5668a9 <.text+0x1658a9>
  566899:      	pushl	0x633b08(%edi)
  56689f:      	pushl	%esi
  5668a0:      	calll	0x571f12 <.text+0x170f12>
  5668a5:      	popl	%ecx
  5668a6:      	popl	%ecx
  5668a7:      	movl	%eax, (%ebx)
  5668a9:      	addl	$0x10, %edi
  5668ac:      	addl	$0x4, %ebx
  5668af:      	cmpl	$0x50, %edi
  5668b2:      	jb	0x566885 <.text+0x165885>
  5668b4:      	calll	0x582000 <.text+0x181000>
  5668b9:      	andl	$0x0, 0xc6fda4
  5668c0:      	addl	$0xbb8, %eax            # imm = 0xBB8
  5668c5:      	movl	$0xc6fdec, %edi         # imm = 0xC6FDEC
  5668ca:      	movl	%edi, %ecx
  5668cc:      	movl	%eax, 0xc6f4c4
  5668d1:      	movb	$0x0, 0xc6fda9
  5668d8:      	movl	$0xc9, 0xc6fd2c
  5668e2:      	movl	$0x4, 0xc6fd28
  5668ec:      	calll	0x55b669 <.text+0x15a669>
  5668f1:      	movl	%edi, %ecx
  5668f3:      	calll	0x55934a <.text+0x15834a>
  5668f8:      	movl	0x5ce53c, %ebx
  5668fe:      	pushl	$0x5594ac               # imm = 0x5594AC
  566903:      	pushl	$0xc6f4a8               # imm = 0xC6F4A8
  566908:      	pushl	$0x3fc                  # imm = 0x3FC
  56690d:      	pushl	%esi
  56690e:      	calll	*%ebx
  566910:      	pushl	%eax
  566911:      	pushl	0xba7724
  566917:      	pushl	$0x437                  # imm = 0x437
  56691c:      	pushl	%esi
  56691d:      	calll	*%ebx
  56691f:      	pushl	%eax
  566920:      	movl	%edi, %ecx
  566922:      	calll	0x550bd0 <.text+0x14fbd0>
  566927:      	movl	$0xc6fea8, %edi         # imm = 0xC6FEA8
  56692c:      	movl	%edi, %ecx
  56692e:      	calll	0x55b669 <.text+0x15a669>
  566933:      	movl	%edi, %ecx
  566935:      	calll	0x55934a <.text+0x15834a>
  56693a:      	pushl	$0x0
  56693c:      	pushl	$0xc6f4a8               # imm = 0xC6F4A8
  566941:      	pushl	$0x3fc                  # imm = 0x3FC
  566946:      	pushl	%esi
  566947:      	calll	*%ebx
  566949:      	pushl	%eax
  56694a:      	pushl	0xba7724
  566950:      	pushl	$0x436                  # imm = 0x436
  566955:      	pushl	%esi
  566956:      	calll	*%ebx
  566958:      	pushl	%eax
  566959:      	movl	%edi, %ecx
  56695b:      	calll	0x550bd0 <.text+0x14fbd0>
  566960:      	pushl	%esi
  566961:      	movl	$0x3fd, %edi            # imm = 0x3FD
  566966:      	pushl	%edi
  566967:      	pushl	%esi
  566968:      	calll	*%ebx
  56696a:      	pushl	%eax
  56696b:      	pushl	0xba7724
  566971:      	pushl	$0x40c                  # imm = 0x40C
  566976:      	pushl	%esi
  566977:      	calll	*%ebx
  566979:      	pushl	%eax
  56697a:      	movl	$0xc6fe68, %ecx         # imm = 0xC6FE68
  56697f:      	calll	0x55b3ba <.text+0x15a3ba>
  566984:      	pushl	%esi
  566985:      	pushl	%edi
  566986:      	pushl	%esi
  566987:      	calll	*%ebx
  566989:      	pushl	%eax
  56698a:      	pushl	0xba7724
  566990:      	movl	$0x810, %edi            # imm = 0x810
  566995:      	pushl	%edi
  566996:      	pushl	%esi
  566997:      	calll	*%ebx
  566999:      	pushl	%eax
  56699a:      	movl	$0xc6fe28, %ecx         # imm = 0xC6FE28
  56699f:      	calll	0x55b3ba <.text+0x15a3ba>
  5669a4:      	pushl	$0x3fc                  # imm = 0x3FC
  5669a9:      	pushl	%esi
  5669aa:      	calll	*%ebx
  5669ac:      	pushl	%eax
  5669ad:      	movl	$0xc6f4a8, %ecx         # imm = 0xC6F4A8
  5669b2:      	calll	0x5503a3 <.text+0x14f3a3>
  5669b7:      	pushl	%esi
  5669b8:      	calll	0x56ea7b <.text+0x16da7b>
  5669bd:      	pushl	%esi
  5669be:      	calll	0x56eaea <.text+0x16daea>
  5669c3:      	popl	%ecx
  5669c4:      	popl	%ecx
  5669c5:      	pushl	$0x1
  5669c7:      	pushl	$0x7a
  5669c9:      	pushl	$0xa1
  5669ce:      	pushl	$0x3b
  5669d0:      	pushl	$0x20
  5669d2:      	pushl	%edi
  5669d3:      	pushl	%esi
  5669d4:      	calll	*%ebx
  5669d6:      	movl	0x5ce548, %edi
  5669dc:      	pushl	%eax
  5669dd:      	calll	*%edi
  5669df:      	pushl	$0x1
  5669e1:      	pushl	$0x9b
  5669e6:      	pushl	$0xa1
  5669eb:      	pushl	$0x3b
  5669ed:      	pushl	$0x1c1                  # imm = 0x1C1
  5669f2:      	pushl	$0x40c                  # imm = 0x40C
  5669f7:      	pushl	%esi
  5669f8:      	calll	*%ebx
  5669fa:      	pushl	%eax
  5669fb:      	calll	*%edi
  5669fd:      	pushl	$0x1
  5669ff:      	pushl	$0x64
  566a01:      	pushl	$0xa1
  566a06:      	pushl	$0x12b                  # imm = 0x12B
  566a0b:      	pushl	$0x20
  566a0d:      	pushl	$0x437                  # imm = 0x437
  566a12:      	pushl	%esi
  566a13:      	calll	*%ebx
  566a15:      	pushl	%eax
  566a16:      	calll	*%edi
  566a18:      	pushl	$0x1
  566a1a:      	pushl	$0x7a
  566a1c:      	pushl	$0xa1
  566a21:      	pushl	$0x118                  # imm = 0x118
  566a26:      	pushl	$0x1c1                  # imm = 0x1C1
  566a2b:      	pushl	$0x436                  # imm = 0x436
  566a30:      	pushl	%esi
  566a31:      	calll	*%ebx
  566a33:      	pushl	%eax
  566a34:      	calll	*%edi
  566a36:      	pushl	$0x1
  566a38:      	pushl	$0x15b                  # imm = 0x15B
  566a3d:      	pushl	$0xd6
  566a42:      	pushl	$0x3b
  566a44:      	pushl	$0xcd
  566a49:      	pushl	$0x3fc                  # imm = 0x3FC
  566a4e:      	pushl	%esi
  566a4f:      	calll	*%ebx
  566a51:      	pushl	%eax
  566a52:      	calll	*%edi
  566a54:      	pushl	$0x1
  566a56:      	pushl	$0x10
  566a58:      	pushl	$0xea
  566a5d:      	pushl	$0x1a5                  # imm = 0x1A5
  566a62:      	pushl	$0xcf
  566a67:      	pushl	$0x3fd                  # imm = 0x3FD
  566a6c:      	pushl	%esi
  566a6d:      	calll	*%ebx
  566a6f:      	pushl	%eax
  566a70:      	calll	*%edi
  566a72:      	pushl	$0x0
  566a74:      	pushl	$0xf1
  566a79:      	pushl	$0xc5
  566a7e:      	pushl	$0x3fd                  # imm = 0x3FD
  566a83:      	pushl	%esi
  566a84:      	calll	*0x5ce52c
  566a8a:      	pushl	$0x5ef8b8               # imm = 0x5EF8B8
  566a8f:      	calll	0x546add <.text+0x145add>
  566a94:      	pushl	$0x0
  566a96:      	calll	0x546d17 <.text+0x145d17>
  566a9b:      	movl	%eax, -0x30(%ebp)
  566a9e:      	calll	0x546ac4 <.text+0x145ac4>
  566aa3:      	pushl	$0x5d2afc               # imm = 0x5D2AFC
  566aa8:      	leal	-0x24(%ebp), %eax
  566aab:      	pushl	$0x5ef8c8               # imm = 0x5EF8C8
  566ab0:      	pushl	%eax
  566ab1:      	calll	*0x5ce49c
  566ab7:      	pushl	$0x128                  # imm = 0x128
  566abc:      	calll	0x5c6d12 <.text+0x1c5d12>
  566ac1:      	addl	$0x18, %esp
  566ac4:      	testl	%eax, %eax
  566ac6:      	je	0x566aec <.text+0x165aec>
  566ac8:      	xorl	%edi, %edi
  566aca:      	pushl	%edi
  566acb:      	pushl	$0xc
  566acd:      	pushl	$0xa0
  566ad2:      	pushl	$0x4
  566ad4:      	pushl	$0xf0
  566ad9:      	leal	-0x24(%ebp), %ecx
  566adc:      	pushl	%ecx
  566add:      	pushl	%esi
  566ade:      	movl	%eax, %ecx
  566ae0:      	calll	0x572841 <.text+0x171841>
  566ae5:      	movl	%eax, 0xc702fc
  566aea:      	jmp	0x566af5 <.text+0x165af5>
  566aec:      	andl	$0x0, 0xc702fc
  566af3:      	xorl	%edi, %edi
  566af5:      	pushl	-0x30(%ebp)
  566af8:      	leal	-0x24(%ebp), %eax
  566afb:      	pushl	$0x5ef8a8               # imm = 0x5EF8A8
  566b00:      	pushl	%eax
  566b01:      	calll	*0x5ce49c
  566b07:      	pushl	$0x128                  # imm = 0x128
  566b0c:      	calll	0x5c6d12 <.text+0x1c5d12>
  566b11:      	addl	$0x10, %esp
  566b14:      	cmpl	%edi, %eax
  566b16:      	je	0x566b3a <.text+0x165b3a>
  566b18:      	pushl	%edi
  566b19:      	pushl	$0xc
  566b1b:      	pushl	$0xa0
  566b20:      	pushl	$0x10
  566b22:      	pushl	$0xf0
  566b27:      	leal	-0x24(%ebp), %ecx
  566b2a:      	pushl	%ecx
  566b2b:      	pushl	%esi
  566b2c:      	movl	%eax, %ecx
  566b2e:      	calll	0x572841 <.text+0x171841>
  566b33:      	movl	%eax, 0xc702f8
  566b38:      	jmp	0x566b40 <.text+0x165b40>
  566b3a:      	movl	%edi, 0xc702f8
  566b40:      	pushl	$0x128                  # imm = 0x128
  566b45:      	calll	0x5c6d12 <.text+0x1c5d12>
  566b4a:      	popl	%ecx
  566b4b:      	cmpl	%edi, %eax
  566b4d:      	je	0x566b6a <.text+0x165b6a>
  566b4f:      	pushl	%edi
  566b50:      	pushl	$0x16
  566b52:      	pushl	$0x41
  566b54:      	pushl	$0x116                  # imm = 0x116
  566b59:      	pushl	$0x20
  566b5b:      	pushl	$0x5e655c               # imm = 0x5E655C
  566b60:      	pushl	%esi
  566b61:      	movl	%eax, %ecx
  566b63:      	calll	0x572841 <.text+0x171841>
  566b68:      	jmp	0x566b6c <.text+0x165b6c>
  566b6a:      	xorl	%eax, %eax
  566b6c:      	pushl	0x633b90
  566b72:      	movl	%eax, %ecx
  566b74:      	pushl	$0x633b50               # imm = 0x633B50
  566b79:      	movl	%eax, 0xc702f4
  566b7e:      	calll	0x571b60 <.text+0x170b60>
  566b83:      	pushl	$0x128                  # imm = 0x128
  566b88:      	calll	0x5c6d12 <.text+0x1c5d12>
  566b8d:      	popl	%ecx
  566b8e:      	cmpl	%edi, %eax
  566b90:      	je	0x566bb0 <.text+0x165bb0>
  566b92:      	pushl	%edi
  566b93:      	pushl	$0x16
  566b95:      	pushl	$0x14
  566b97:      	pushl	$0x116                  # imm = 0x116
  566b9c:      	pushl	$0x91
  566ba1:      	pushl	$0x5e6534               # imm = 0x5E6534
  566ba6:      	pushl	%esi
  566ba7:      	movl	%eax, %ecx
  566ba9:      	calll	0x572841 <.text+0x171841>
  566bae:      	jmp	0x566bb2 <.text+0x165bb2>
  566bb0:      	xorl	%eax, %eax
  566bb2:      	pushl	0x633b90
  566bb8:      	movl	%eax, %ecx
  566bba:      	pushl	$0x633b50               # imm = 0x633B50
  566bbf:      	movl	%eax, 0xc702f0
  566bc4:      	calll	0x571b60 <.text+0x170b60>
  566bc9:      	pushl	$0x128                  # imm = 0x128
  566bce:      	calll	0x5c6d12 <.text+0x1c5d12>
  566bd3:      	popl	%ecx
  566bd4:      	cmpl	%edi, %eax
  566bd6:      	je	0x566bf6 <.text+0x165bf6>
  566bd8:      	pushl	%edi
  566bd9:      	pushl	$0x16
  566bdb:      	pushl	$0x1e
  566bdd:      	pushl	$0x116                  # imm = 0x116
  566be2:      	pushl	$0xa5
  566be7:      	pushl	$0x5f0624               # imm = 0x5F0624
  566bec:      	pushl	%esi
  566bed:      	movl	%eax, %ecx
  566bef:      	calll	0x572841 <.text+0x171841>
  566bf4:      	jmp	0x566bf8 <.text+0x165bf8>
  566bf6:      	xorl	%eax, %eax
  566bf8:      	pushl	0x633b90
  566bfe:      	movl	%eax, %ecx
  566c00:      	pushl	$0x633b50               # imm = 0x633B50
  566c05:      	movl	%eax, 0xc702ec
  566c0a:      	calll	0x571b60 <.text+0x170b60>
  566c0f:      	pushl	$0x128                  # imm = 0x128
  566c14:      	calll	0x5c6d12 <.text+0x1c5d12>
  566c19:      	popl	%ecx
  566c1a:      	cmpl	%edi, %eax
  566c1c:      	je	0x566c3e <.text+0x165c3e>
  566c1e:      	pushl	%edi
  566c1f:      	pushl	$0xd
  566c21:      	pushl	$0x87
  566c26:      	pushl	$0x29
  566c28:      	pushl	$0x2d
  566c2a:      	pushl	$0x5f0da0               # imm = 0x5F0DA0
  566c2f:      	pushl	%esi
  566c30:      	movl	%eax, %ecx
  566c32:      	calll	0x572841 <.text+0x171841>
  566c37:      	movl	%eax, 0xc702e8
  566c3c:      	jmp	0x566c44 <.text+0x165c44>
  566c3e:      	movl	%edi, 0xc702e8
  566c44:      	pushl	$0x128                  # imm = 0x128
  566c49:      	calll	0x5c6d12 <.text+0x1c5d12>
  566c4e:      	popl	%ecx
  566c4f:      	cmpl	%edi, %eax
  566c51:      	je	0x566c76 <.text+0x165c76>
  566c53:      	pushl	%edi
  566c54:      	pushl	$0xd
  566c56:      	pushl	$0x87
  566c5b:      	pushl	$0x106                  # imm = 0x106
  566c60:      	pushl	$0x2d
  566c62:      	pushl	$0x5f0d90               # imm = 0x5F0D90
  566c67:      	pushl	%esi
  566c68:      	movl	%eax, %ecx
  566c6a:      	calll	0x572841 <.text+0x171841>
  566c6f:      	movl	%eax, 0xc702e4
  566c74:      	jmp	0x566c7c <.text+0x165c7c>
  566c76:      	movl	%edi, 0xc702e4
  566c7c:      	pushl	$0x128                  # imm = 0x128
  566c81:      	calll	0x5c6d12 <.text+0x1c5d12>
  566c86:      	popl	%ecx
  566c87:      	cmpl	%edi, %eax
  566c89:      	je	0x566cae <.text+0x165cae>
  566c8b:      	pushl	%edi
  566c8c:      	pushl	$0xd
  566c8e:      	pushl	$0xd4
  566c93:      	pushl	$0x29
  566c95:      	pushl	$0xd7
  566c9a:      	pushl	$0x5ef36c               # imm = 0x5EF36C
  566c9f:      	pushl	%esi
  566ca0:      	movl	%eax, %ecx
  566ca2:      	calll	0x572841 <.text+0x171841>
  566ca7:      	movl	%eax, 0xc702e0
  566cac:      	jmp	0x566cb4 <.text+0x165cb4>
  566cae:      	movl	%edi, 0xc702e0
  566cb4:      	pushl	$0x128                  # imm = 0x128
  566cb9:      	calll	0x5c6d12 <.text+0x1c5d12>
  566cbe:      	popl	%ecx
  566cbf:      	cmpl	%edi, %eax
  566cc1:      	je	0x566ce6 <.text+0x165ce6>
  566cc3:      	pushl	%edi
  566cc4:      	pushl	$0xd
  566cc6:      	pushl	$0x87
  566ccb:      	pushl	$0x29
  566ccd:      	pushl	$0x1cf                  # imm = 0x1CF
  566cd2:      	pushl	$0x5f0d88               # imm = 0x5F0D88
  566cd7:      	pushl	%esi
  566cd8:      	movl	%eax, %ecx
  566cda:      	calll	0x572841 <.text+0x171841>
  566cdf:      	movl	%eax, 0xc702dc
  566ce4:      	jmp	0x566cec <.text+0x165cec>
  566ce6:      	movl	%edi, 0xc702dc
  566cec:      	pushl	$0x128                  # imm = 0x128
  566cf1:      	calll	0x5c6d12 <.text+0x1c5d12>
  566cf6:      	popl	%ecx
  566cf7:      	cmpl	%edi, %eax
  566cf9:      	je	0x566d21 <.text+0x165d21>
  566cfb:      	pushl	%edi
  566cfc:      	pushl	$0xd
  566cfe:      	pushl	$0x87
  566d03:      	pushl	$0x106                  # imm = 0x106
  566d08:      	pushl	$0x1cf                  # imm = 0x1CF
  566d0d:      	pushl	$0x5f0d78               # imm = 0x5F0D78
  566d12:      	pushl	%esi
  566d13:      	movl	%eax, %ecx
  566d15:      	calll	0x572841 <.text+0x171841>
  566d1a:      	movl	%eax, 0xc702d8
  566d1f:      	jmp	0x566d27 <.text+0x165d27>
  566d21:      	movl	%edi, 0xc702d8
  566d27:      	pushl	$0x20
  566d29:      	calll	0x5c6d12 <.text+0x1c5d12>
  566d2e:      	popl	%ecx
  566d2f:      	cmpl	%edi, %eax
  566d31:      	je	0x566d43 <.text+0x165d43>
  566d33:      	pushl	%edi
  566d34:      	pushl	%edi
  566d35:      	pushl	$0x5f0d64               # imm = 0x5F0D64
  566d3a:      	movl	%eax, %ecx
  566d3c:      	calll	0x56f633 <.text+0x16e633>
  566d41:      	jmp	0x566d45 <.text+0x165d45>
  566d43:      	xorl	%eax, %eax
  566d45:      	pushl	%eax
  566d46:      	pushl	%esi
  566d47:      	movl	%eax, 0xc70354
  566d4c:      	calll	0x570cce <.text+0x16fcce>
  566d51:      	pushl	$0x110                  # imm = 0x110
  566d56:      	calll	0x5c6d12 <.text+0x1c5d12>
  566d5b:      	addl	$0xc, %esp
  566d5e:      	cmpl	%edi, %eax
  566d60:      	je	0x566d97 <.text+0x165d97>
  566d62:      	pushl	$0x5f0844               # imm = 0x5F0844
  566d67:      	pushl	$0x1
  566d69:      	pushl	$0x22
  566d6b:      	pushl	$0x98
  566d70:      	pushl	%edi
  566d71:      	pushl	$0x1
  566d73:      	pushl	$0x104                  # imm = 0x104
  566d78:      	pushl	$0x102                  # imm = 0x102
  566d7d:      	pushl	$0x103                  # imm = 0x103
  566d82:      	pushl	0xc6f4bc
  566d88:      	movl	%eax, %ecx
  566d8a:      	pushl	%esi
  566d8b:      	calll	0x5715a0 <.text+0x1705a0>
  566d90:      	movl	%eax, 0xc70350
  566d95:      	jmp	0x566d9d <.text+0x165d9d>
  566d97:      	movl	%edi, 0xc70350
  566d9d:      	pushl	$0x110                  # imm = 0x110
  566da2:      	calll	0x5c6d12 <.text+0x1c5d12>
  566da7:      	popl	%ecx
  566da8:      	cmpl	%edi, %eax
  566daa:      	je	0x566de2 <.text+0x165de2>
  566dac:      	pushl	$0x5f083c               # imm = 0x5F083C
  566db1:      	pushl	$0x1
  566db3:      	pushl	$0x22
  566db5:      	movl	$0xc7, %edx
  566dba:      	pushl	%edx
  566dbb:      	pushl	$0x1bd                  # imm = 0x1BD
  566dc0:      	pushl	$0x1
  566dc2:      	pushl	$0xc8
  566dc7:      	pushl	$0xc6
  566dcc:      	pushl	%edx
  566dcd:      	pushl	0xc6f4bc
  566dd3:      	movl	%eax, %ecx
  566dd5:      	pushl	%esi
  566dd6:      	calll	0x5715a0 <.text+0x1705a0>
  566ddb:      	movl	%eax, 0xc70348
  566de0:      	jmp	0x566de8 <.text+0x165de8>
  566de2:      	movl	%edi, 0xc70348
  566de8:      	pushl	$0x110                  # imm = 0x110
  566ded:      	calll	0x5c6d12 <.text+0x1c5d12>
  566df2:      	popl	%ecx
  566df3:      	cmpl	%edi, %eax
  566df5:      	je	0x566e2f <.text+0x165e2f>
  566df7:      	pushl	$0x5f0d58               # imm = 0x5F0D58
  566dfc:      	pushl	$0x1
  566dfe:      	pushl	$0x22
  566e00:      	pushl	$0x98
  566e05:      	pushl	%edi
  566e06:      	pushl	$0x1e8                  # imm = 0x1E8
  566e0b:      	pushl	$0xcb
  566e10:      	pushl	$0xc9
  566e15:      	pushl	$0xca
  566e1a:      	pushl	0xc6f4bc
  566e20:      	movl	%eax, %ecx
  566e22:      	pushl	%esi
  566e23:      	calll	0x5715a0 <.text+0x1705a0>
  566e28:      	movl	%eax, 0xc7034c
  566e2d:      	jmp	0x566e35 <.text+0x165e35>
  566e2f:      	movl	%edi, 0xc7034c
  566e35:      	pushl	$0x110                  # imm = 0x110
  566e3a:      	calll	0x5c6d12 <.text+0x1c5d12>
  566e3f:      	popl	%ecx
  566e40:      	cmpl	%edi, %eax
  566e42:      	je	0x566e7b <.text+0x165e7b>
  566e44:      	pushl	$0x5f0d4c               # imm = 0x5F0D4C
  566e49:      	pushl	$0x1
  566e4b:      	pushl	$0x22
  566e4d:      	pushl	$0xc7
  566e52:      	pushl	$0x1bd                  # imm = 0x1BD
  566e57:      	pushl	$0x1b9                  # imm = 0x1B9
  566e5c:      	pushl	$0xc5
  566e61:      	pushl	$0xc3
  566e66:      	pushl	$0xc4
  566e6b:      	pushl	0xc6f4bc
  566e71:      	movl	%eax, %ecx
  566e73:      	pushl	%esi
  566e74:      	calll	0x5715a0 <.text+0x1705a0>
  566e79:      	jmp	0x566e7d <.text+0x165e7d>
  566e7b:      	xorl	%eax, %eax
  566e7d:      	pushl	$0x17
  566e7f:      	pushl	$0x58
  566e81:      	pushl	$0x1c4                  # imm = 0x1C4
  566e86:      	pushl	$0x1fb                  # imm = 0x1FB
  566e8b:      	movl	%eax, %ecx
  566e8d:      	movl	%eax, 0xc70344
  566e92:      	calll	0x5724d7 <.text+0x1714d7>
  566e97:      	movl	0xc70350, %ecx
  566e9d:      	pushl	$0x17
  566e9f:      	pushl	$0x58
  566ea1:      	pushl	$0x4
  566ea3:      	pushl	$0x2f
  566ea5:      	calll	0x5724d7 <.text+0x1714d7>
  566eaa:      	movl	0xc70348, %ecx
  566eb0:      	pushl	$0x17
  566eb2:      	pushl	$0x58
  566eb4:      	pushl	$0x1c6                  # imm = 0x1C6
  566eb9:      	pushl	$0x2f
  566ebb:      	calll	0x5724d7 <.text+0x1714d7>
  566ec0:      	movl	0xc7034c, %ecx
  566ec6:      	pushl	$0x17
  566ec8:      	pushl	$0x58
  566eca:      	pushl	$0x4
  566ecc:      	pushl	$0x1fb                  # imm = 0x1FB
  566ed1:      	calll	0x5724d7 <.text+0x1714d7>
  566ed6:      	pushl	$0x110                  # imm = 0x110
  566edb:      	calll	0x5c6d12 <.text+0x1c5d12>
  566ee0:      	popl	%ecx
  566ee1:      	cmpl	%edi, %eax
  566ee3:      	je	0x566f15 <.text+0x165f15>
  566ee5:      	pushl	$0x5f0d40               # imm = 0x5F0D40
  566eea:      	pushl	$0x1
  566eec:      	pushl	$0x1a
  566eee:      	pushl	$0xa5
  566ef3:      	pushl	$0xe2
  566ef8:      	pushl	$0x1e
  566efa:      	pushl	$0x806                  # imm = 0x806
  566eff:      	pushl	$0x805                  # imm = 0x805
  566f04:      	pushl	%edi
  566f05:      	pushl	0xc6f4bc
  566f0b:      	movl	%eax, %ecx
  566f0d:      	pushl	%esi
  566f0e:      	calll	0x5715a0 <.text+0x1705a0>
  566f13:      	jmp	0x566f17 <.text+0x165f17>
  566f15:      	xorl	%eax, %eax
  566f17:      	pushl	$0x5f0828               # imm = 0x5F0828
  566f1c:      	pushl	$0x5f081c               # imm = 0x5F081C
  566f21:      	movl	%eax, %ecx
  566f23:      	movl	%eax, 0xc70328
  566f28:      	calll	0x56f4cb <.text+0x16e4cb>
  566f2d:      	pushl	$0x110                  # imm = 0x110
  566f32:      	calll	0x5c6d12 <.text+0x1c5d12>
  566f37:      	popl	%ecx
  566f38:      	cmpl	%edi, %eax
  566f3a:      	je	0x566f69 <.text+0x165f69>
  566f3c:      	pushl	$0x5f0838               # imm = 0x5F0838
  566f41:      	pushl	$0x1
  566f43:      	pushl	$0x12
  566f45:      	pushl	$0x13
  566f47:      	pushl	$0x1a5                  # imm = 0x1A5
  566f4c:      	pushl	$0x1f
  566f4e:      	pushl	$0x7fa                  # imm = 0x7FA
  566f53:      	pushl	$0x81a                  # imm = 0x81A
  566f58:      	pushl	%edi
  566f59:      	pushl	0xc6f4bc
  566f5f:      	movl	%eax, %ecx
  566f61:      	pushl	%esi
  566f62:      	calll	0x5715a0 <.text+0x1705a0>
  566f67:      	jmp	0x566f6b <.text+0x165f6b>
  566f69:      	xorl	%eax, %eax
  566f6b:      	pushl	$0x5f0828               # imm = 0x5F0828
  566f70:      	pushl	$0x5f081c               # imm = 0x5F081C
  566f75:      	movl	%eax, %ecx
  566f77:      	movl	%eax, 0xc70340
  566f7c:      	calll	0x56f4cb <.text+0x16e4cb>
  566f81:      	pushl	$0x110                  # imm = 0x110
  566f86:      	calll	0x5c6d12 <.text+0x1c5d12>
  566f8b:      	popl	%ecx
  566f8c:      	cmpl	%edi, %eax
  566f8e:      	je	0x566fbd <.text+0x165fbd>
  566f90:      	pushl	$0x5f0818               # imm = 0x5F0818
  566f95:      	pushl	$0x1
  566f97:      	pushl	$0x12
  566f99:      	pushl	$0x13
  566f9b:      	pushl	$0x1a5                  # imm = 0x1A5
  566fa0:      	pushl	$0x47
  566fa2:      	pushl	$0x7fa                  # imm = 0x7FA
  566fa7:      	pushl	$0x81a                  # imm = 0x81A
  566fac:      	pushl	%edi
  566fad:      	pushl	0xc6f4bc
  566fb3:      	movl	%eax, %ecx
  566fb5:      	pushl	%esi
  566fb6:      	calll	0x5715a0 <.text+0x1705a0>
  566fbb:      	jmp	0x566fbf <.text+0x165fbf>
  566fbd:      	xorl	%eax, %eax
  566fbf:      	pushl	$0x5f0828               # imm = 0x5F0828
  566fc4:      	pushl	$0x5f081c               # imm = 0x5F081C
  566fc9:      	movl	%eax, %ecx
  566fcb:      	movl	%eax, 0xc70338
  566fd0:      	calll	0x56f4cb <.text+0x16e4cb>
  566fd5:      	pushl	$0x110                  # imm = 0x110
  566fda:      	calll	0x5c6d12 <.text+0x1c5d12>
  566fdf:      	popl	%ecx
  566fe0:      	cmpl	%edi, %eax
  566fe2:      	je	0x567011 <.text+0x166011>
  566fe4:      	pushl	$0x5e83d8               # imm = 0x5E83D8
  566fe9:      	pushl	$0x1
  566feb:      	pushl	$0x12
  566fed:      	pushl	$0x13
  566fef:      	pushl	$0x1a5                  # imm = 0x1A5
  566ff4:      	pushl	$0x33
  566ff6:      	pushl	$0x7fa                  # imm = 0x7FA
  566ffb:      	pushl	$0x81a                  # imm = 0x81A
  567000:      	pushl	%edi
  567001:      	pushl	0xc6f4bc
  567007:      	movl	%eax, %ecx
  567009:      	pushl	%esi
  56700a:      	calll	0x5715a0 <.text+0x1705a0>
  56700f:      	jmp	0x567013 <.text+0x166013>
  567011:      	xorl	%eax, %eax
  567013:      	pushl	$0x5f0828               # imm = 0x5F0828
  567018:      	pushl	$0x5f081c               # imm = 0x5F081C
  56701d:      	movl	%eax, %ecx
  56701f:      	movl	%eax, 0xc7033c
  567024:      	calll	0x56f4cb <.text+0x16e4cb>
  567029:      	pushl	$0x110                  # imm = 0x110
  56702e:      	calll	0x5c6d12 <.text+0x1c5d12>
  567033:      	popl	%ecx
  567034:      	cmpl	%edi, %eax
  567036:      	je	0x567065 <.text+0x166065>
  567038:      	pushl	$0x5f0d3c               # imm = 0x5F0D3C
  56703d:      	pushl	$0x1
  56703f:      	pushl	$0x12
  567041:      	pushl	$0x13
  567043:      	pushl	$0x1a5                  # imm = 0x1A5
  567048:      	pushl	$0x5b
  56704a:      	pushl	$0x7fa                  # imm = 0x7FA
  56704f:      	pushl	$0x81a                  # imm = 0x81A
  567054:      	pushl	%edi
  567055:      	pushl	0xc6f4bc
  56705b:      	movl	%eax, %ecx
  56705d:      	pushl	%esi
  56705e:      	calll	0x5715a0 <.text+0x1705a0>
  567063:      	jmp	0x567067 <.text+0x166067>
  567065:      	xorl	%eax, %eax
  567067:      	pushl	$0x5f0828               # imm = 0x5F0828
  56706c:      	pushl	$0x5f081c               # imm = 0x5F081C
  567071:      	movl	%eax, %ecx
  567073:      	movl	%eax, 0xc70334
  567078:      	calll	0x56f4cb <.text+0x16e4cb>
  56707d:      	movl	0xc6fc70, %eax
  567082:      	cmpl	$0x1, %eax
  567085:      	je	0x567174 <.text+0x166174>
  56708b:      	cmpl	$0x2, %eax
  56708e:      	je	0x567174 <.text+0x166174>
  567094:      	pushl	$0x110                  # imm = 0x110
  567099:      	calll	0x5c6d12 <.text+0x1c5d12>
  56709e:      	popl	%ecx
  56709f:      	cmpl	%edi, %eax
  5670a1:      	je	0x5670d0 <.text+0x1660d0>
  5670a3:      	pushl	$0x5e83d4               # imm = 0x5E83D4
  5670a8:      	pushl	$0x1
  5670aa:      	pushl	$0x12
  5670ac:      	pushl	$0x13
  5670ae:      	pushl	$0x1a5                  # imm = 0x1A5
  5670b3:      	pushl	$0x6f
  5670b5:      	pushl	$0x7fa                  # imm = 0x7FA
  5670ba:      	pushl	$0x81a                  # imm = 0x81A
  5670bf:      	pushl	%edi
  5670c0:      	pushl	0xc6f4bc
  5670c6:      	movl	%eax, %ecx
  5670c8:      	pushl	%esi
  5670c9:      	calll	0x5715a0 <.text+0x1705a0>
  5670ce:      	jmp	0x5670d2 <.text+0x1660d2>
  5670d0:      	xorl	%eax, %eax
  5670d2:      	pushl	$0x5f0828               # imm = 0x5F0828
  5670d7:      	pushl	$0x5f081c               # imm = 0x5F081C
  5670dc:      	movl	%eax, %ecx
  5670de:      	movl	%eax, 0xc70330
  5670e3:      	calll	0x56f4cb <.text+0x16e4cb>
  5670e8:      	pushl	$0x110                  # imm = 0x110
  5670ed:      	calll	0x5c6d12 <.text+0x1c5d12>
  5670f2:      	popl	%ecx
  5670f3:      	cmpl	%edi, %eax
  5670f5:      	je	0x567127 <.text+0x166127>
  5670f7:      	pushl	$0x5e83dc               # imm = 0x5E83DC
  5670fc:      	pushl	$0x1
  5670fe:      	pushl	$0x12
  567100:      	pushl	$0x13
  567102:      	pushl	$0x1a5                  # imm = 0x1A5
  567107:      	pushl	$0x83
  56710c:      	pushl	$0x7fa                  # imm = 0x7FA
  567111:      	pushl	$0x81a                  # imm = 0x81A
  567116:      	pushl	%edi
  567117:      	pushl	0xc6f4bc
  56711d:      	movl	%eax, %ecx
  56711f:      	pushl	%esi
  567120:      	calll	0x5715a0 <.text+0x1705a0>
  567125:      	jmp	0x567129 <.text+0x166129>
  567127:      	xorl	%eax, %eax
  567129:      	pushl	$0x5f0828               # imm = 0x5F0828
  56712e:      	pushl	$0x5f081c               # imm = 0x5F081C
  567133:      	movl	%eax, %ecx
  567135:      	movl	%eax, 0xc7032c
  56713a:      	calll	0x56f4cb <.text+0x16e4cb>
  56713f:      	movl	0xc70330, %eax
  567144:      	addl	$0x20, %eax
  567147:      	pushl	%eax
  567148:      	pushl	$0x5f0d34               # imm = 0x5F0D34
  56714d:      	pushl	$0x5e5c9c               # imm = 0x5E5C9C
  567152:      	calll	0x4ba7c3 <.text+0xb97c3>
  567157:      	movl	0xc7032c, %eax
  56715c:      	addl	$0x20, %eax
  56715f:      	pushl	%eax
  567160:      	pushl	$0x5f0d30               # imm = 0x5F0D30
  567165:      	pushl	$0x5e5c9c               # imm = 0x5E5C9C
  56716a:      	calll	0x4ba7c3 <.text+0xb97c3>
  56716f:      	addl	$0x18, %esp
  567172:      	jmp	0x567180 <.text+0x166180>
  567174:      	movl	%edi, 0xc70330
  56717a:      	movl	%edi, 0xc7032c
  567180:      	pushl	$0x110                  # imm = 0x110
  567185:      	calll	0x5c6d12 <.text+0x1c5d12>
  56718a:      	popl	%ecx
  56718b:      	cmpl	%edi, %eax
  56718d:      	je	0x5671bf <.text+0x1661bf>
  56718f:      	pushl	%edi
  567190:      	pushl	%edi
  567191:      	pushl	$0x12
  567193:      	pushl	$0x13
  567195:      	pushl	$0x174                  # imm = 0x174
  56719a:      	pushl	$0x1a6                  # imm = 0x1A6
  56719f:      	pushl	$0x7ff                  # imm = 0x7FF
  5671a4:      	pushl	$0x819                  # imm = 0x819
  5671a9:      	pushl	%edi
  5671aa:      	pushl	0xc6f4bc
  5671b0:      	movl	%eax, %ecx
  5671b2:      	pushl	%esi
  5671b3:      	calll	0x5715a0 <.text+0x1705a0>
  5671b8:      	movl	%eax, 0xc70324
  5671bd:      	jmp	0x5671c5 <.text+0x1661c5>
  5671bf:      	movl	%edi, 0xc70324
  5671c5:      	pushl	$0x110                  # imm = 0x110
  5671ca:      	calll	0x5c6d12 <.text+0x1c5d12>
  5671cf:      	popl	%ecx
  5671d0:      	cmpl	%edi, %eax
  5671d2:      	je	0x567204 <.text+0x166204>
  5671d4:      	pushl	%edi
  5671d5:      	pushl	%edi
  5671d6:      	pushl	$0x12
  5671d8:      	pushl	$0x13
  5671da:      	pushl	$0x186                  # imm = 0x186
  5671df:      	pushl	$0x1a6                  # imm = 0x1A6
  5671e4:      	pushl	$0x800                  # imm = 0x800
  5671e9:      	pushl	$0x818                  # imm = 0x818
  5671ee:      	pushl	%edi
  5671ef:      	pushl	0xc6f4bc
  5671f5:      	movl	%eax, %ecx
  5671f7:      	pushl	%esi
  5671f8:      	calll	0x5715a0 <.text+0x1705a0>
  5671fd:      	movl	%eax, 0xc70320
  567202:      	jmp	0x56720a <.text+0x16620a>
  567204:      	movl	%edi, 0xc70320
  56720a:      	pushl	$0x110                  # imm = 0x110
  56720f:      	calll	0x5c6d12 <.text+0x1c5d12>
  567214:      	popl	%ecx
  567215:      	cmpl	%edi, %eax
  567217:      	je	0x567249 <.text+0x166249>
  567219:      	pushl	%edi
  56721a:      	pushl	%edi
  56721b:      	pushl	$0x12
  56721d:      	pushl	$0x13
  56721f:      	pushl	$0xb7
  567224:      	pushl	$0xaf
  567229:      	pushl	$0x7ff                  # imm = 0x7FF
  56722e:      	pushl	$0x819                  # imm = 0x819
  567233:      	pushl	%edi
  567234:      	pushl	0xc6f4bc
  56723a:      	movl	%eax, %ecx
  56723c:      	pushl	%esi
  56723d:      	calll	0x5715a0 <.text+0x1705a0>
  567242:      	movl	%eax, 0xc7031c
  567247:      	jmp	0x56724f <.text+0x16624f>
  567249:      	movl	%edi, 0xc7031c
  56724f:      	pushl	$0x110                  # imm = 0x110
  567254:      	calll	0x5c6d12 <.text+0x1c5d12>
  567259:      	popl	%ecx
  56725a:      	cmpl	%edi, %eax
  56725c:      	je	0x56728e <.text+0x16628e>
  56725e:      	pushl	%edi
  56725f:      	pushl	%edi
  567260:      	pushl	$0x12
  567262:      	pushl	$0x13
  567264:      	pushl	$0xc9
  567269:      	pushl	$0xaf
  56726e:      	pushl	$0x800                  # imm = 0x800
  567273:      	pushl	$0x818                  # imm = 0x818
  567278:      	pushl	%edi
  567279:      	pushl	0xc6f4bc
  56727f:      	movl	%eax, %ecx
  567281:      	pushl	%esi
  567282:      	calll	0x5715a0 <.text+0x1705a0>
  567287:      	movl	%eax, 0xc70318
  56728c:      	jmp	0x567294 <.text+0x166294>
  56728e:      	movl	%edi, 0xc70318
  567294:      	pushl	$0x110                  # imm = 0x110
  567299:      	calll	0x5c6d12 <.text+0x1c5d12>
  56729e:      	popl	%ecx
  56729f:      	cmpl	%edi, %eax
  5672a1:      	je	0x5672d3 <.text+0x1662d3>
  5672a3:      	pushl	%edi
  5672a4:      	pushl	%edi
  5672a5:      	pushl	$0x12
  5672a7:      	pushl	$0x13
  5672a9:      	pushl	$0x194                  # imm = 0x194
  5672ae:      	pushl	$0xaf
  5672b3:      	pushl	$0x7ff                  # imm = 0x7FF
  5672b8:      	pushl	$0x819                  # imm = 0x819
  5672bd:      	pushl	%edi
  5672be:      	pushl	0xc6f4bc
  5672c4:      	movl	%eax, %ecx
  5672c6:      	pushl	%esi
  5672c7:      	calll	0x5715a0 <.text+0x1705a0>
  5672cc:      	movl	%eax, 0xc70314
  5672d1:      	jmp	0x5672d9 <.text+0x1662d9>
  5672d3:      	movl	%edi, 0xc70314
  5672d9:      	pushl	$0x110                  # imm = 0x110
  5672de:      	calll	0x5c6d12 <.text+0x1c5d12>
  5672e3:      	popl	%ecx
  5672e4:      	cmpl	%edi, %eax
  5672e6:      	je	0x567318 <.text+0x166318>
  5672e8:      	pushl	%edi
  5672e9:      	pushl	%edi
  5672ea:      	pushl	$0x12
  5672ec:      	pushl	$0x13
  5672ee:      	pushl	$0x1a6                  # imm = 0x1A6
  5672f3:      	pushl	$0xaf
  5672f8:      	pushl	$0x800                  # imm = 0x800
  5672fd:      	pushl	$0x818                  # imm = 0x818
  567302:      	pushl	%edi
  567303:      	pushl	0xc6f4bc
  567309:      	movl	%eax, %ecx
  56730b:      	pushl	%esi
  56730c:      	calll	0x5715a0 <.text+0x1705a0>
  567311:      	movl	%eax, 0xc70310
  567316:      	jmp	0x56731e <.text+0x16631e>
  567318:      	movl	%edi, 0xc70310
  56731e:      	pushl	$0x110                  # imm = 0x110
  567323:      	calll	0x5c6d12 <.text+0x1c5d12>
  567328:      	popl	%ecx
  567329:      	cmpl	%edi, %eax
  56732b:      	je	0x56735d <.text+0x16635d>
  56732d:      	pushl	%edi
  56732e:      	pushl	%edi
  56732f:      	pushl	$0x12
  567331:      	pushl	$0x13
  567333:      	pushl	$0xd8
  567338:      	pushl	$0x250                  # imm = 0x250
  56733d:      	pushl	$0x7ff                  # imm = 0x7FF
  567342:      	pushl	$0x819                  # imm = 0x819
  567347:      	pushl	%edi
  567348:      	pushl	0xc6f4bc
  56734e:      	movl	%eax, %ecx
  567350:      	pushl	%esi
  567351:      	calll	0x5715a0 <.text+0x1705a0>
  567356:      	movl	%eax, 0xc7030c
  56735b:      	jmp	0x567363 <.text+0x166363>
  56735d:      	movl	%edi, 0xc7030c
  567363:      	pushl	$0x110                  # imm = 0x110
  567368:      	calll	0x5c6d12 <.text+0x1c5d12>
  56736d:      	popl	%ecx
  56736e:      	cmpl	%edi, %eax
  567370:      	je	0x5673a2 <.text+0x1663a2>
  567372:      	pushl	%edi
  567373:      	pushl	%edi
  567374:      	pushl	$0x12
  567376:      	pushl	$0x13
  567378:      	pushl	$0xea
  56737d:      	pushl	$0x250                  # imm = 0x250
  567382:      	pushl	$0x800                  # imm = 0x800
  567387:      	pushl	$0x818                  # imm = 0x818
  56738c:      	pushl	%edi
  56738d:      	pushl	0xc6f4bc
  567393:      	movl	%eax, %ecx
  567395:      	pushl	%esi
  567396:      	calll	0x5715a0 <.text+0x1705a0>
  56739b:      	movl	%eax, 0xc70308
  5673a0:      	jmp	0x5673a8 <.text+0x1663a8>
  5673a2:      	movl	%edi, 0xc70308
  5673a8:      	pushl	$0x110                  # imm = 0x110
  5673ad:      	calll	0x5c6d12 <.text+0x1c5d12>
  5673b2:      	popl	%ecx
  5673b3:      	cmpl	%edi, %eax
  5673b5:      	je	0x5673e7 <.text+0x1663e7>
  5673b7:      	pushl	%edi
  5673b8:      	pushl	%edi
  5673b9:      	pushl	$0x12
  5673bb:      	pushl	$0x13
  5673bd:      	pushl	$0x194                  # imm = 0x194
  5673c2:      	pushl	$0x250                  # imm = 0x250
  5673c7:      	pushl	$0x7ff                  # imm = 0x7FF
  5673cc:      	pushl	$0x819                  # imm = 0x819
  5673d1:      	pushl	%edi
  5673d2:      	pushl	0xc6f4bc
  5673d8:      	movl	%eax, %ecx
  5673da:      	pushl	%esi
  5673db:      	calll	0x5715a0 <.text+0x1705a0>
  5673e0:      	movl	%eax, 0xc70304
  5673e5:      	jmp	0x5673ed <.text+0x1663ed>
  5673e7:      	movl	%edi, 0xc70304
  5673ed:      	pushl	$0x110                  # imm = 0x110
  5673f2:      	calll	0x5c6d12 <.text+0x1c5d12>
  5673f7:      	popl	%ecx
  5673f8:      	cmpl	%edi, %eax
  5673fa:      	je	0x56742c <.text+0x16642c>
  5673fc:      	pushl	%edi
  5673fd:      	pushl	%edi
  5673fe:      	pushl	$0x12
  567400:      	pushl	$0x13
  567402:      	pushl	$0x1a6                  # imm = 0x1A6
  567407:      	pushl	$0x250                  # imm = 0x250
  56740c:      	pushl	$0x800                  # imm = 0x800
  567411:      	pushl	$0x818                  # imm = 0x818
  567416:      	pushl	%edi
  567417:      	pushl	0xc6f4bc
  56741d:      	movl	%eax, %ecx
  56741f:      	pushl	%esi
  567420:      	calll	0x5715a0 <.text+0x1705a0>
  567425:      	movl	%eax, 0xc70300
  56742a:      	jmp	0x567432 <.text+0x166432>
  56742c:      	movl	%edi, 0xc70300
  567432:      	pushl	$0x128                  # imm = 0x128
  567437:      	calll	0x5c6d12 <.text+0x1c5d12>
  56743c:      	popl	%ecx
  56743d:      	cmpl	%edi, %eax
  56743f:      	je	0x567462 <.text+0x166462>
  567441:      	pushl	%edi
  567442:      	pushl	$0x11
  567444:      	pushl	$0xcd
  567449:      	pushl	$0x1c2                  # imm = 0x1C2
  56744e:      	pushl	$0xd8
  567453:      	pushl	$0x5df2cc               # imm = 0x5DF2CC
  567458:      	pushl	%esi
  567459:      	movl	%eax, %ecx
  56745b:      	calll	0x572841 <.text+0x171841>
  567460:      	jmp	0x567464 <.text+0x166464>
  567462:      	xorl	%eax, %eax
  567464:      	pushl	$0x1
  567466:      	movl	%eax, %ecx
  567468:      	movl	%eax, 0xc702d4
  56746d:      	calll	0x572935 <.text+0x171935>
  567472:      	movl	0xc70350, %eax
  567477:      	addl	$0x20, %eax
  56747a:      	pushl	%eax
  56747b:      	pushl	$0x5f060c               # imm = 0x5F060C
  567480:      	movl	$0x5e5c9c, %edi         # imm = 0x5E5C9C
  567485:      	pushl	%edi
  567486:      	calll	0x4ba7c3 <.text+0xb97c3>
  56748b:      	movl	0xc70348, %eax
  567490:      	addl	$0x20, %eax
  567493:      	pushl	%eax
  567494:      	pushl	$0x5f05fc               # imm = 0x5F05FC
  567499:      	pushl	%edi
  56749a:      	calll	0x4ba7c3 <.text+0xb97c3>
  56749f:      	movl	0xc7034c, %eax
  5674a4:      	addl	$0x20, %eax
  5674a7:      	pushl	%eax
  5674a8:      	pushl	$0x5f0d24               # imm = 0x5F0D24
  5674ad:      	movl	$0x5f0d18, %edi         # imm = 0x5F0D18
  5674b2:      	pushl	%edi
  5674b3:      	calll	0x4ba7c3 <.text+0xb97c3>
  5674b8:      	movl	0xc70344, %eax
  5674bd:      	addl	$0x20, %eax
  5674c0:      	pushl	%eax
  5674c1:      	pushl	$0x5f0d0c               # imm = 0x5F0D0C
  5674c6:      	pushl	%edi
  5674c7:      	calll	0x4ba7c3 <.text+0xb97c3>
  5674cc:      	movl	0xc70328, %eax
  5674d1:      	addl	$0x20, %eax
  5674d4:      	pushl	%eax
  5674d5:      	pushl	$0x5f0d00               # imm = 0x5F0D00
  5674da:      	pushl	%edi
  5674db:      	calll	0x4ba7c3 <.text+0xb97c3>
  5674e0:      	movl	0xc702e8, %eax
  5674e5:      	addl	$0x4, %eax
  5674e8:      	pushl	%eax
  5674e9:      	pushl	$0x5f0cf8               # imm = 0x5F0CF8
  5674ee:      	pushl	%edi
  5674ef:      	calll	0x4ba7c3 <.text+0xb97c3>
  5674f4:      	movl	0xc702dc, %eax
  5674f9:      	addl	$0x48, %esp
  5674fc:      	addl	$0x4, %eax
  5674ff:      	pushl	%eax
  567500:      	pushl	$0x5f0cf0               # imm = 0x5F0CF0
  567505:      	pushl	%edi
  567506:      	calll	0x4ba7c3 <.text+0xb97c3>
  56750b:      	movl	0xc702e4, %eax
  567510:      	addl	$0x4, %eax
  567513:      	pushl	%eax
  567514:      	pushl	$0x5f0ce4               # imm = 0x5F0CE4
  567519:      	pushl	%edi
  56751a:      	calll	0x4ba7c3 <.text+0xb97c3>
  56751f:      	movl	0xc702d8, %eax
  567524:      	addl	$0x4, %eax
  567527:      	pushl	%eax
  567528:      	pushl	$0x5f0cd8               # imm = 0x5F0CD8
  56752d:      	pushl	%edi
  56752e:      	calll	0x4ba7c3 <.text+0xb97c3>
  567533:      	movl	0xc70340, %eax
  567538:      	addl	$0x20, %eax
  56753b:      	pushl	%eax
  56753c:      	pushl	$0x5f05f4               # imm = 0x5F05F4
  567541:      	pushl	$0x5e5c9c               # imm = 0x5E5C9C
  567546:      	calll	0x4ba7c3 <.text+0xb97c3>
  56754b:      	movl	0xc7033c, %eax
  567550:      	addl	$0x20, %eax
  567553:      	pushl	%eax
  567554:      	pushl	$0x5f05ec               # imm = 0x5F05EC
  567559:      	pushl	$0x5e5c9c               # imm = 0x5E5C9C
  56755e:      	calll	0x4ba7c3 <.text+0xb97c3>
  567563:      	movl	0xc70338, %eax
  567568:      	addl	$0x20, %eax
  56756b:      	pushl	%eax
  56756c:      	pushl	$0x5f05e4               # imm = 0x5F05E4
  567571:      	pushl	$0x5e5c9c               # imm = 0x5E5C9C
  567576:      	calll	0x4ba7c3 <.text+0xb97c3>
  56757b:      	movl	0xc70334, %eax
  567580:      	addl	$0x48, %esp
  567583:      	addl	$0x20, %eax
  567586:      	pushl	%eax
  567587:      	pushl	$0x5f0cd0               # imm = 0x5F0CD0
  56758c:      	pushl	$0x5e5c9c               # imm = 0x5E5C9C
  567591:      	calll	0x4ba7c3 <.text+0xb97c3>
  567596:      	movl	0xc702e0, %eax
  56759b:      	addl	$0x4, %eax
  56759e:      	pushl	%eax
  56759f:      	pushl	$0x5f0584               # imm = 0x5F0584
  5675a4:      	pushl	$0x5e5c9c               # imm = 0x5E5C9C
  5675a9:      	calll	0x4ba7c3 <.text+0xb97c3>
  5675ae:      	movl	0xc702f4, %eax
  5675b3:      	addl	$0x4, %eax
  5675b6:      	pushl	%eax
  5675b7:      	pushl	$0x5e6524               # imm = 0x5E6524
  5675bc:      	pushl	$0x5e5c9c               # imm = 0x5E5C9C
  5675c1:      	calll	0x4ba7c3 <.text+0xb97c3>
  5675c6:      	movl	0xc702f0, %eax
  5675cb:      	addl	$0x4, %eax
  5675ce:      	pushl	%eax
  5675cf:      	pushl	$0x5e6504               # imm = 0x5E6504
  5675d4:      	pushl	%edi
  5675d5:      	calll	0x4ba7c3 <.text+0xb97c3>
  5675da:      	movl	0xc702ec, %eax
  5675df:      	addl	$0x4, %eax
  5675e2:      	pushl	%eax
  5675e3:      	pushl	$0x5e64fc               # imm = 0x5E64FC
  5675e8:      	pushl	$0x5e5c9c               # imm = 0x5E5C9C
  5675ed:      	calll	0x4ba7c3 <.text+0xb97c3>
  5675f2:      	addl	$0x3c, %esp
  5675f5:      	pushl	$0x0
  5675f7:      	pushl	$0x32
  5675f9:      	pushl	$0x1
  5675fb:      	pushl	%esi
  5675fc:      	calll	*0x5ce534
  567602:      	pushl	$0x94
  567607:      	movl	%eax, 0xc702d0
  56760c:      	calll	0x5c6d12 <.text+0x1c5d12>
  567611:      	popl	%ecx
  567612:      	testl	%eax, %eax
  567614:      	je	0x567622 <.text+0x166622>
  567616:      	pushl	$0x0
  567618:      	pushl	%esi
  567619:      	movl	%eax, %ecx
  56761b:      	calll	0x551c69 <.text+0x150c69>
  567620:      	jmp	0x567624 <.text+0x166624>
  567622:      	xorl	%eax, %eax
  567624:      	pushl	$0x5efea0               # imm = 0x5EFEA0
  567629:      	movl	%eax, %ecx
  56762b:      	movl	%eax, 0xc702cc
  567630:      	calll	0x55b7bf <.text+0x15a7bf>
  567635:      	pushl	$0x6
  567637:      	popl	%ecx
  567638:      	pushl	$0x3fd                  # imm = 0x3FD
  56763d:      	xorl	%eax, %eax
  56763f:      	movl	$0xc70290, %edi         # imm = 0xC70290
  567644:      	pushl	%esi
  567645:      	rep		stosl	%eax, %es:(%edi)
  567647:      	calll	*%ebx
  567649:      	pushl	%eax
  56764a:      	calll	*0x5ce5f4
  567650:      	xorl	%eax, %eax
  567652:      	jmp	0x568fe4 <.text+0x167fe4>
  567657:      	movl	$0x10, 0x10(%ebx)
  56765e:      	jmp	0x567785 <.text+0x166785>
  567663:      	movl	0xc702d0, %eax
  567668:      	xorl	%edi, %edi
  56766a:      	cmpl	%edi, %eax
  56766c:      	je	0x56767c <.text+0x16667c>
  56766e:      	pushl	%eax
  56766f:      	pushl	%esi
  567670:      	calll	*0x5ce538
  567676:      	movl	%edi, 0xc702d0
  56767c:      	movl	0x5ce530, %ebx
  567682:      	pushl	%edi
  567683:      	pushl	%esi
  567684:      	calll	*%ebx
  567686:      	pushl	%esi
  567687:      	calll	0x55cfe1 <.text+0x15bfe1>
  56768c:      	popl	%ecx
  56768d:      	pushl	%edi
  56768e:      	pushl	%esi
  56768f:      	calll	*%ebx
  567691:      	cmpb	$0x0, 0xc6fca6
  567698:      	je	0x56778d <.text+0x16678d>
  56769e:      	pushl	$0x5
  5676a0:      	popl	%ecx
  5676a1:      	movl	$0x5f03e4, %esi         # imm = 0x5F03E4
  5676a6:      	leal	0x51c(%ebp), %edi
  5676ac:      	rep		movsl	(%esi), %es:(%edi)
  5676ae:      	movsw	(%esi), %es:(%edi)
  5676b0:      	pushl	$0xe9
  5676b5:      	leal	0x533(%ebp), %eax
  5676bb:      	pushl	$0x0
  5676bd:      	pushl	%eax
  5676be:      	movsb	(%esi), %es:(%edi)
  5676bf:      	calll	0x5c6dfc <.text+0x1c5dfc>
  5676c4:      	leal	0x51c(%ebp), %eax
  5676ca:      	pushl	%eax
  5676cb:      	pushl	$0x5f03d0               # imm = 0x5F03D0
  5676d0:      	pushl	$0x5ef520               # imm = 0x5EF520
  5676d5:      	calll	0x4ba7c3 <.text+0xb97c3>
  5676da:      	movl	-0x2c(%ebp), %esi
  5676dd:      	leal	0x51c(%ebp), %eax
  5676e3:      	pushl	%eax
  5676e4:      	pushl	%esi
  5676e5:      	calll	0x553e75 <.text+0x152e75>
  5676ea:      	addl	$0x20, %esp
  5676ed:      	xorl	%edi, %edi
  5676ef:      	pushl	%edi
  5676f0:      	pushl	%esi
  5676f1:      	calll	*%ebx
  5676f3:      	calll	0x4dd321 <.text+0xdc321>
  5676f8:      	pushl	%edi
  5676f9:      	pushl	%esi
  5676fa:      	calll	*%ebx
  5676fc:      	pushl	%edi
  5676fd:      	pushl	0xba7724
  567703:      	calll	0x5860be <.text+0x1850be>
  567708:      	popl	%ecx
  567709:      	popl	%ecx
  56770a:      	pushl	%edi
  56770b:      	pushl	%esi
  56770c:      	movl	%eax, -0x30(%ebp)
  56770f:      	calll	*%ebx
  567711:      	cmpl	%edi, -0x30(%ebp)
  567714:      	je	0x567768 <.text+0x166768>
  567716:      	pushl	$0x8
  567718:      	popl	%ecx
  567719:      	pushl	$0xe0
  56771e:      	leal	0x53c(%ebp), %eax
  567724:      	pushl	$0x0
  567726:      	movl	$0x5f0cb0, %esi         # imm = 0x5F0CB0
  56772b:      	leal	0x51c(%ebp), %edi
  567731:      	pushl	%eax
  567732:      	rep		movsl	(%esi), %es:(%edi)
  567734:      	calll	0x5c6dfc <.text+0x1c5dfc>
  567739:      	leal	0x51c(%ebp), %eax
  56773f:      	pushl	%eax
  567740:      	pushl	$0x5f0ca0               # imm = 0x5F0CA0
  567745:      	pushl	$0x5ef520               # imm = 0x5EF520
  56774a:      	calll	0x4ba7c3 <.text+0xb97c3>
  56774f:      	leal	0x51c(%ebp), %eax
  567755:      	pushl	%eax
  567756:      	pushl	-0x2c(%ebp)
  567759:      	calll	0x553e75 <.text+0x152e75>
  56775e:      	addl	$0x20, %esp
  567761:      	pushl	$0x0
  567763:      	pushl	-0x2c(%ebp)
  567766:      	calll	*%ebx
  567768:      	andl	$0x0, 0xba7724
  56776f:      	pushl	$0x0
  567771:      	pushl	-0x2c(%ebp)
  567774:      	movl	$0xd, 0xc70520
  56777e:      	calll	0x56e64a <.text+0x16d64a>
  567783:      	popl	%ecx
  567784:      	popl	%ecx
  567785:      	xorl	%eax, %eax
  567787:      	incl	%eax
  567788:      	jmp	0x568fe4 <.text+0x167fe4>
  56778d:      	cmpb	$0x0, 0xc6f4b7
  567794:      	je	0x5677ca <.text+0x1667ca>
  567796:      	pushl	$0x6
  567798:      	popl	%ecx
  567799:      	pushl	$0xe8
  56779e:      	leal	0x534(%ebp), %eax
  5677a4:      	pushl	$0x0
  5677a6:      	movl	$0x5f0410, %esi         # imm = 0x5F0410
  5677ab:      	leal	0x51c(%ebp), %edi
  5677b1:      	pushl	%eax
  5677b2:      	rep		movsl	(%esi), %es:(%edi)
  5677b4:      	calll	0x5c6dfc <.text+0x1c5dfc>
  5677b9:      	leal	0x51c(%ebp), %eax
  5677bf:      	pushl	%eax
  5677c0:      	pushl	$0x5f03fc               # imm = 0x5F03FC
  5677c5:      	jmp	0x5676d0 <.text+0x1666d0>
  5677ca:      	pushl	%edi
  5677cb:      	pushl	%esi
  5677cc:      	calll	*%ebx
  5677ce:      	cmpb	$0x0, 0xc6f86f
  5677d5:      	je	0x567831 <.text+0x166831>
  5677d7:      	pushl	$0x8
  5677d9:      	popl	%ecx
  5677da:      	movl	$0x5f0c7c, %esi         # imm = 0x5F0C7C
  5677df:      	leal	0x51c(%ebp), %edi
  5677e5:      	rep		movsl	(%esi), %es:(%edi)
  5677e7:      	pushl	$0xdf
  5677ec:      	leal	0x53d(%ebp), %eax
  5677f2:      	pushl	$0x0
  5677f4:      	pushl	%eax
  5677f5:      	movb	$0x0, 0xc6f86f
  5677fc:      	movsb	(%esi), %es:(%edi)
  5677fd:      	calll	0x5c6dfc <.text+0x1c5dfc>
  567802:      	leal	0x51c(%ebp), %eax
  567808:      	pushl	%eax
  567809:      	pushl	$0x5f0c68               # imm = 0x5F0C68
  56780e:      	pushl	$0x5e5b64               # imm = 0x5E5B64
  567813:      	calll	0x4ba7c3 <.text+0xb97c3>
  567818:      	leal	0x51c(%ebp), %eax
  56781e:      	pushl	%eax
  56781f:      	pushl	$0xc6f4a8               # imm = 0xC6F4A8
  567824:      	calll	0x555cce <.text+0x154cce>
  567829:      	movl	-0x2c(%ebp), %esi
  56782c:      	addl	$0x20, %esp
  56782f:      	xorl	%edi, %edi
  567831:      	pushl	%edi
  567832:      	pushl	%esi
  567833:      	calll	*%ebx
  567835:      	movl	$0xc6fdec, %ecx         # imm = 0xC6FDEC
  56783a:      	calll	0x55934a <.text+0x15834a>
  56783f:      	pushl	0xc702d4
  567845:      	pushl	$0xc70290               # imm = 0xC70290
  56784a:      	calll	0x552ab0 <.text+0x151ab0>
  56784f:      	popl	%ecx
  567850:      	popl	%ecx
  567851:      	pushl	%edi
  567852:      	pushl	%esi
  567853:      	calll	*%ebx
  567855:      	pushl	%edi
  567856:      	pushl	$0x32
  567858:      	pushl	$0x1
  56785a:      	pushl	%esi
  56785b:      	calll	*0x5ce534
  567861:      	movl	%eax, 0xc702d0
  567866:      	cmpl	%edi, 0xc702a8
  56786c:      	je	0x567785 <.text+0x166785>
  567872:      	pushl	$0x1
  567874:      	pushl	%esi
  567875:      	calll	*%ebx
  567877:      	jmp	0x567785 <.text+0x166785>
  56787c:      	subl	$0x133, %ecx            # imm = 0x133
  567882:      	je	0x568fc7 <.text+0x167fc7>
  567888:      	decl	%ecx
  567889:      	je	0x568fc7 <.text+0x167fc7>
  56788f:      	decl	%ecx
  567890:      	decl	%ecx
  567891:      	je	0x568fa7 <.text+0x167fa7>
  567897:      	decl	%ecx
  567898:      	decl	%ecx
  567899:      	je	0x568fa7 <.text+0x167fa7>
  56789f:      	subl	$0xc8, %ecx
  5678a5:      	je	0x568c6b <.text+0x167c6b>
  5678ab:      	decl	%ecx
  5678ac:      	je	0x568a06 <.text+0x167a06>
  5678b2:      	decl	%ecx
  5678b3:      	jne	0x567650 <.text+0x166650>
  5678b9:      	movl	0xc7033c, %ecx
  5678bf:      	movl	%ebx, %edi
  5678c1:      	shrl	$0x10, %edi
  5678c4:      	movzwl	%bx, %ebx
  5678c7:      	pushl	%edi
  5678c8:      	pushl	%ebx
  5678c9:      	movl	%edi, -0x28(%ebp)
  5678cc:      	calll	0x56f3dc <.text+0x16e3dc>
  5678d1:      	testl	%eax, %eax
  5678d3:      	je	0x5678f5 <.text+0x1668f5>
  5678d5:      	movl	0xc7033c, %ecx
  5678db:      	pushl	$0x0
  5678dd:      	pushl	$0x0
  5678df:      	pushl	$0x1
  5678e1:      	calll	0x57231f <.text+0x17131f>
  5678e6:      	movl	$0xc6fdec, %ecx         # imm = 0xC6FDEC
  5678eb:      	calll	0x55b6cc <.text+0x15a6cc>
  5678f0:      	jmp	0x567650 <.text+0x166650>
  5678f5:      	movl	0xc70338, %ecx
  5678fb:      	pushl	%edi
  5678fc:      	pushl	%ebx
  5678fd:      	calll	0x56f3dc <.text+0x16e3dc>
  567902:      	testl	%eax, %eax
  567904:      	je	0x567926 <.text+0x166926>
  567906:      	movl	0xc70338, %ecx
  56790c:      	pushl	$0x0
  56790e:      	pushl	$0x0
  567910:      	pushl	$0x1
  567912:      	calll	0x57231f <.text+0x17131f>
  567917:      	movl	$0xc6fdec, %ecx         # imm = 0xC6FDEC
  56791c:      	calll	0x559091 <.text+0x158091>
  567921:      	jmp	0x567650 <.text+0x166650>
  567926:      	movl	0xc70340, %ecx
  56792c:      	pushl	%edi
  56792d:      	pushl	%ebx
  56792e:      	calll	0x56f3dc <.text+0x16e3dc>
  567933:      	testl	%eax, %eax
  567935:      	je	0x56796c <.text+0x16696c>
  567937:      	movl	0xc70340, %ecx
  56793d:      	pushl	$0x0
  56793f:      	pushl	$0x0
  567941:      	pushl	$0x1
  567943:      	calll	0x57231f <.text+0x17131f>
  567948:      	movzwl	0x62aea4, %eax
  56794f:      	pushl	%eax
  567950:      	pushl	$0x3fd                  # imm = 0x3FD
  567955:      	pushl	%esi
  567956:      	calll	*0x5ce53c
  56795c:      	pushl	%eax
  56795d:      	movl	$0xc6fdec, %ecx         # imm = 0xC6FDEC
  567962:      	calll	0x558fd8 <.text+0x157fd8>
  567967:      	jmp	0x567650 <.text+0x166650>
  56796c:      	movl	0xc70334, %ecx
  567972:      	pushl	%edi
  567973:      	pushl	%ebx
  567974:      	calll	0x56f3dc <.text+0x16e3dc>
  567979:      	testl	%eax, %eax
  56797b:      	je	0x567d13 <.text+0x166d13>
  567981:      	movl	$0xc6fdec, %ecx         # imm = 0xC6FDEC
  567986:      	calll	0x559306 <.text+0x158306>
  56798b:      	pushl	$0xf7
  567990:      	movl	%eax, -0x30(%ebp)
  567993:      	movl	$0x5f0c5c, %esi         # imm = 0x5F0C5C
  567998:      	pushl	$0x0
  56799a:      	testl	%eax, %eax
  56799c:      	je	0x567c7e <.text+0x166c7e>
  5679a2:      	leal	0x21c(%ebp), %edi
  5679a8:      	movsl	(%esi), %es:(%edi)
  5679a9:      	movsl	(%esi), %es:(%edi)
  5679aa:      	leal	0x225(%ebp), %eax
  5679b0:      	pushl	%eax
  5679b1:      	movsb	(%esi), %es:(%edi)
  5679b2:      	calll	0x5c6dfc <.text+0x1c5dfc>
  5679b7:      	movl	$0x5f0c4c, %esi         # imm = 0x5F0C4C
  5679bc:      	leal	0x51c(%ebp), %edi
  5679c2:      	movsl	(%esi), %es:(%edi)
  5679c3:      	movsl	(%esi), %es:(%edi)
  5679c4:      	movsl	(%esi), %es:(%edi)
  5679c5:      	pushl	$0xf3
  5679ca:      	leal	0x529(%ebp), %eax
  5679d0:      	pushl	$0x0
  5679d2:      	pushl	%eax
  5679d3:      	movsb	(%esi), %es:(%edi)
  5679d4:      	calll	0x5c6dfc <.text+0x1c5dfc>
  5679d9:      	leal	0x21c(%ebp), %eax
  5679df:      	pushl	%eax
  5679e0:      	pushl	$0x5f0c40               # imm = 0x5F0C40
  5679e5:      	movl	$0x5e5b64, %ebx         # imm = 0x5E5B64
  5679ea:      	pushl	%ebx
  5679eb:      	calll	0x4ba7c3 <.text+0xb97c3>
  5679f0:      	leal	0x51c(%ebp), %eax
  5679f6:      	pushl	%eax
  5679f7:      	pushl	$0x5f0c34               # imm = 0x5F0C34
  5679fc:      	pushl	%ebx
  5679fd:      	calll	0x4ba7c3 <.text+0xb97c3>
  567a02:      	pushl	-0x30(%ebp)
  567a05:      	leal	0x51c(%ebp), %eax
  567a0b:      	pushl	%eax
  567a0c:      	leal	0x21c(%ebp), %eax
  567a12:      	pushl	%eax
  567a13:      	pushl	$0x5f0c24               # imm = 0x5F0C24
  567a18:      	pushl	$0xc6f4a8               # imm = 0xC6F4A8
  567a1d:      	calll	0x555cce <.text+0x154cce>
  567a22:      	addl	$0x44, %esp
  567a25:      	movl	$0xc6fdec, %ecx         # imm = 0xC6FDEC
  567a2a:      	calll	0x559171 <.text+0x158171>
  567a2f:      	testb	%al, %al
  567a31:      	je	0x567c2e <.text+0x166c2e>
  567a37:      	movl	$0xc6fdec, %ecx         # imm = 0xC6FDEC
  567a3c:      	calll	0x559216 <.text+0x158216>
  567a41:      	movl	%eax, -0x30(%ebp)
  567a44:      	testl	%eax, %eax
  567a46:      	je	0x567a9a <.text+0x166a9a>
  567a48:      	movl	$0x5f0c1c, %esi         # imm = 0x5F0C1C
  567a4d:      	leal	0x61c(%ebp), %edi
  567a53:      	movsl	(%esi), %es:(%edi)
  567a54:      	movsw	(%esi), %es:(%edi)
  567a56:      	pushl	$0xf9
  567a5b:      	leal	0x623(%ebp), %eax
  567a61:      	pushl	$0x0
  567a63:      	pushl	%eax
  567a64:      	movsb	(%esi), %es:(%edi)
  567a65:      	calll	0x5c6dfc <.text+0x1c5dfc>
  567a6a:      	leal	0x61c(%ebp), %eax
  567a70:      	pushl	%eax
  567a71:      	pushl	$0x5f0d34               # imm = 0x5F0D34
  567a76:      	pushl	%ebx
  567a77:      	calll	0x4ba7c3 <.text+0xb97c3>
  567a7c:      	pushl	-0x30(%ebp)
  567a7f:      	leal	0x61c(%ebp), %eax
  567a85:      	pushl	%eax
  567a86:      	pushl	$0x5e1908               # imm = 0x5E1908
  567a8b:      	pushl	$0xc6f4a8               # imm = 0xC6F4A8
  567a90:      	calll	0x555cce <.text+0x154cce>
  567a95:      	addl	$0x28, %esp
  567a98:      	jmp	0x567ae6 <.text+0x166ae6>
  567a9a:      	pushl	$0x8
  567a9c:      	popl	%ecx
  567a9d:      	movl	$0x5f0bf8, %esi         # imm = 0x5F0BF8
  567aa2:      	leal	0x61c(%ebp), %edi
  567aa8:      	rep		movsl	(%esi), %es:(%edi)
  567aaa:      	movsw	(%esi), %es:(%edi)
  567aac:      	pushl	$0xdd
  567ab1:      	leal	0x63f(%ebp), %eax
  567ab7:      	pushl	$0x0
  567ab9:      	pushl	%eax
  567aba:      	movsb	(%esi), %es:(%edi)
  567abb:      	calll	0x5c6dfc <.text+0x1c5dfc>
  567ac0:      	leal	0x61c(%ebp), %eax
  567ac6:      	pushl	%eax
  567ac7:      	pushl	$0x5f0bec               # imm = 0x5F0BEC
  567acc:      	pushl	%ebx
  567acd:      	calll	0x4ba7c3 <.text+0xb97c3>
  567ad2:      	leal	0x61c(%ebp), %eax
  567ad8:      	pushl	%eax
  567ad9:      	pushl	$0xc6f4a8               # imm = 0xC6F4A8
  567ade:      	calll	0x555cce <.text+0x154cce>
  567ae3:      	addl	$0x20, %esp
  567ae6:      	movl	$0xc6fdec, %ecx         # imm = 0xC6FDEC
  567aeb:      	calll	0x559266 <.text+0x158266>
  567af0:      	movl	%eax, -0x30(%ebp)
  567af3:      	testl	%eax, %eax
  567af5:      	je	0x567b49 <.text+0x166b49>
  567af7:      	movl	$0x5f0be0, %esi         # imm = 0x5F0BE0
  567afc:      	leal	0x61c(%ebp), %edi
  567b02:      	movsl	(%esi), %es:(%edi)
  567b03:      	movsl	(%esi), %es:(%edi)
  567b04:      	pushl	$0xf6
  567b09:      	leal	0x626(%ebp), %eax
  567b0f:      	pushl	$0x0
  567b11:      	pushl	%eax
  567b12:      	movsw	(%esi), %es:(%edi)
  567b14:      	calll	0x5c6dfc <.text+0x1c5dfc>
  567b19:      	leal	0x61c(%ebp), %eax
  567b1f:      	pushl	%eax
  567b20:      	pushl	$0x5f0d30               # imm = 0x5F0D30
  567b25:      	pushl	%ebx
  567b26:      	calll	0x4ba7c3 <.text+0xb97c3>
  567b2b:      	pushl	-0x30(%ebp)
  567b2e:      	leal	0x61c(%ebp), %eax
  567b34:      	pushl	%eax
  567b35:      	pushl	$0x5e1908               # imm = 0x5E1908
  567b3a:      	pushl	$0xc6f4a8               # imm = 0xC6F4A8
  567b3f:      	calll	0x555cce <.text+0x154cce>
  567b44:      	addl	$0x28, %esp
  567b47:      	jmp	0x567b93 <.text+0x166b93>
  567b49:      	pushl	$0x9
  567b4b:      	popl	%ecx
  567b4c:      	movl	$0x5f0bb8, %esi         # imm = 0x5F0BB8
  567b51:      	leal	0x61c(%ebp), %edi
  567b57:      	rep		movsl	(%esi), %es:(%edi)
  567b59:      	pushl	$0xdb
  567b5e:      	leal	0x641(%ebp), %eax
  567b64:      	pushl	$0x0
  567b66:      	pushl	%eax
  567b67:      	movsb	(%esi), %es:(%edi)
  567b68:      	calll	0x5c6dfc <.text+0x1c5dfc>
  567b6d:      	leal	0x61c(%ebp), %eax
  567b73:      	pushl	%eax
  567b74:      	pushl	$0x5f0bb0               # imm = 0x5F0BB0
  567b79:      	pushl	%ebx
  567b7a:      	calll	0x4ba7c3 <.text+0xb97c3>
  567b7f:      	leal	0x61c(%ebp), %eax
  567b85:      	pushl	%eax
  567b86:      	pushl	$0xc6f4a8               # imm = 0xC6F4A8
  567b8b:      	calll	0x555cce <.text+0x154cce>
  567b90:      	addl	$0x20, %esp
  567b93:      	movl	$0xc6fdec, %ecx         # imm = 0xC6FDEC
  567b98:      	calll	0x5592b6 <.text+0x1582b6>
  567b9d:      	movl	%eax, -0x30(%ebp)
  567ba0:      	testl	%eax, %eax
  567ba2:      	je	0x567bfd <.text+0x166bfd>
  567ba4:      	pushl	$0x5
  567ba6:      	popl	%ecx
  567ba7:      	movl	$0x5f0b98, %esi         # imm = 0x5F0B98
  567bac:      	leal	0x61c(%ebp), %edi
  567bb2:      	rep		movsl	(%esi), %es:(%edi)
  567bb4:      	movsw	(%esi), %es:(%edi)
  567bb6:      	pushl	$0xe9
  567bbb:      	leal	0x633(%ebp), %eax
  567bc1:      	pushl	$0x0
  567bc3:      	pushl	%eax
  567bc4:      	movsb	(%esi), %es:(%edi)
  567bc5:      	calll	0x5c6dfc <.text+0x1c5dfc>
  567bca:      	leal	0x61c(%ebp), %eax
  567bd0:      	pushl	%eax
  567bd1:      	pushl	$0x5f0550               # imm = 0x5F0550
  567bd6:      	pushl	%ebx
  567bd7:      	calll	0x4ba7c3 <.text+0xb97c3>
  567bdc:      	pushl	-0x30(%ebp)
  567bdf:      	leal	0x61c(%ebp), %eax
  567be5:      	pushl	%eax
  567be6:      	pushl	$0x5e1908               # imm = 0x5E1908
  567beb:      	pushl	$0xc6f4a8               # imm = 0xC6F4A8
  567bf0:      	calll	0x555cce <.text+0x154cce>
  567bf5:      	addl	$0x28, %esp
  567bf8:      	jmp	0x567d02 <.text+0x166d02>
  567bfd:      	pushl	$0x8
  567bff:      	popl	%ecx
  567c00:      	pushl	$0xe0
  567c05:      	leal	0x3c(%ebp), %eax
  567c08:      	pushl	$0x0
  567c0a:      	movl	$0x5f0b78, %esi         # imm = 0x5F0B78
  567c0f:      	leal	0x1c(%ebp), %edi
  567c12:      	pushl	%eax
  567c13:      	rep		movsl	(%esi), %es:(%edi)
  567c15:      	calll	0x5c6dfc <.text+0x1c5dfc>
  567c1a:      	leal	0x1c(%ebp), %eax
  567c1d:      	pushl	%eax
  567c1e:      	pushl	$0x5f0b70               # imm = 0x5F0B70
  567c23:      	pushl	%ebx
  567c24:      	calll	0x4ba7c3 <.text+0xb97c3>
  567c29:      	leal	0x1c(%ebp), %eax
  567c2c:      	jmp	0x567c6b <.text+0x166c6b>
  567c2e:      	pushl	$0x8
  567c30:      	popl	%ecx
  567c31:      	movl	$0x5f0b4c, %esi         # imm = 0x5F0B4C
  567c36:      	leal	0x11c(%ebp), %edi
  567c3c:      	rep		movsl	(%esi), %es:(%edi)
  567c3e:      	pushl	$0xde
  567c43:      	leal	0x13e(%ebp), %eax
  567c49:      	pushl	$0x0
  567c4b:      	pushl	%eax
  567c4c:      	movsw	(%esi), %es:(%edi)
  567c4e:      	calll	0x5c6dfc <.text+0x1c5dfc>
  567c53:      	leal	0x11c(%ebp), %eax
  567c59:      	pushl	%eax
  567c5a:      	pushl	$0x5f0b44               # imm = 0x5F0B44
  567c5f:      	pushl	%ebx
  567c60:      	calll	0x4ba7c3 <.text+0xb97c3>
  567c65:      	leal	0x11c(%ebp), %eax
  567c6b:      	pushl	%eax
  567c6c:      	pushl	$0xc6f4a8               # imm = 0xC6F4A8
  567c71:      	calll	0x555cce <.text+0x154cce>
  567c76:      	addl	$0x20, %esp
  567c79:      	jmp	0x567d02 <.text+0x166d02>
  567c7e:      	leal	0x41c(%ebp), %edi
  567c84:      	movsl	(%esi), %es:(%edi)
  567c85:      	movsl	(%esi), %es:(%edi)
  567c86:      	leal	0x425(%ebp), %eax
  567c8c:      	pushl	%eax
  567c8d:      	movsb	(%esi), %es:(%edi)
  567c8e:      	calll	0x5c6dfc <.text+0x1c5dfc>
  567c93:      	pushl	$0x5
  567c95:      	popl	%ecx
  567c96:      	movl	$0x5f0b2c, %esi         # imm = 0x5F0B2C
  567c9b:      	leal	0x31c(%ebp), %edi
  567ca1:      	rep		movsl	(%esi), %es:(%edi)
  567ca3:      	movsw	(%esi), %es:(%edi)
  567ca5:      	pushl	$0xe9
  567caa:      	leal	0x333(%ebp), %eax
  567cb0:      	pushl	$0x0
  567cb2:      	pushl	%eax
  567cb3:      	movsb	(%esi), %es:(%edi)
  567cb4:      	calll	0x5c6dfc <.text+0x1c5dfc>
  567cb9:      	leal	0x41c(%ebp), %eax
  567cbf:      	pushl	%eax
  567cc0:      	pushl	$0x5f0c40               # imm = 0x5F0C40
  567cc5:      	movl	$0x5e5b64, %ebx         # imm = 0x5E5B64
  567cca:      	pushl	%ebx
  567ccb:      	calll	0x4ba7c3 <.text+0xb97c3>
  567cd0:      	leal	0x31c(%ebp), %eax
  567cd6:      	pushl	%eax
  567cd7:      	pushl	$0x5f0b18               # imm = 0x5F0B18
  567cdc:      	pushl	%ebx
  567cdd:      	calll	0x4ba7c3 <.text+0xb97c3>
  567ce2:      	leal	0x31c(%ebp), %eax
  567ce8:      	pushl	%eax
  567ce9:      	leal	0x41c(%ebp), %eax
  567cef:      	pushl	%eax
  567cf0:      	pushl	$0x5f0b0c               # imm = 0x5F0B0C
  567cf5:      	pushl	$0xc6f4a8               # imm = 0xC6F4A8
  567cfa:      	calll	0x555cce <.text+0x154cce>
  567cff:      	addl	$0x40, %esp
  567d02:      	movl	0xc70334, %ecx
  567d08:      	pushl	$0x0
  567d0a:      	pushl	$0x0
  567d0c:      	pushl	$0x1
  567d0e:      	jmp	0x568c61 <.text+0x167c61>
  567d13:      	movl	0xc70330, %ecx
  567d19:      	xorl	%edi, %edi
  567d1b:      	cmpl	%edi, %ecx
  567d1d:      	je	0x567f36 <.text+0x166f36>
  567d23:      	pushl	-0x28(%ebp)
  567d26:      	pushl	%ebx
  567d27:      	calll	0x56f3dc <.text+0x16e3dc>
  567d2c:      	testl	%eax, %eax
  567d2e:      	je	0x567f36 <.text+0x166f36>
  567d34:      	movl	$0x5f0b00, %esi         # imm = 0x5F0B00
  567d39:      	leal	0x21c(%ebp), %edi
  567d3f:      	movsl	(%esi), %es:(%edi)
  567d40:      	movsl	(%esi), %es:(%edi)
  567d41:      	movsw	(%esi), %es:(%edi)
  567d43:      	pushl	$0xf5
  567d48:      	leal	0x227(%ebp), %eax
  567d4e:      	pushl	$0x0
  567d50:      	pushl	%eax
  567d51:      	movsb	(%esi), %es:(%edi)
  567d52:      	calll	0x5c6dfc <.text+0x1c5dfc>
  567d57:      	leal	0x21c(%ebp), %eax
  567d5d:      	pushl	%eax
  567d5e:      	pushl	$0x5f0af4               # imm = 0x5F0AF4
  567d63:      	movl	$0x5e5b64, %ebx         # imm = 0x5E5B64
  567d68:      	pushl	%ebx
  567d69:      	calll	0x4ba7c3 <.text+0xb97c3>
  567d6e:      	addl	$0x18, %esp
  567d71:      	movl	$0xc6fdec, %ecx         # imm = 0xC6FDEC
  567d76:      	calll	0x559306 <.text+0x158306>
  567d7b:      	movl	%eax, -0x34(%ebp)
  567d7e:      	testl	%eax, %eax
  567d80:      	je	0x567ecd <.text+0x166ecd>
  567d86:      	movl	$0x5f0c4c, %esi         # imm = 0x5F0C4C
  567d8b:      	leal	0x51c(%ebp), %edi
  567d91:      	movsl	(%esi), %es:(%edi)
  567d92:      	movsl	(%esi), %es:(%edi)
  567d93:      	movsl	(%esi), %es:(%edi)
  567d94:      	pushl	$0xf3
  567d99:      	leal	0x529(%ebp), %eax
  567d9f:      	pushl	$0x0
  567da1:      	pushl	%eax
  567da2:      	movsb	(%esi), %es:(%edi)
  567da3:      	calll	0x5c6dfc <.text+0x1c5dfc>
  567da8:      	leal	0x51c(%ebp), %eax
  567dae:      	pushl	%eax
  567daf:      	pushl	$0x5f0c34               # imm = 0x5F0C34
  567db4:      	pushl	%ebx
  567db5:      	calll	0x4ba7c3 <.text+0xb97c3>
  567dba:      	addl	$0x18, %esp
  567dbd:      	movl	$0xc6fdec, %ecx         # imm = 0xC6FDEC
  567dc2:      	calll	0x559171 <.text+0x158171>
  567dc7:      	testb	%al, %al
  567dc9:      	je	0x567e6a <.text+0x166e6a>
  567dcf:      	movl	$0xc6fdec, %ecx         # imm = 0xC6FDEC
  567dd4:      	calll	0x559216 <.text+0x158216>
  567dd9:      	testl	%eax, %eax
  567ddb:      	je	0x567e13 <.text+0x166e13>
  567ddd:      	pushl	%eax
  567dde:      	leal	0x69c(%ebp), %eax
  567de4:      	pushl	$0x5f0ae8               # imm = 0x5F0AE8
  567de9:      	pushl	%eax
  567dea:      	calll	*0x5ce49c
  567df0:      	addl	$0xc, %esp
  567df3:      	pushl	$0x1
  567df5:      	pushl	$0x0
  567df7:      	pushl	$0x0
  567df9:      	leal	0x69c(%ebp), %eax
  567dff:      	pushl	%eax
  567e00:      	pushl	$0x5f0ae0               # imm = 0x5F0AE0
  567e05:      	pushl	-0x2c(%ebp)
  567e08:      	calll	*0x5ce4ec
  567e0e:      	jmp	0x567f25 <.text+0x166f25>
  567e13:      	pushl	$0x8
  567e15:      	popl	%ecx
  567e16:      	movl	$0x5f0bf8, %esi         # imm = 0x5F0BF8
  567e1b:      	leal	0x41c(%ebp), %edi
  567e21:      	rep		movsl	(%esi), %es:(%edi)
  567e23:      	movsw	(%esi), %es:(%edi)
  567e25:      	pushl	$0xdd
  567e2a:      	leal	0x43f(%ebp), %eax
  567e30:      	pushl	$0x0
  567e32:      	pushl	%eax
  567e33:      	movsb	(%esi), %es:(%edi)
  567e34:      	calll	0x5c6dfc <.text+0x1c5dfc>
  567e39:      	leal	0x41c(%ebp), %eax
  567e3f:      	pushl	%eax
  567e40:      	pushl	$0x5f0bec               # imm = 0x5F0BEC
  567e45:      	pushl	%ebx
  567e46:      	calll	0x4ba7c3 <.text+0xb97c3>
  567e4b:      	leal	0x41c(%ebp), %eax
  567e51:      	pushl	%eax
  567e52:      	pushl	-0x34(%ebp)
  567e55:      	leal	0x51c(%ebp), %eax
  567e5b:      	pushl	%eax
  567e5c:      	leal	0x21c(%ebp), %eax
  567e62:      	pushl	%eax
  567e63:      	pushl	$0x5f0acc               # imm = 0x5F0ACC
  567e68:      	jmp	0x567ebe <.text+0x166ebe>
  567e6a:      	pushl	$0x8
  567e6c:      	popl	%ecx
  567e6d:      	movl	$0x5f0b4c, %esi         # imm = 0x5F0B4C
  567e72:      	leal	0x31c(%ebp), %edi
  567e78:      	rep		movsl	(%esi), %es:(%edi)
  567e7a:      	pushl	$0xde
  567e7f:      	leal	0x33e(%ebp), %eax
  567e85:      	pushl	$0x0
  567e87:      	pushl	%eax
  567e88:      	movsw	(%esi), %es:(%edi)
  567e8a:      	calll	0x5c6dfc <.text+0x1c5dfc>
  567e8f:      	leal	0x31c(%ebp), %eax
  567e95:      	pushl	%eax
  567e96:      	pushl	$0x5f0b44               # imm = 0x5F0B44
  567e9b:      	pushl	%ebx
  567e9c:      	calll	0x4ba7c3 <.text+0xb97c3>
  567ea1:      	leal	0x31c(%ebp), %eax
  567ea7:      	pushl	%eax
  567ea8:      	pushl	-0x34(%ebp)
  567eab:      	leal	0x51c(%ebp), %eax
  567eb1:      	pushl	%eax
  567eb2:      	leal	0x21c(%ebp), %eax
  567eb8:      	pushl	%eax
  567eb9:      	pushl	$0x5f0ab8               # imm = 0x5F0AB8
  567ebe:      	pushl	$0xc6f4a8               # imm = 0xC6F4A8
  567ec3:      	calll	0x555cce <.text+0x154cce>
  567ec8:      	addl	$0x30, %esp
  567ecb:      	jmp	0x567f25 <.text+0x166f25>
  567ecd:      	pushl	$0x5
  567ecf:      	popl	%ecx
  567ed0:      	movl	$0x5f0b2c, %esi         # imm = 0x5F0B2C
  567ed5:      	leal	0x11c(%ebp), %edi
  567edb:      	rep		movsl	(%esi), %es:(%edi)
  567edd:      	movsw	(%esi), %es:(%edi)
  567edf:      	pushl	$0xe9
  567ee4:      	leal	0x133(%ebp), %eax
  567eea:      	pushl	$0x0
  567eec:      	pushl	%eax
  567eed:      	movsb	(%esi), %es:(%edi)
  567eee:      	calll	0x5c6dfc <.text+0x1c5dfc>
  567ef3:      	leal	0x11c(%ebp), %eax
  567ef9:      	pushl	%eax
  567efa:      	pushl	$0x5f0b18               # imm = 0x5F0B18
  567eff:      	pushl	%ebx
  567f00:      	calll	0x4ba7c3 <.text+0xb97c3>
  567f05:      	leal	0x11c(%ebp), %eax
  567f0b:      	pushl	%eax
  567f0c:      	leal	0x21c(%ebp), %eax
  567f12:      	pushl	%eax
  567f13:      	pushl	$0x5f0aac               # imm = 0x5F0AAC
  567f18:      	pushl	$0xc6f4a8               # imm = 0xC6F4A8
  567f1d:      	calll	0x555cce <.text+0x154cce>
  567f22:      	addl	$0x28, %esp
  567f25:      	movl	0xc70330, %ecx
  567f2b:      	pushl	$0x0
  567f2d:      	pushl	$0x0
  567f2f:      	pushl	$0x1
  567f31:      	jmp	0x568c61 <.text+0x167c61>
  567f36:      	movl	0xc7032c, %ecx
  567f3c:      	cmpl	%edi, %ecx
  567f3e:      	je	0x56811e <.text+0x16711e>
  567f44:      	pushl	-0x28(%ebp)
  567f47:      	pushl	%ebx
  567f48:      	calll	0x56f3dc <.text+0x16e3dc>
  567f4d:      	testl	%eax, %eax
  567f4f:      	je	0x56811e <.text+0x16711e>
  567f55:      	movl	$0x5f0aa0, %esi         # imm = 0x5F0AA0
  567f5a:      	leal	0x21c(%ebp), %edi
  567f60:      	movsl	(%esi), %es:(%edi)
  567f61:      	movsl	(%esi), %es:(%edi)
  567f62:      	movsw	(%esi), %es:(%edi)
  567f64:      	pushl	$0xf5
  567f69:      	leal	0x227(%ebp), %eax
  567f6f:      	pushl	$0x0
  567f71:      	pushl	%eax
  567f72:      	movsb	(%esi), %es:(%edi)
  567f73:      	calll	0x5c6dfc <.text+0x1c5dfc>
  567f78:      	leal	0x21c(%ebp), %eax
  567f7e:      	pushl	%eax
  567f7f:      	pushl	$0x5f0a94               # imm = 0x5F0A94
  567f84:      	movl	$0x5e5b64, %ebx         # imm = 0x5E5B64
  567f89:      	pushl	%ebx
  567f8a:      	calll	0x4ba7c3 <.text+0xb97c3>
  567f8f:      	addl	$0x18, %esp
  567f92:      	movl	$0xc6fdec, %ecx         # imm = 0xC6FDEC
  567f97:      	calll	0x559306 <.text+0x158306>
  567f9c:      	movl	%eax, -0x34(%ebp)
  567f9f:      	testl	%eax, %eax
  567fa1:      	je	0x5680b5 <.text+0x1670b5>
  567fa7:      	movl	$0x5f0c4c, %esi         # imm = 0x5F0C4C
  567fac:      	leal	0x51c(%ebp), %edi
  567fb2:      	movsl	(%esi), %es:(%edi)
  567fb3:      	movsl	(%esi), %es:(%edi)
  567fb4:      	movsl	(%esi), %es:(%edi)
  567fb5:      	pushl	$0xf3
  567fba:      	leal	0x529(%ebp), %eax
  567fc0:      	pushl	$0x0
  567fc2:      	pushl	%eax
  567fc3:      	movsb	(%esi), %es:(%edi)
  567fc4:      	calll	0x5c6dfc <.text+0x1c5dfc>
  567fc9:      	leal	0x51c(%ebp), %eax
  567fcf:      	pushl	%eax
  567fd0:      	pushl	$0x5f0c34               # imm = 0x5F0C34
  567fd5:      	pushl	%ebx
  567fd6:      	calll	0x4ba7c3 <.text+0xb97c3>
  567fdb:      	addl	$0x18, %esp
  567fde:      	movl	$0xc6fdec, %ecx         # imm = 0xC6FDEC
  567fe3:      	calll	0x559171 <.text+0x158171>
  567fe8:      	testb	%al, %al
  567fea:      	je	0x568052 <.text+0x167052>
  567fec:      	movl	$0xc6fdec, %ecx         # imm = 0xC6FDEC
  567ff1:      	calll	0x559266 <.text+0x158266>
  567ff6:      	testl	%eax, %eax
  567ff8:      	je	0x568014 <.text+0x167014>
  567ffa:      	pushl	$0x1
  567ffc:      	pushl	$0x0
  567ffe:      	pushl	$0x0
  568000:      	pushl	%eax
  568001:      	pushl	$0x5f0ae0               # imm = 0x5F0AE0
  568006:      	pushl	-0x2c(%ebp)
  568009:      	calll	*0x5ce4ec
  56800f:      	jmp	0x56810d <.text+0x16710d>
  568014:      	pushl	$0x9
  568016:      	popl	%ecx
  568017:      	movl	$0x5f0bb8, %esi         # imm = 0x5F0BB8
  56801c:      	leal	0x41c(%ebp), %edi
  568022:      	rep		movsl	(%esi), %es:(%edi)
  568024:      	pushl	$0xdb
  568029:      	leal	0x441(%ebp), %eax
  56802f:      	pushl	$0x0
  568031:      	pushl	%eax
  568032:      	movsb	(%esi), %es:(%edi)
  568033:      	calll	0x5c6dfc <.text+0x1c5dfc>
  568038:      	leal	0x41c(%ebp), %eax
  56803e:      	pushl	%eax
  56803f:      	pushl	$0x5f0bb0               # imm = 0x5F0BB0
  568044:      	pushl	%ebx
  568045:      	calll	0x4ba7c3 <.text+0xb97c3>
  56804a:      	leal	0x41c(%ebp), %eax
  568050:      	jmp	0x56808f <.text+0x16708f>
  568052:      	pushl	$0x8
  568054:      	popl	%ecx
  568055:      	movl	$0x5f0b4c, %esi         # imm = 0x5F0B4C
  56805a:      	leal	0x31c(%ebp), %edi
  568060:      	rep		movsl	(%esi), %es:(%edi)
  568062:      	pushl	$0xde
  568067:      	leal	0x33e(%ebp), %eax
  56806d:      	pushl	$0x0
  56806f:      	pushl	%eax
  568070:      	movsw	(%esi), %es:(%edi)
  568072:      	calll	0x5c6dfc <.text+0x1c5dfc>
  568077:      	leal	0x31c(%ebp), %eax
  56807d:      	pushl	%eax
  56807e:      	pushl	$0x5f0b44               # imm = 0x5F0B44
  568083:      	pushl	%ebx
  568084:      	calll	0x4ba7c3 <.text+0xb97c3>
  568089:      	leal	0x31c(%ebp), %eax
  56808f:      	pushl	%eax
  568090:      	pushl	-0x34(%ebp)
  568093:      	leal	0x51c(%ebp), %eax
  568099:      	pushl	%eax
  56809a:      	leal	0x21c(%ebp), %eax
  5680a0:      	pushl	%eax
  5680a1:      	pushl	$0x5f0a80               # imm = 0x5F0A80
  5680a6:      	pushl	$0xc6f4a8               # imm = 0xC6F4A8
  5680ab:      	calll	0x555cce <.text+0x154cce>
  5680b0:      	addl	$0x30, %esp
  5680b3:      	jmp	0x56810d <.text+0x16710d>
  5680b5:      	pushl	$0x5
  5680b7:      	popl	%ecx
  5680b8:      	movl	$0x5f0b2c, %esi         # imm = 0x5F0B2C
  5680bd:      	leal	0x11c(%ebp), %edi
  5680c3:      	rep		movsl	(%esi), %es:(%edi)
  5680c5:      	movsw	(%esi), %es:(%edi)
  5680c7:      	pushl	$0xe9
  5680cc:      	leal	0x133(%ebp), %eax
  5680d2:      	pushl	$0x0
  5680d4:      	pushl	%eax
  5680d5:      	movsb	(%esi), %es:(%edi)
  5680d6:      	calll	0x5c6dfc <.text+0x1c5dfc>
  5680db:      	leal	0x11c(%ebp), %eax
  5680e1:      	pushl	%eax
  5680e2:      	pushl	$0x5f0b18               # imm = 0x5F0B18
  5680e7:      	pushl	%ebx
  5680e8:      	calll	0x4ba7c3 <.text+0xb97c3>
  5680ed:      	leal	0x11c(%ebp), %eax
  5680f3:      	pushl	%eax
  5680f4:      	leal	0x21c(%ebp), %eax
  5680fa:      	pushl	%eax
  5680fb:      	pushl	$0x5f0aac               # imm = 0x5F0AAC
  568100:      	pushl	$0xc6f4a8               # imm = 0xC6F4A8
  568105:      	calll	0x555cce <.text+0x154cce>
  56810a:      	addl	$0x28, %esp
  56810d:      	movl	0xc7032c, %ecx
  568113:      	pushl	$0x0
  568115:      	pushl	$0x0
  568117:      	pushl	$0x1
  568119:      	jmp	0x568c61 <.text+0x167c61>
  56811e:      	pushl	-0x28(%ebp)
  568121:      	movl	0xc70328, %ecx
  568127:      	pushl	%ebx
  568128:      	calll	0x56f3dc <.text+0x16e3dc>
  56812d:      	testl	%eax, %eax
  56812f:      	je	0x56817b <.text+0x16717b>
  568131:      	movl	0x5ce530, %ebx
  568137:      	pushl	%edi
  568138:      	pushl	%esi
  568139:      	calll	*%ebx
  56813b:      	pushl	%edi
  56813c:      	pushl	$0x564e09               # imm = 0x564E09
  568141:      	pushl	0xc6f4c0
  568147:      	movl	%edi, 0xc702a8
  56814d:      	pushl	$0x98
  568152:      	pushl	0xc6f4bc
  568158:      	calll	0x571361 <.text+0x170361>
  56815d:      	pushl	0xc70354
  568163:      	xorl	%edi, %edi
  568165:      	incl	%edi
  568166:      	pushl	%esi
  568167:      	movl	%edi, 0xc702a8
  56816d:      	calll	0x570cce <.text+0x16fcce>
  568172:      	addl	$0x1c, %esp
  568175:      	pushl	%edi
  568176:      	jmp	0x5683a3 <.text+0x1673a3>
  56817b:      	pushl	-0x28(%ebp)
  56817e:      	movl	0xc70324, %ecx
  568184:      	pushl	%ebx
  568185:      	calll	0x56f3dc <.text+0x16e3dc>
  56818a:      	testl	%eax, %eax
  56818c:      	je	0x5681a1 <.text+0x1671a1>
  56818e:      	movl	0xc70324, %ecx
  568194:      	pushl	%edi
  568195:      	pushl	%edi
  568196:      	pushl	$0x1
  568198:      	calll	0x57231f <.text+0x17131f>
  56819d:      	pushl	%edi
  56819e:      	pushl	%edi
  56819f:      	jmp	0x5681c6 <.text+0x1671c6>
  5681a1:      	pushl	-0x28(%ebp)
  5681a4:      	movl	0xc70320, %ecx
  5681aa:      	pushl	%ebx
  5681ab:      	calll	0x56f3dc <.text+0x16e3dc>
  5681b0:      	testl	%eax, %eax
  5681b2:      	je	0x5681dc <.text+0x1671dc>
  5681b4:      	movl	0xc70320, %ecx
  5681ba:      	pushl	%edi
  5681bb:      	pushl	%edi
  5681bc:      	pushl	$0x1
  5681be:      	calll	0x57231f <.text+0x17131f>
  5681c3:      	pushl	%edi
  5681c4:      	pushl	$0x1
  5681c6:      	pushl	$0xb5
  5681cb:      	pushl	$0x3fc                  # imm = 0x3FC
  5681d0:      	pushl	%esi
  5681d1:      	calll	*0x5ce52c
  5681d7:      	jmp	0x567650 <.text+0x166650>
  5681dc:      	pushl	-0x28(%ebp)
  5681df:      	movl	0xc7031c, %ecx
  5681e5:      	pushl	%ebx
  5681e6:      	calll	0x56f3dc <.text+0x16e3dc>
  5681eb:      	testl	%eax, %eax
  5681ed:      	je	0x568208 <.text+0x167208>
  5681ef:      	movl	0xc7031c, %ecx
  5681f5:      	pushl	%edi
  5681f6:      	pushl	%edi
  5681f7:      	pushl	$0x1
  5681f9:      	calll	0x57231f <.text+0x17131f>
  5681fe:      	movl	$0xc6fe28, %ecx         # imm = 0xC6FE28
  568203:      	jmp	0x5682b3 <.text+0x1672b3>
  568208:      	pushl	-0x28(%ebp)
  56820b:      	movl	0xc70318, %ecx
  568211:      	pushl	%ebx
  568212:      	calll	0x56f3dc <.text+0x16e3dc>
  568217:      	testl	%eax, %eax
  568219:      	je	0x568234 <.text+0x167234>
  56821b:      	movl	0xc70318, %ecx
  568221:      	pushl	%edi
  568222:      	pushl	%edi
  568223:      	pushl	$0x1
  568225:      	calll	0x57231f <.text+0x17131f>
  56822a:      	movl	$0xc6fe28, %ecx         # imm = 0xC6FE28
  56822f:      	jmp	0x5682e4 <.text+0x1672e4>
  568234:      	pushl	-0x28(%ebp)
  568237:      	movl	0xc70314, %ecx
  56823d:      	pushl	%ebx
  56823e:      	calll	0x56f3dc <.text+0x16e3dc>
  568243:      	testl	%eax, %eax
  568245:      	je	0x568260 <.text+0x167260>
  568247:      	movl	0xc70314, %ecx
  56824d:      	pushl	%edi
  56824e:      	pushl	%edi
  56824f:      	pushl	$0x1
  568251:      	calll	0x57231f <.text+0x17131f>
  568256:      	movl	$0xc6fdec, %ecx         # imm = 0xC6FDEC
  56825b:      	jmp	0x568315 <.text+0x167315>
  568260:      	pushl	-0x28(%ebp)
  568263:      	movl	0xc70310, %ecx
  568269:      	pushl	%ebx
  56826a:      	calll	0x56f3dc <.text+0x16e3dc>
  56826f:      	testl	%eax, %eax
  568271:      	je	0x56828c <.text+0x16728c>
  568273:      	movl	0xc70310, %ecx
  568279:      	pushl	%edi
  56827a:      	pushl	%edi
  56827b:      	pushl	$0x1
  56827d:      	calll	0x57231f <.text+0x17131f>
  568282:      	movl	$0xc6fdec, %ecx         # imm = 0xC6FDEC
  568287:      	jmp	0x568346 <.text+0x167346>
  56828c:      	pushl	-0x28(%ebp)
  56828f:      	movl	0xc7030c, %ecx
  568295:      	pushl	%ebx
  568296:      	calll	0x56f3dc <.text+0x16e3dc>
  56829b:      	testl	%eax, %eax
  56829d:      	je	0x5682bd <.text+0x1672bd>
  56829f:      	movl	0xc7030c, %ecx
  5682a5:      	pushl	%edi
  5682a6:      	pushl	%edi
  5682a7:      	pushl	$0x1
  5682a9:      	calll	0x57231f <.text+0x17131f>
  5682ae:      	movl	$0xc6fe68, %ecx         # imm = 0xC6FE68
  5682b3:      	calll	0x5506f0 <.text+0x14f6f0>
  5682b8:      	jmp	0x567650 <.text+0x166650>
  5682bd:      	pushl	-0x28(%ebp)
  5682c0:      	movl	0xc70308, %ecx
  5682c6:      	pushl	%ebx
  5682c7:      	calll	0x56f3dc <.text+0x16e3dc>
  5682cc:      	testl	%eax, %eax
  5682ce:      	je	0x5682ee <.text+0x1672ee>
  5682d0:      	movl	0xc70308, %ecx
  5682d6:      	pushl	%edi
  5682d7:      	pushl	%edi
  5682d8:      	pushl	$0x1
  5682da:      	calll	0x57231f <.text+0x17131f>
  5682df:      	movl	$0xc6fe68, %ecx         # imm = 0xC6FE68
  5682e4:      	calll	0x55071d <.text+0x14f71d>
  5682e9:      	jmp	0x567650 <.text+0x166650>
  5682ee:      	pushl	-0x28(%ebp)
  5682f1:      	movl	0xc70304, %ecx
  5682f7:      	pushl	%ebx
  5682f8:      	calll	0x56f3dc <.text+0x16e3dc>
  5682fd:      	testl	%eax, %eax
  5682ff:      	je	0x56831f <.text+0x16731f>
  568301:      	movl	0xc70304, %ecx
  568307:      	pushl	%edi
  568308:      	pushl	%edi
  568309:      	pushl	$0x1
  56830b:      	calll	0x57231f <.text+0x17131f>
  568310:      	movl	$0xc6fea8, %ecx         # imm = 0xC6FEA8
  568315:      	calll	0x550b6b <.text+0x14fb6b>
  56831a:      	jmp	0x567650 <.text+0x166650>
  56831f:      	pushl	-0x28(%ebp)
  568322:      	movl	0xc70300, %ecx
  568328:      	pushl	%ebx
  568329:      	calll	0x56f3dc <.text+0x16e3dc>
  56832e:      	testl	%eax, %eax
  568330:      	je	0x568350 <.text+0x167350>
  568332:      	movl	0xc70300, %ecx
  568338:      	pushl	%edi
  568339:      	pushl	%edi
  56833a:      	pushl	$0x1
  56833c:      	calll	0x57231f <.text+0x17131f>
  568341:      	movl	$0xc6fea8, %ecx         # imm = 0xC6FEA8
  568346:      	calll	0x550ba1 <.text+0x14fba1>
  56834b:      	jmp	0x567650 <.text+0x166650>
  568350:      	pushl	-0x28(%ebp)
  568353:      	movl	0xc70348, %ecx
  568359:      	pushl	%ebx
  56835a:      	calll	0x56f3dc <.text+0x16e3dc>
  56835f:      	testl	%eax, %eax
  568361:      	je	0x5683ab <.text+0x1673ab>
  568363:      	movl	0x5ce614, %ebx
  568369:      	pushl	%edi
  56836a:      	pushl	%esi
  56836b:      	calll	*%ebx
  56836d:      	pushl	%edi
  56836e:      	pushl	%esi
  56836f:      	calll	*0x5ce530
  568375:      	pushl	%edi
  568376:      	movl	%edi, 0xc702a8
  56837c:      	calll	0x57be22 <.text+0x17ae22>
  568381:      	pushl	0xc70354
  568387:      	xorl	%edi, %edi
  568389:      	incl	%edi
  56838a:      	pushl	%esi
  56838b:      	movl	%edi, 0xc702a8
  568391:      	calll	0x570cce <.text+0x16fcce>
  568396:      	addl	$0xc, %esp
  568399:      	pushl	%edi
  56839a:      	pushl	%esi
  56839b:      	calll	*0x5ce530
  5683a1:      	pushl	$0x5
  5683a3:      	pushl	%esi
  5683a4:      	calll	*%ebx
  5683a6:      	jmp	0x567650 <.text+0x166650>
  5683ab:      	pushl	-0x28(%ebp)
  5683ae:      	movl	0xc7034c, %ecx
  5683b4:      	pushl	%ebx
  5683b5:      	calll	0x56f3dc <.text+0x16e3dc>
  5683ba:      	testl	%eax, %eax
  5683bc:      	je	0x56857b <.text+0x16757b>
  5683c2:      	movl	0x5ce530, %ebx
  5683c8:      	pushl	%edi
  5683c9:      	pushl	%esi
  5683ca:      	calll	*%ebx
  5683cc:      	pushl	%esi
  5683cd:      	movl	%edi, 0xc702a8
  5683d3:      	calll	0x56e640 <.text+0x16d640>
  5683d8:      	popl	%ecx
  5683d9:      	testl	%eax, %eax
  5683db:      	jne	0x5683fd <.text+0x1673fd>
  5683dd:      	pushl	0xc70354
  5683e3:      	pushl	%esi
  5683e4:      	calll	0x570cce <.text+0x16fcce>
  5683e9:      	popl	%ecx
  5683ea:      	xorl	%edi, %edi
  5683ec:      	popl	%ecx
  5683ed:      	incl	%edi
  5683ee:      	pushl	%edi
  5683ef:      	pushl	%esi
  5683f0:      	calll	*%ebx
  5683f2:      	movl	%edi, 0xc702a8
  5683f8:      	jmp	0x567650 <.text+0x166650>
  5683fd:      	movl	0xc702d0, %eax
  568402:      	movl	0x5ce538, %ebx
  568408:      	cmpl	%edi, %eax
  56840a:      	je	0x568416 <.text+0x167416>
  56840c:      	pushl	%eax
  56840d:      	pushl	%esi
  56840e:      	calll	*%ebx
  568410:      	movl	%edi, 0xc702d0
  568416:      	pushl	%edi
  568417:      	pushl	$0x32
  568419:      	pushl	$0x1
  56841b:      	pushl	%esi
  56841c:      	movl	%edi, 0xc702a8
  568422:      	calll	*0x5ce534
  568428:      	pushl	%edi
  568429:      	pushl	$0x553f12               # imm = 0x553F12
  56842e:      	pushl	0xc6f4c0
  568434:      	movl	%eax, 0xc702d0
  568439:      	pushl	$0x9a
  56843e:      	pushl	0xc6f4bc
  568444:      	calll	0x571361 <.text+0x170361>
  568449:      	addl	$0x14, %esp
  56844c:      	testl	%eax, %eax
  56844e:      	je	0x56854a <.text+0x16754a>
  568454:      	pushl	0xc70354
  56845a:      	pushl	%esi
  56845b:      	calll	0x570cce <.text+0x16fcce>
  568460:      	cmpb	$0x0, 0xc6f606
  568467:      	popl	%ecx
  568468:      	popl	%ecx
  568469:      	jne	0x568481 <.text+0x167481>
  56846b:      	pushl	$0x5f0a64               # imm = 0x5F0A64
  568470:      	pushl	$0xc6f4a8               # imm = 0xC6F4A8
  568475:      	calll	0x555cce <.text+0x154cce>
  56847a:      	popl	%ecx
  56847b:      	popl	%ecx
  56847c:      	jmp	0x56854a <.text+0x16754a>
  568481:      	movl	%esi, %ecx
  568483:      	calll	0x556e23 <.text+0x155e23>
  568488:      	testl	%eax, %eax
  56848a:      	je	0x56854a <.text+0x16754a>
  568490:      	movl	0xc702d0, %eax
  568495:      	cmpl	%edi, %eax
  568497:      	je	0x5684a3 <.text+0x1674a3>
  568499:      	pushl	%eax
  56849a:      	pushl	%esi
  56849b:      	calll	*%ebx
  56849d:      	movl	%edi, 0xc702d0
  5684a3:      	movl	$0xc6fe68, %ecx         # imm = 0xC6FE68
  5684a8:      	movl	$0xc9, 0xc6fd2c
  5684b2:      	movl	%edi, 0xc6fda4
  5684b8:      	movl	$0x4, 0xc6fd28
  5684c2:      	calll	0x55b376 <.text+0x15a376>
  5684c7:      	movl	$0xc6fe28, %ebx         # imm = 0xC6FE28
  5684cc:      	movl	%ebx, %ecx
  5684ce:      	calll	0x55b376 <.text+0x15a376>
  5684d3:      	pushl	%edi
  5684d4:      	pushl	%esi
  5684d5:      	calll	*0x5ce614
  5684db:      	calll	0x563039 <.text+0x162039>
  5684e0:      	pushl	0xc70354
  5684e6:      	movl	%eax, -0x30(%ebp)
  5684e9:      	pushl	%esi
  5684ea:      	calll	0x570cce <.text+0x16fcce>
  5684ef:      	popl	%ecx
  5684f0:      	popl	%ecx
  5684f1:      	cmpl	%edi, -0x30(%ebp)
  5684f4:      	je	0x568504 <.text+0x167504>
  5684f6:      	pushl	$0x1
  5684f8:      	pushl	%esi
  5684f9:      	calll	0x56e64a <.text+0x16d64a>
  5684fe:      	popl	%ecx
  5684ff:      	jmp	0x565bb1 <.text+0x164bb1>
  568504:      	pushl	$0x5
  568506:      	pushl	%esi
  568507:      	calll	*0x5ce614
  56850d:      	pushl	%edi
  56850e:      	pushl	$0x32
  568510:      	pushl	$0x1
  568512:      	pushl	%esi
  568513:      	calll	*0x5ce534
  568519:      	movl	%ebx, %ecx
  56851b:      	movl	%eax, 0xc702d0
  568520:      	calll	0x55075f <.text+0x14f75f>
  568525:      	movl	$0xc6fdec, %ecx         # imm = 0xC6FDEC
  56852a:      	calll	0x558b53 <.text+0x157b53>
  56852f:      	movl	$0xc6fea8, %ecx         # imm = 0xC6FEA8
  568534:      	calll	0x558b53 <.text+0x157b53>
  568539:      	movl	$0xc6fe68, %ecx         # imm = 0xC6FE68
  56853e:      	calll	0x55b376 <.text+0x15a376>
  568543:      	movl	%ebx, %ecx
  568545:      	calll	0x55b376 <.text+0x15a376>
  56854a:      	pushl	0xc70354
  568550:      	pushl	%esi
  568551:      	calll	0x570cce <.text+0x16fcce>
  568556:      	popl	%ecx
  568557:      	popl	%ecx
  568558:      	xorl	%edi, %edi
  56855a:      	incl	%edi
  56855b:      	pushl	%edi
  56855c:      	pushl	%esi
  56855d:      	calll	*0x5ce530
  568563:      	pushl	$0x3fd                  # imm = 0x3FD
  568568:      	pushl	%esi
  568569:      	calll	*0x5ce53c
  56856f:      	pushl	%eax
  568570:      	calll	*0x5ce5f4
  568576:      	jmp	0x5683f2 <.text+0x1673f2>
  56857b:      	pushl	-0x28(%ebp)
  56857e:      	movl	0xc70350, %ecx
  568584:      	pushl	%ebx
  568585:      	calll	0x56f3dc <.text+0x16e3dc>
  56858a:      	testl	%eax, %eax
  56858c:      	je	0x5686bc <.text+0x1676bc>
  568592:      	cmpl	$0x1, 0xc6fc70
  568599:      	movl	0x5ce530, %ebx
  56859f:      	jne	0x568613 <.text+0x167613>
  5685a1:      	andl	%edi, 0xc702a8
  5685a7:      	pushl	$0x0
  5685a9:      	pushl	%esi
  5685aa:      	calll	*%ebx
  5685ac:      	movl	$0x5f0a50, %esi         # imm = 0x5F0A50
  5685b1:      	leal	0x41c(%ebp), %edi
  5685b7:      	movsl	(%esi), %es:(%edi)
  5685b8:      	movsl	(%esi), %es:(%edi)
  5685b9:      	movsl	(%esi), %es:(%edi)
  5685ba:      	movsl	(%esi), %es:(%edi)
  5685bb:      	movsw	(%esi), %es:(%edi)
  5685bd:      	pushl	$0xee
  5685c2:      	xorl	%esi, %esi
  5685c4:      	leal	0x42e(%ebp), %eax
  5685ca:      	pushl	%esi
  5685cb:      	pushl	%eax
  5685cc:      	calll	0x5c6dfc <.text+0x1c5dfc>
  5685d1:      	leal	0x41c(%ebp), %eax
  5685d7:      	pushl	%eax
  5685d8:      	pushl	$0x5f0a44               # imm = 0x5F0A44
  5685dd:      	pushl	$0x5ef4d4               # imm = 0x5EF4D4
  5685e2:      	calll	0x4ba7c3 <.text+0xb97c3>
  5685e7:      	leal	0x41c(%ebp), %eax
  5685ed:      	pushl	%eax
  5685ee:      	pushl	-0x2c(%ebp)
  5685f1:      	calll	0x554e78 <.text+0x153e78>
  5685f6:      	xorl	%edi, %edi
  5685f8:      	incl	%edi
  5685f9:      	addl	$0x20, %esp
  5685fc:      	cmpl	%edi, %eax
  5685fe:      	je	0x568618 <.text+0x167618>
  568600:      	pushl	%edi
  568601:      	pushl	-0x2c(%ebp)
  568604:      	movl	%edi, 0xc702a8
  56860a:      	calll	*%ebx
  56860c:      	movl	%edi, %eax
  56860e:      	jmp	0x568fe4 <.text+0x167fe4>
  568613:      	xorl	%edi, %edi
  568615:      	incl	%edi
  568616:      	xorl	%esi, %esi
  568618:      	movl	0xc702d0, %eax
  56861d:      	cmpl	%esi, %eax
  56861f:      	je	0x568631 <.text+0x167631>
  568621:      	pushl	%eax
  568622:      	pushl	-0x2c(%ebp)
  568625:      	calll	*0x5ce538
  56862b:      	movl	%esi, 0xc702d0
  568631:      	pushl	%esi
  568632:      	pushl	-0x2c(%ebp)
  568635:      	calll	*%ebx
  568637:      	pushl	%edi
  568638:      	movl	%esi, 0xc702a8
  56863e:      	calll	0x4dd22f <.text+0xdc22f>
  568643:      	pushl	%esi
  568644:      	pushl	0xba7724
  56864a:      	calll	0x5860be <.text+0x1850be>
  56864f:      	addl	$0xc, %esp
  568652:      	testl	%eax, %eax
  568654:      	je	0x5686a3 <.text+0x1676a3>
  568656:      	pushl	$0x8
  568658:      	popl	%ecx
  568659:      	pushl	$0xe0
  56865e:      	leal	0x43c(%ebp), %eax
  568664:      	pushl	$0x0
  568666:      	movl	$0x5f0cb0, %esi         # imm = 0x5F0CB0
  56866b:      	leal	0x41c(%ebp), %edi
  568671:      	pushl	%eax
  568672:      	rep		movsl	(%esi), %es:(%edi)
  568674:      	calll	0x5c6dfc <.text+0x1c5dfc>
  568679:      	leal	0x41c(%ebp), %eax
  56867f:      	pushl	%eax
  568680:      	pushl	$0x5f0ca0               # imm = 0x5F0CA0
  568685:      	pushl	$0x5ef520               # imm = 0x5EF520
  56868a:      	calll	0x4ba7c3 <.text+0xb97c3>
  56868f:      	leal	0x41c(%ebp), %eax
  568695:      	pushl	%eax
  568696:      	pushl	-0x2c(%ebp)
  568699:      	calll	0x553e75 <.text+0x152e75>
  56869e:      	addl	$0x20, %esp
  5686a1:      	xorl	%esi, %esi
  5686a3:      	pushl	%esi
  5686a4:      	pushl	-0x2c(%ebp)
  5686a7:      	movl	%esi, 0xba7724
  5686ad:      	movl	$0xd, 0xc70520
  5686b7:      	jmp	0x5684f9 <.text+0x1674f9>
  5686bc:      	pushl	-0x28(%ebp)
  5686bf:      	movl	0xc70344, %ecx
  5686c5:      	pushl	%ebx
  5686c6:      	calll	0x56f3dc <.text+0x16e3dc>
  5686cb:      	testl	%eax, %eax
  5686cd:      	je	0x567650 <.text+0x166650>
  5686d3:      	movl	0x5ce530, %ebx
  5686d9:      	pushl	%edi
  5686da:      	pushl	%esi
  5686db:      	calll	*%ebx
  5686dd:      	movl	0xc702d0, %eax
  5686e2:      	movl	%edi, 0xc702a8
  5686e8:      	cmpl	%edi, %eax
  5686ea:      	je	0x5686fa <.text+0x1676fa>
  5686ec:      	pushl	%eax
  5686ed:      	pushl	%esi
  5686ee:      	calll	*0x5ce538
  5686f4:      	movl	%edi, 0xc702d0
  5686fa:      	movl	$0xc6fe68, %ecx         # imm = 0xC6FE68
  5686ff:      	calll	0x55b15f <.text+0x15a15f>
  568704:      	movl	%eax, -0x34(%ebp)
  568707:      	cmpl	%edi, %eax
  568709:      	jne	0x56872d <.text+0x16772d>
  56870b:      	pushl	%edi
  56870c:      	xorl	%edi, %edi
  56870e:      	pushl	$0x32
  568710:      	incl	%edi
  568711:      	pushl	%edi
  568712:      	pushl	%esi
  568713:      	calll	*0x5ce534
  568719:      	movl	%eax, 0xc702d0
  56871e:      	pushl	%edi
  56871f:      	pushl	%esi
  568720:      	calll	*%ebx
  568722:      	movl	%edi, 0xc702a8
  568728:      	jmp	0x56860c <.text+0x16760c>
  56872d:      	movl	$0xc6fe68, %ecx         # imm = 0xC6FE68
  568732:      	calll	0x55af25 <.text+0x159f25>
  568737:      	pushl	%eax
  568738:      	calll	0x552d39 <.text+0x151d39>
  56873d:      	popl	%ecx
  56873e:      	testl	%eax, %eax
  568740:      	jne	0x568770 <.text+0x167770>
  568742:      	pushl	%esi
  568743:      	calll	0x56e640 <.text+0x16d640>
  568748:      	popl	%ecx
  568749:      	testl	%eax, %eax
  56874b:      	jne	0x568770 <.text+0x167770>
  56874d:      	pushl	%edi
  56874e:      	pushl	$0x32
  568750:      	xorl	%edi, %edi
  568752:      	incl	%edi
  568753:      	pushl	%edi
  568754:      	pushl	%esi
  568755:      	calll	*0x5ce534
  56875b:      	pushl	0xc70354
  568761:      	movl	%eax, 0xc702d0
  568766:      	pushl	%esi
  568767:      	calll	0x570cce <.text+0x16fcce>
  56876c:      	popl	%ecx
  56876d:      	popl	%ecx
  56876e:      	jmp	0x56871e <.text+0x16771e>
  568770:      	movl	-0x34(%ebp), %esi
  568773:      	pushl	$0x17
  568775:      	popl	%ecx
  568776:      	pushl	-0x34(%ebp)
  568779:      	movl	$0xc6f810, %edi         # imm = 0xC6F810
  56877e:      	rep		movsl	(%esi), %es:(%edi)
  568780:      	movsw	(%esi), %es:(%edi)
  568782:      	movsb	(%esi), %es:(%edi)
  568783:      	calll	0x4dd37a <.text+0xdc37a>
  568788:      	popl	%ecx
  568789:      	calll	0x4dd321 <.text+0xdc321>
  56878e:      	andl	$0x0, 0xc6fda4
  568795:      	movl	$0xfa01, %eax           # imm = 0xFA01
  56879a:      	movl	$0xc6fe68, %ecx         # imm = 0xC6FE68
  56879f:      	movw	%ax, 0x62aea4
  5687a5:      	movl	$0xc9, 0xc6fd2c
  5687af:      	movl	$0x4, 0xc6fd28
  5687b9:      	calll	0x55b376 <.text+0x15a376>
  5687be:      	movl	$0xc6fe28, %ebx         # imm = 0xC6FE28
  5687c3:      	movl	%ebx, %ecx
  5687c5:      	calll	0x55b376 <.text+0x15a376>
  5687ca:      	xorl	%edx, %edx
  5687cc:      	movb	0xc6f847(%edx), %al
  5687d2:      	andb	$0x7f, %al
  5687d4:      	leal	0x72c(%ebp,%edx), %ecx
  5687db:      	movb	%al, (%ecx)
  5687dd:      	cmpb	$0x2e, %al
  5687df:      	jne	0x5687e4 <.text+0x1677e4>
  5687e1:      	movb	$0x0, (%ecx)
  5687e4:      	incl	%edx
  5687e5:      	cmpl	$0xa, %edx
  5687e8:      	jl	0x5687cc <.text+0x1677cc>
  5687ea:      	cmpb	$0x0, 0x72c(%ebp)
  5687f1:      	movb	$0x0, 0x736(%ebp)
  5687f8:      	jne	0x568827 <.text+0x167827>
  5687fa:      	pushl	$0x0
  5687fc:      	pushl	$0x32
  5687fe:      	xorl	%esi, %esi
  568800:      	incl	%esi
  568801:      	pushl	%esi
  568802:      	pushl	-0x2c(%ebp)
  568805:      	calll	*0x5ce534
  56880b:      	pushl	%esi
  56880c:      	pushl	-0x2c(%ebp)
  56880f:      	movl	%eax, 0xc702d0
  568814:      	calll	*0x5ce530
  56881a:      	movl	%esi, 0xc702a8
  568820:      	movl	%esi, %eax
  568822:      	jmp	0x568fe4 <.text+0x167fe4>
  568827:      	pushl	$0xc6f827               # imm = 0xC6F827
  56882c:      	calll	0x4dd8f9 <.text+0xdc8f9>
  568831:      	leal	0x72c(%ebp), %eax
  568837:      	pushl	%eax
  568838:      	pushl	$0x5ee828               # imm = 0x5EE828
  56883d:      	movl	$0xd42330, %esi         # imm = 0xD42330
  568842:      	pushl	%esi
  568843:      	calll	*0x5ce49c
  568849:      	pushl	%esi
  56884a:      	calll	0x4dd403 <.text+0xdc403>
  56884f:      	pushl	$0x5ef34c               # imm = 0x5EF34C
  568854:      	calll	0x546add <.text+0x145add>
  568859:      	leal	0x72c(%ebp), %eax
  56885f:      	pushl	%eax
  568860:      	calll	0x546d28 <.text+0x145d28>
  568865:      	addl	$0x1c, %esp
  568868:      	movl	%eax, %esi
  56886a:      	calll	0x546ac4 <.text+0x145ac4>
  56886f:      	cmpl	0xc6f85f, %esi
  568875:      	je	0x56897c <.text+0x16797c>
  56887b:      	cmpl	0xba721c, %esi
  568881:      	je	0x56897c <.text+0x16797c>
  568887:      	leal	0x72c(%ebp), %eax
  56888d:      	pushl	%eax
  56888e:      	calll	0x546eb3 <.text+0x145eb3>
  568893:      	popl	%ecx
  568894:      	testl	%eax, %eax
  568896:      	je	0x5688e7 <.text+0x1678e7>
  568898:      	pushl	$0xa
  56889a:      	popl	%ecx
  56889b:      	movl	$0x5f0a18, %esi         # imm = 0x5F0A18
  5688a0:      	leal	0x41c(%ebp), %edi
  5688a6:      	rep		movsl	(%esi), %es:(%edi)
  5688a8:      	pushl	$0xd7
  5688ad:      	leal	0x445(%ebp), %eax
  5688b3:      	pushl	$0x0
  5688b5:      	pushl	%eax
  5688b6:      	movsb	(%esi), %es:(%edi)
  5688b7:      	calll	0x5c6dfc <.text+0x1c5dfc>
  5688bc:      	leal	0x41c(%ebp), %eax
  5688c2:      	pushl	%eax
  5688c3:      	pushl	$0x5f02e4               # imm = 0x5F02E4
  5688c8:      	pushl	$0x5ef520               # imm = 0x5EF520
  5688cd:      	calll	0x4ba7c3 <.text+0xb97c3>
  5688d2:      	movl	-0x2c(%ebp), %esi
  5688d5:      	leal	0x41c(%ebp), %eax
  5688db:      	pushl	%eax
  5688dc:      	pushl	%esi
  5688dd:      	calll	0x553e75 <.text+0x152e75>
  5688e2:      	addl	$0x20, %esp
  5688e5:      	jmp	0x56893b <.text+0x16793b>
  5688e7:      	pushl	$0x5
  5688e9:      	popl	%ecx
  5688ea:      	movl	$0x5ef6fc, %esi         # imm = 0x5EF6FC
  5688ef:      	leal	0x31c(%ebp), %edi
  5688f5:      	rep		movsl	(%esi), %es:(%edi)
  5688f7:      	pushl	$0xeb
  5688fc:      	leal	0x331(%ebp), %eax
  568902:      	pushl	$0x0
  568904:      	pushl	%eax
  568905:      	movsb	(%esi), %es:(%edi)
  568906:      	calll	0x5c6dfc <.text+0x1c5dfc>
  56890b:      	leal	0x31c(%ebp), %eax
  568911:      	pushl	%eax
  568912:      	pushl	$0x5ef6f0               # imm = 0x5EF6F0
  568917:      	pushl	$0x5ef520               # imm = 0x5EF520
  56891c:      	calll	0x4ba7c3 <.text+0xb97c3>
  568921:      	movl	-0x2c(%ebp), %esi
  568924:      	leal	0x72c(%ebp), %eax
  56892a:      	pushl	%eax
  56892b:      	leal	0x31c(%ebp), %eax
  568931:      	pushl	%eax
  568932:      	pushl	%esi
  568933:      	calll	0x553e75 <.text+0x152e75>
  568938:      	addl	$0x24, %esp
  56893b:      	cmpl	$0x0, 0xc704f4
  568942:      	movl	$0x1, 0xc702a8
  56894c:      	jne	0x56897f <.text+0x16797f>
  56894e:      	pushl	0xc70354
  568954:      	pushl	%esi
  568955:      	calll	0x570cce <.text+0x16fcce>
  56895a:      	popl	%ecx
  56895b:      	popl	%ecx
  56895c:      	pushl	$0x0
  56895e:      	pushl	$0x32
  568960:      	pushl	$0x1
  568962:      	pushl	%esi
  568963:      	calll	*0x5ce534
  568969:      	pushl	$0x1
  56896b:      	pushl	%esi
  56896c:      	movl	%eax, 0xc702d0
  568971:      	calll	*0x5ce530
  568977:      	jmp	0x567785 <.text+0x166785>
  56897c:      	movl	-0x2c(%ebp), %esi
  56897f:      	pushl	$0x1
  568981:      	calll	0x4dd8d5 <.text+0xdc8d5>
  568986:      	pushl	$0x0
  568988:      	calll	0x4dd8e3 <.text+0xdc8e3>
  56898d:      	pushl	%esi
  56898e:      	calll	0x556f33 <.text+0x155f33>
  568993:      	movl	0x5ce614, %edi
  568999:      	addl	$0xc, %esp
  56899c:      	testl	%eax, %eax
  56899e:      	je	0x5689ca <.text+0x1679ca>
  5689a0:      	pushl	$0x0
  5689a2:      	pushl	%esi
  5689a3:      	calll	*%edi
  5689a5:      	calll	0x563039 <.text+0x162039>
  5689aa:      	testl	%eax, %eax
  5689ac:      	je	0x5689ca <.text+0x1679ca>
  5689ae:      	pushl	0xc70354
  5689b4:      	pushl	%esi
  5689b5:      	calll	0x570cce <.text+0x16fcce>
  5689ba:      	pushl	$0x1
  5689bc:      	pushl	%esi
  5689bd:      	calll	0x56e64a <.text+0x16d64a>
  5689c2:      	addl	$0x10, %esp
  5689c5:      	jmp	0x567785 <.text+0x166785>
  5689ca:      	pushl	$0x0
  5689cc:      	pushl	$0x32
  5689ce:      	pushl	$0x1
  5689d0:      	pushl	%esi
  5689d1:      	calll	*0x5ce534
  5689d7:      	pushl	0xc70354
  5689dd:      	movl	%eax, 0xc702d0
  5689e2:      	pushl	%esi
  5689e3:      	calll	0x570cce <.text+0x16fcce>
  5689e8:      	popl	%ecx
  5689e9:      	popl	%ecx
  5689ea:      	movl	%ebx, %ecx
  5689ec:      	calll	0x55075f <.text+0x14f75f>
  5689f1:      	pushl	$0x5
  5689f3:      	pushl	%esi
  5689f4:      	calll	*%edi
  5689f6:      	xorl	%edi, %edi
  5689f8:      	incl	%edi
  5689f9:      	pushl	%edi
  5689fa:      	pushl	%esi
  5689fb:      	calll	*0x5ce530
  568a01:      	jmp	0x568722 <.text+0x167722>
  568a06:      	movl	0xc7033c, %ecx
  568a0c:      	movl	%ebx, %esi
  568a0e:      	shrl	$0x10, %esi
  568a11:      	movzwl	%bx, %edi
  568a14:      	pushl	%esi
  568a15:      	pushl	%edi
  568a16:      	calll	0x56f3dc <.text+0x16e3dc>
  568a1b:      	testl	%eax, %eax
  568a1d:      	je	0x568a2c <.text+0x167a2c>
  568a1f:      	movl	0xc7033c, %ecx
  568a25:      	pushl	$0x0
  568a27:      	jmp	0x568c5d <.text+0x167c5d>
  568a2c:      	movl	0xc70338, %ecx
  568a32:      	pushl	%esi
  568a33:      	pushl	%edi
  568a34:      	calll	0x56f3dc <.text+0x16e3dc>
  568a39:      	testl	%eax, %eax
  568a3b:      	je	0x568a4a <.text+0x167a4a>
  568a3d:      	movl	0xc70338, %ecx
  568a43:      	pushl	$0x0
  568a45:      	jmp	0x568c5d <.text+0x167c5d>
  568a4a:      	movl	0xc70340, %ecx
  568a50:      	pushl	%esi
  568a51:      	pushl	%edi
  568a52:      	calll	0x56f3dc <.text+0x16e3dc>
  568a57:      	testl	%eax, %eax
  568a59:      	je	0x568a68 <.text+0x167a68>
  568a5b:      	movl	0xc70340, %ecx
  568a61:      	pushl	$0x0
  568a63:      	jmp	0x568c5d <.text+0x167c5d>
  568a68:      	movl	0xc70334, %ecx
  568a6e:      	pushl	%esi
  568a6f:      	pushl	%edi
  568a70:      	calll	0x56f3dc <.text+0x16e3dc>
  568a75:      	testl	%eax, %eax
  568a77:      	je	0x568a86 <.text+0x167a86>
  568a79:      	movl	0xc70334, %ecx
  568a7f:      	pushl	$0x0
  568a81:      	jmp	0x568c5d <.text+0x167c5d>
  568a86:      	movl	0xc70330, %ecx
  568a8c:      	xorl	%ebx, %ebx
  568a8e:      	cmpl	%ebx, %ecx
  568a90:      	je	0x568aa8 <.text+0x167aa8>
  568a92:      	pushl	%esi
  568a93:      	pushl	%edi
  568a94:      	calll	0x56f3dc <.text+0x16e3dc>
  568a99:      	testl	%eax, %eax
  568a9b:      	je	0x568aa8 <.text+0x167aa8>
  568a9d:      	movl	0xc70330, %ecx
  568aa3:      	jmp	0x568c5c <.text+0x167c5c>
  568aa8:      	movl	0xc7032c, %ecx
  568aae:      	cmpl	%ebx, %ecx
  568ab0:      	je	0x568ac8 <.text+0x167ac8>
  568ab2:      	pushl	%esi
  568ab3:      	pushl	%edi
  568ab4:      	calll	0x56f3dc <.text+0x16e3dc>
  568ab9:      	testl	%eax, %eax
  568abb:      	je	0x568ac8 <.text+0x167ac8>
  568abd:      	movl	0xc7032c, %ecx
  568ac3:      	jmp	0x568c5c <.text+0x167c5c>
  568ac8:      	movl	0xc70328, %ecx
  568ace:      	pushl	%esi
  568acf:      	pushl	%edi
  568ad0:      	calll	0x56f3dc <.text+0x16e3dc>
  568ad5:      	testl	%eax, %eax
  568ad7:      	je	0x568ae4 <.text+0x167ae4>
  568ad9:      	movl	0xc70328, %ecx
  568adf:      	jmp	0x568c5c <.text+0x167c5c>
  568ae4:      	movl	0xc70324, %ecx
  568aea:      	pushl	%esi
  568aeb:      	pushl	%edi
  568aec:      	calll	0x56f3dc <.text+0x16e3dc>
  568af1:      	testl	%eax, %eax
  568af3:      	je	0x568b00 <.text+0x167b00>
  568af5:      	movl	0xc70324, %ecx
  568afb:      	jmp	0x568c5c <.text+0x167c5c>
  568b00:      	movl	0xc70320, %ecx
  568b06:      	pushl	%esi
  568b07:      	pushl	%edi
  568b08:      	calll	0x56f3dc <.text+0x16e3dc>
  568b0d:      	testl	%eax, %eax
  568b0f:      	je	0x568b1c <.text+0x167b1c>
  568b11:      	movl	0xc70320, %ecx
  568b17:      	jmp	0x568c5c <.text+0x167c5c>
  568b1c:      	movl	0xc7031c, %ecx
  568b22:      	pushl	%esi
  568b23:      	pushl	%edi
  568b24:      	calll	0x56f3dc <.text+0x16e3dc>
  568b29:      	testl	%eax, %eax
  568b2b:      	je	0x568b38 <.text+0x167b38>
  568b2d:      	movl	0xc7031c, %ecx
  568b33:      	jmp	0x568c5c <.text+0x167c5c>
  568b38:      	movl	0xc70318, %ecx
  568b3e:      	pushl	%esi
  568b3f:      	pushl	%edi
  568b40:      	calll	0x56f3dc <.text+0x16e3dc>
  568b45:      	testl	%eax, %eax
  568b47:      	je	0x568b54 <.text+0x167b54>
  568b49:      	movl	0xc70318, %ecx
  568b4f:      	jmp	0x568c5c <.text+0x167c5c>
  568b54:      	movl	0xc70314, %ecx
  568b5a:      	pushl	%esi
  568b5b:      	pushl	%edi
  568b5c:      	calll	0x56f3dc <.text+0x16e3dc>
  568b61:      	testl	%eax, %eax
  568b63:      	je	0x568b70 <.text+0x167b70>
  568b65:      	movl	0xc70314, %ecx
  568b6b:      	jmp	0x568c5c <.text+0x167c5c>
  568b70:      	movl	0xc70310, %ecx
  568b76:      	pushl	%esi
  568b77:      	pushl	%edi
  568b78:      	calll	0x56f3dc <.text+0x16e3dc>
  568b7d:      	testl	%eax, %eax
  568b7f:      	je	0x568b8c <.text+0x167b8c>
  568b81:      	movl	0xc70310, %ecx
  568b87:      	jmp	0x568c5c <.text+0x167c5c>
  568b8c:      	movl	0xc7030c, %ecx
  568b92:      	pushl	%esi
  568b93:      	pushl	%edi
  568b94:      	calll	0x56f3dc <.text+0x16e3dc>
  568b99:      	testl	%eax, %eax
  568b9b:      	je	0x568ba8 <.text+0x167ba8>
  568b9d:      	movl	0xc7030c, %ecx
  568ba3:      	jmp	0x568c5c <.text+0x167c5c>
  568ba8:      	movl	0xc70308, %ecx
  568bae:      	pushl	%esi
  568baf:      	pushl	%edi
  568bb0:      	calll	0x56f3dc <.text+0x16e3dc>
  568bb5:      	testl	%eax, %eax
  568bb7:      	je	0x568bc4 <.text+0x167bc4>
  568bb9:      	movl	0xc70308, %ecx
  568bbf:      	jmp	0x568c5c <.text+0x167c5c>
  568bc4:      	movl	0xc70304, %ecx
  568bca:      	pushl	%esi
  568bcb:      	pushl	%edi
  568bcc:      	calll	0x56f3dc <.text+0x16e3dc>
  568bd1:      	testl	%eax, %eax
  568bd3:      	je	0x568bdd <.text+0x167bdd>
  568bd5:      	movl	0xc70304, %ecx
  568bdb:      	jmp	0x568c5c <.text+0x167c5c>
  568bdd:      	movl	0xc70300, %ecx
  568be3:      	pushl	%esi
  568be4:      	pushl	%edi
  568be5:      	calll	0x56f3dc <.text+0x16e3dc>
  568bea:      	testl	%eax, %eax
  568bec:      	je	0x568bf6 <.text+0x167bf6>
  568bee:      	movl	0xc70300, %ecx
  568bf4:      	jmp	0x568c5c <.text+0x167c5c>
  568bf6:      	movl	0xc70348, %ecx
  568bfc:      	pushl	%esi
  568bfd:      	pushl	%edi
  568bfe:      	calll	0x56f3dc <.text+0x16e3dc>
  568c03:      	testl	%eax, %eax
  568c05:      	je	0x568c0f <.text+0x167c0f>
  568c07:      	movl	0xc70348, %ecx
  568c0d:      	jmp	0x568c5c <.text+0x167c5c>
  568c0f:      	movl	0xc7034c, %ecx
  568c15:      	pushl	%esi
  568c16:      	pushl	%edi
  568c17:      	calll	0x56f3dc <.text+0x16e3dc>
  568c1c:      	testl	%eax, %eax
  568c1e:      	je	0x568c28 <.text+0x167c28>
  568c20:      	movl	0xc7034c, %ecx
  568c26:      	jmp	0x568c5c <.text+0x167c5c>
  568c28:      	movl	0xc70350, %ecx
  568c2e:      	pushl	%esi
  568c2f:      	pushl	%edi
  568c30:      	calll	0x56f3dc <.text+0x16e3dc>
  568c35:      	testl	%eax, %eax
  568c37:      	je	0x568c41 <.text+0x167c41>
  568c39:      	movl	0xc70350, %ecx
  568c3f:      	jmp	0x568c5c <.text+0x167c5c>
  568c41:      	movl	0xc70344, %ecx
  568c47:      	pushl	%esi
  568c48:      	pushl	%edi
  568c49:      	calll	0x56f3dc <.text+0x16e3dc>
  568c4e:      	testl	%eax, %eax
  568c50:      	je	0x567650 <.text+0x166650>
  568c56:      	movl	0xc70344, %ecx
  568c5c:      	pushl	%ebx
  568c5d:      	pushl	$0x1
  568c5f:      	pushl	$0x2
  568c61:      	calll	0x57231f <.text+0x17131f>
  568c66:      	jmp	0x567650 <.text+0x166650>
  568c6b:      	movl	0xc70328, %ecx
  568c71:      	movl	%ebx, %esi
  568c73:      	movzwl	%bx, %edi
  568c76:      	xorl	%ebx, %ebx
  568c78:      	pushl	%ebx
  568c79:      	pushl	$0x1
  568c7b:      	shrl	$0x10, %esi
  568c7e:      	pushl	%esi
  568c7f:      	pushl	%edi
  568c80:      	calll	0x56f3dc <.text+0x16e3dc>
  568c85:      	movl	0xc70328, %ecx
  568c8b:      	pushl	%eax
  568c8c:      	calll	0x57231f <.text+0x17131f>
  568c91:      	movl	0xc70340, %ecx
  568c97:      	pushl	%ebx
  568c98:      	pushl	$0x1
  568c9a:      	pushl	%esi
  568c9b:      	pushl	%edi
  568c9c:      	calll	0x56f3dc <.text+0x16e3dc>
  568ca1:      	movl	0xc70340, %ecx
  568ca7:      	pushl	%eax
  568ca8:      	calll	0x57231f <.text+0x17131f>
  568cad:      	pushl	$0x5f05f4               # imm = 0x5F05F4
  568cb2:      	pushl	$0x5f0240               # imm = 0x5F0240
  568cb7:      	pushl	0xc702d4
  568cbd:      	pushl	0xc70340
  568cc3:      	calll	0x572c2d <.text+0x171c2d>
  568cc8:      	movl	0xc70338, %ecx
  568cce:      	addl	$0x10, %esp
  568cd1:      	pushl	%ebx
  568cd2:      	pushl	$0x1
  568cd4:      	pushl	%esi
  568cd5:      	pushl	%edi
  568cd6:      	calll	0x56f3dc <.text+0x16e3dc>
  568cdb:      	movl	0xc70338, %ecx
  568ce1:      	pushl	%eax
  568ce2:      	calll	0x57231f <.text+0x17131f>
  568ce7:      	pushl	$0x5f05e4               # imm = 0x5F05E4
  568cec:      	pushl	$0x5f0278               # imm = 0x5F0278
  568cf1:      	pushl	0xc702d4
  568cf7:      	pushl	0xc70338
  568cfd:      	calll	0x572c2d <.text+0x171c2d>
  568d02:      	movl	0xc7033c, %ecx
  568d08:      	addl	$0x10, %esp
  568d0b:      	pushl	%ebx
  568d0c:      	pushl	$0x1
  568d0e:      	pushl	%esi
  568d0f:      	pushl	%edi
  568d10:      	calll	0x56f3dc <.text+0x16e3dc>
  568d15:      	movl	0xc7033c, %ecx
  568d1b:      	pushl	%eax
  568d1c:      	calll	0x57231f <.text+0x17131f>
  568d21:      	pushl	$0x5f05ec               # imm = 0x5F05EC
  568d26:      	pushl	$0x5f0260               # imm = 0x5F0260
  568d2b:      	pushl	0xc702d4
  568d31:      	pushl	0xc7033c
  568d37:      	calll	0x572c2d <.text+0x171c2d>
  568d3c:      	movl	0xc70334, %ecx
  568d42:      	addl	$0x10, %esp
  568d45:      	pushl	%ebx
  568d46:      	pushl	$0x1
  568d48:      	pushl	%esi
  568d49:      	pushl	%edi
  568d4a:      	calll	0x56f3dc <.text+0x16e3dc>
  568d4f:      	movl	0xc70334, %ecx
  568d55:      	pushl	%eax
  568d56:      	calll	0x57231f <.text+0x17131f>
  568d5b:      	pushl	$0x5f0cd0               # imm = 0x5F0CD0
  568d60:      	pushl	$0x5f09fc               # imm = 0x5F09FC
  568d65:      	pushl	0xc702d4
  568d6b:      	pushl	0xc70334
  568d71:      	calll	0x572c2d <.text+0x171c2d>
  568d76:      	movl	0xc70330, %ecx
  568d7c:      	addl	$0x10, %esp
  568d7f:      	cmpl	%ebx, %ecx
  568d81:      	je	0x568db7 <.text+0x167db7>
  568d83:      	pushl	%ebx
  568d84:      	pushl	$0x1
  568d86:      	pushl	%esi
  568d87:      	pushl	%edi
  568d88:      	calll	0x56f3dc <.text+0x16e3dc>
  568d8d:      	movl	0xc70330, %ecx
  568d93:      	pushl	%eax
  568d94:      	calll	0x57231f <.text+0x17131f>
  568d99:      	pushl	$0x5f0d34               # imm = 0x5F0D34
  568d9e:      	pushl	$0x5f09f4               # imm = 0x5F09F4
  568da3:      	pushl	0xc702d4
  568da9:      	pushl	0xc70330
  568daf:      	calll	0x572c2d <.text+0x171c2d>
  568db4:      	addl	$0x10, %esp
  568db7:      	movl	0xc7032c, %ecx
  568dbd:      	cmpl	%ebx, %ecx
  568dbf:      	je	0x568df5 <.text+0x167df5>
  568dc1:      	pushl	%ebx
  568dc2:      	pushl	$0x1
  568dc4:      	pushl	%esi
  568dc5:      	pushl	%edi
  568dc6:      	calll	0x56f3dc <.text+0x16e3dc>
  568dcb:      	movl	0xc7032c, %ecx
  568dd1:      	pushl	%eax
  568dd2:      	calll	0x57231f <.text+0x17131f>
  568dd7:      	pushl	$0x5f0d30               # imm = 0x5F0D30
  568ddc:      	pushl	$0x5f09e8               # imm = 0x5F09E8
  568de1:      	pushl	0xc702d4
  568de7:      	pushl	0xc7032c
  568ded:      	calll	0x572c2d <.text+0x171c2d>
  568df2:      	addl	$0x10, %esp
  568df5:      	movl	0xc70350, %ecx
  568dfb:      	pushl	$0x0
  568dfd:      	xorl	%ebx, %ebx
  568dff:      	incl	%ebx
  568e00:      	pushl	%ebx
  568e01:      	pushl	%esi
  568e02:      	pushl	%edi
  568e03:      	calll	0x56f3dc <.text+0x16e3dc>
  568e08:      	movl	0xc70350, %ecx
  568e0e:      	pushl	%eax
  568e0f:      	calll	0x57231f <.text+0x17131f>
  568e14:      	movl	0xc7034c, %ecx
  568e1a:      	pushl	$0x0
  568e1c:      	pushl	%ebx
  568e1d:      	pushl	%esi
  568e1e:      	pushl	%edi
  568e1f:      	calll	0x56f3dc <.text+0x16e3dc>
  568e24:      	movl	0xc7034c, %ecx
  568e2a:      	pushl	%eax
  568e2b:      	calll	0x57231f <.text+0x17131f>
  568e30:      	movl	0xc70344, %ecx
  568e36:      	pushl	$0x0
  568e38:      	pushl	%ebx
  568e39:      	pushl	%esi
  568e3a:      	pushl	%edi
  568e3b:      	calll	0x56f3dc <.text+0x16e3dc>
  568e40:      	movl	0xc70344, %ecx
  568e46:      	pushl	%eax
  568e47:      	calll	0x57231f <.text+0x17131f>
  568e4c:      	movl	0xc70348, %ecx
  568e52:      	pushl	$0x0
  568e54:      	pushl	%ebx
  568e55:      	pushl	%esi
  568e56:      	pushl	%edi
  568e57:      	calll	0x56f3dc <.text+0x16e3dc>
  568e5c:      	movl	0xc70348, %ecx
  568e62:      	pushl	%eax
  568e63:      	calll	0x57231f <.text+0x17131f>
  568e68:      	movl	0xc70324, %ecx
  568e6e:      	pushl	$0x0
  568e70:      	pushl	%ebx
  568e71:      	pushl	%esi
  568e72:      	pushl	%edi
  568e73:      	calll	0x56f3dc <.text+0x16e3dc>
  568e78:      	movl	0xc70324, %ecx
  568e7e:      	pushl	%eax
  568e7f:      	calll	0x57231f <.text+0x17131f>
  568e84:      	movl	0xc70320, %ecx
  568e8a:      	pushl	$0x0
  568e8c:      	pushl	%ebx
  568e8d:      	pushl	%esi
  568e8e:      	pushl	%edi
  568e8f:      	calll	0x56f3dc <.text+0x16e3dc>
  568e94:      	movl	0xc70320, %ecx
  568e9a:      	pushl	%eax
  568e9b:      	calll	0x57231f <.text+0x17131f>
  568ea0:      	movl	0xc7031c, %ecx
  568ea6:      	pushl	$0x0
  568ea8:      	pushl	%ebx
  568ea9:      	pushl	%esi
  568eaa:      	pushl	%edi
  568eab:      	calll	0x56f3dc <.text+0x16e3dc>
  568eb0:      	movl	0xc7031c, %ecx
  568eb6:      	pushl	%eax
  568eb7:      	calll	0x57231f <.text+0x17131f>
  568ebc:      	movl	0xc70318, %ecx
  568ec2:      	pushl	$0x0
  568ec4:      	pushl	%ebx
  568ec5:      	pushl	%esi
  568ec6:      	pushl	%edi
  568ec7:      	calll	0x56f3dc <.text+0x16e3dc>
  568ecc:      	movl	0xc70318, %ecx
  568ed2:      	pushl	%eax
  568ed3:      	calll	0x57231f <.text+0x17131f>
  568ed8:      	movl	0xc70314, %ecx
  568ede:      	pushl	$0x0
  568ee0:      	pushl	%ebx
  568ee1:      	pushl	%esi
  568ee2:      	pushl	%edi
  568ee3:      	calll	0x56f3dc <.text+0x16e3dc>
  568ee8:      	pushl	%eax
  568ee9:      	movl	0xc70314, %ecx
  568eef:      	calll	0x57231f <.text+0x17131f>
  568ef4:      	movl	0xc70310, %ecx
  568efa:      	pushl	$0x0
  568efc:      	pushl	%ebx
  568efd:      	pushl	%esi
  568efe:      	pushl	%edi
  568eff:      	calll	0x56f3dc <.text+0x16e3dc>
  568f04:      	movl	0xc70310, %ecx
  568f0a:      	pushl	%eax
  568f0b:      	calll	0x57231f <.text+0x17131f>
  568f10:      	movl	0xc7030c, %ecx
  568f16:      	pushl	$0x0
  568f18:      	pushl	%ebx
  568f19:      	pushl	%esi
  568f1a:      	pushl	%edi
  568f1b:      	calll	0x56f3dc <.text+0x16e3dc>
  568f20:      	movl	0xc7030c, %ecx
  568f26:      	pushl	%eax
  568f27:      	calll	0x57231f <.text+0x17131f>
  568f2c:      	movl	0xc70308, %ecx
  568f32:      	pushl	$0x0
  568f34:      	pushl	%ebx
  568f35:      	pushl	%esi
  568f36:      	pushl	%edi
  568f37:      	calll	0x56f3dc <.text+0x16e3dc>
  568f3c:      	movl	0xc70308, %ecx
  568f42:      	pushl	%eax
  568f43:      	calll	0x57231f <.text+0x17131f>
  568f48:      	movl	0xc70304, %ecx
  568f4e:      	pushl	$0x0
  568f50:      	pushl	%ebx
  568f51:      	pushl	%esi
  568f52:      	pushl	%edi
  568f53:      	calll	0x56f3dc <.text+0x16e3dc>
  568f58:      	movl	0xc70304, %ecx
  568f5e:      	pushl	%eax
  568f5f:      	calll	0x57231f <.text+0x17131f>
  568f64:      	movl	0xc70300, %ecx
  568f6a:      	pushl	$0x0
  568f6c:      	pushl	%ebx
  568f6d:      	pushl	%esi
  568f6e:      	pushl	%edi
  568f6f:      	calll	0x56f3dc <.text+0x16e3dc>
  568f74:      	movl	0xc70300, %ecx
  568f7a:      	pushl	%eax
  568f7b:      	calll	0x57231f <.text+0x17131f>
  568f80:      	movl	0xc702d4, %eax
  568f85:      	pushl	$0x5
  568f87:      	movl	$0x5df2cc, %edi         # imm = 0x5DF2CC
  568f8c:      	leal	0x4(%eax), %esi
  568f8f:      	popl	%ecx
  568f90:      	xorl	%edx, %edx
  568f92:      	rep		cmpsb	%es:(%edi), (%esi)
  568f94:      	jne	0x567650 <.text+0x166650>
  568f9a:      	pushl	%ebx
  568f9b:      	movl	%eax, %ecx
  568f9d:      	calll	0x572935 <.text+0x171935>
  568fa2:      	jmp	0x567650 <.text+0x166650>
  568fa7:      	pushl	$0xff00                 # imm = 0xFF00
  568fac:      	pushl	%edi
  568fad:      	calll	*0x5ce04c
  568fb3:      	pushl	$0x2
  568fb5:      	pushl	%edi
  568fb6:      	calll	*0x5ce048
  568fbc:      	pushl	$0x0
  568fbe:      	pushl	%edi
  568fbf:      	calll	*0x5ce0d8
  568fc5:      	jmp	0x568fdc <.text+0x167fdc>
  568fc7:      	pushl	$0xff00                 # imm = 0xFF00
  568fcc:      	pushl	%edi
  568fcd:      	calll	*0x5ce04c
  568fd3:      	pushl	$0x1
  568fd5:      	pushl	%edi
  568fd6:      	calll	*0x5ce048
  568fdc:      	pushl	$0x4
  568fde:      	calll	*0x5ce040
  568fe4:      	movl	0x738(%ebp), %ecx
  568fea:      	popl	%edi
  568feb:      	popl	%esi
  568fec:      	xorl	%ebp, %ecx
  568fee:      	popl	%ebx
  568fef:      	calll	0x5c6d18 <.text+0x1c5d18>
  568ff4:      	addl	$0x73c, %ebp            # imm = 0x73C
  568ffa:      	leave
  568ffb:      	retl	$0x10
