; Entry: 004f6405
; Name: Gouraud_VUTile_Perspective_Texture_Map_polygon
; Signature: void Gouraud_VUTile_Perspective_Texture_Map_polygon(_GRAPHIC_BUFFER * param_1, POINT_3D * param_2, long param_3, POLYGON_SKIN param_4)
; Stop: 0x004f6dd0
; Reason: Exception while decompiling 004f6405: process: timeout 
; Command: C:\Program Files\LLVM\bin\llvm-objdump.EXE -d --no-show-raw-insn --start-address=0x004f6405 --stop-address=0x004f6dd0 C:\Users\istuart\Downloads\bzone15227\extracted\bzone.exe


C:\Users\istuart\Downloads\bzone15227\extracted\bzone.exe:	file format coff-i386

Disassembly of section .text:

00401000 <.text>:
  4f6405:      	pushl	%ebp
  4f6406:      	movl	%esp, %ebp
  4f6408:      	pushl	%ebx
  4f6409:      	pushl	%esi
  4f640a:      	pushl	%edi
  4f640b:      	movl	0x14(%ebp), %ebx
  4f640e:      	pushl	%ebp
  4f640f:      	movl	0xcfdbc0, %eax
  4f6414:      	subl	$0x700, %esp            # imm = 0x700
  4f641a:      	cmpl	%ebx, %eax
  4f641c:      	je	0x4f648c <.text+0xf548c>
  4f641e:      	movl	%ebx, 0xcfdbc0
  4f6424:      	leal	0xcfdbd8, %edx
  4f642a:      	movl	(%ebx), %eax
  4f642c:      	movl	0x4(%ebx), %ecx
  4f642f:      	leal	0x8(%ebx), %esi
  4f6432:      	movl	%ecx, 0x4(%esp)
  4f6436:      	movl	%eax, %edi
  4f6438:      	addl	$0x3, %ecx
  4f643b:      	addl	%esi, %edi
  4f643d:      	leal	(%esi,%eax,2), %ebx
  4f6440:      	leal	(%eax,%eax,2), %eax
  4f6443:      	movl	%esi, -0x4(%edx)
  4f6446:      	movl	%esi, -0x8(%edx)
  4f6449:      	movl	%esi, -0xc(%edx)
  4f644c:      	movl	%esi, -0x10(%edx)
  4f644f:      	movl	%esi, (%edx)
  4f6451:      	movl	%edi, 0x4(%edx)
  4f6454:      	movl	%ebx, 0x8(%edx)
  4f6457:      	addl	%eax, %esi
  4f6459:      	addl	%eax, %edi
  4f645b:      	addl	%eax, %ebx
  4f645d:      	addl	$0xc, %edx
  4f6460:      	subl	$0x3, %ecx
  4f6463:      	jge	0x4f644f <.text+0xf544f>
  4f6465:      	movl	0x4(%esp), %edx
  4f6469:      	movl	0xcfdbd4(,%edx,4), %eax
  4f6470:      	movl	%eax, 0xcfdbd8(,%edx,4)
  4f6477:      	movl	%eax, 0xcfdbdc(,%edx,4)
  4f647e:      	movl	%eax, 0xcfdbe0(,%edx,4)
  4f6485:      	movl	%eax, 0xcfdbe4(,%edx,4)
  4f648c:      	movl	0x14(%ebp), %ebx
  4f648f:      	movl	$0x186a0, %edx          # imm = 0x186A0
  4f6494:      	movl	0xc(%ebp), %esi
  4f6497:      	movl	0x10(%ebp), %eax
  4f649a:      	movl	(%ebx), %ecx
  4f649c:      	movl	0x4(%ebx), %edi
  4f649f:      	decl	%ecx
  4f64a0:      	decl	%edi
  4f64a1:      	fildl	0x4(%ebx)
  4f64a4:      	movl	%ecx, 0x18(%esp)
  4f64a8:      	movl	%edi, 0x1c(%esp)
  4f64ac:      	incl	%ecx
  4f64ad:      	movl	%esi, (%esp)
  4f64b0:      	shll	$0x3, %eax
  4f64b3:      	leal	0x8(%ebx), %edi
  4f64b6:      	fildl	(%ebx)
  4f64b8:      	movl	%ecx, 0x10(%esp)
  4f64bc:      	leal	(%eax,%eax,2), %ecx
  4f64bf:      	xorl	%eax, %eax
  4f64c1:      	movl	%edi, 0x24(%esp)
  4f64c5:      	flds	0x62c808
  4f64cb:      	fsubs	0x14(%esi,%eax)
  4f64cf:      	flds	0x4(%esi,%eax)
  4f64d3:      	faddl	0x632380
  4f64d9:      	fxch	%st(1)
  4f64db:      	flds	0xc(%esi,%eax)
  4f64df:      	fmul	%st(3), %st
  4f64e1:      	flds	0x10(%esi,%eax)
  4f64e5:      	fmul	%st(5), %st
  4f64e7:      	fxch	%st(3)
  4f64e9:      	fstpl	0x648(%esp)
  4f64f0:      	fxch	%st(1)
  4f64f2:      	fmuls	0x62c810
  4f64f8:      	fxch	%st(2)
  4f64fa:      	fstps	0x10(%esi,%eax)
  4f64fe:      	fstps	0xc(%esi,%eax)
  4f6502:      	fstps	0x14(%esi,%eax)
  4f6506:      	movl	0x648(%esp), %edi
  4f650d:      	movl	%eax, 0x328(%esp,%eax)
  4f6514:      	movl	%eax, 0x58(%esp,%eax)
  4f6518:      	movl	%edi, 0x344(%esp,%eax)
  4f651f:      	addl	$0x18, %eax
  4f6522:      	cmpl	%edx, %edi
  4f6524:      	jg	0x4f652a <.text+0xf552a>
  4f6526:      	movl	%eax, %ebx
  4f6528:      	movl	%edi, %edx
  4f652a:      	cmpl	%ecx, %eax
  4f652c:      	jne	0x4f64c5 <.text+0xf54c5>
  4f652e:      	subl	$0x18, %ebx
  4f6531:      	leal	-0x18(%eax), %ecx
  4f6534:      	fcompp
  4f6536:      	movl	$0x0, 0x328(%esp,%eax)
  4f6541:      	movl	%ecx, 0x40(%esp)
  4f6545:      	movl	0x8(%ebp), %edi
  4f6548:      	movl	%ebx, 0x6d0(%esp)
  4f654f:      	movl	%ebx, 0x6a0(%esp)
  4f6556:      	movl	%ebx, 0x6d4(%esp)
  4f655d:      	movl	%esi, %ebp
  4f655f:      	movl	0x20(%edi), %eax
  4f6562:      	movl	(%edi), %ecx
  4f6564:      	addl	%edx, %eax
  4f6566:      	movl	0x14(%edi), %esi
  4f6569:      	movl	0x1c(%edi), %edi
  4f656c:      	imull	%ecx
  4f656e:      	addl	%edi, %esi
  4f6570:      	movl	%ecx, 0xc(%esp)
  4f6574:      	addl	%eax, %esi
  4f6576:      	movl	0x344(%esp,%ebx), %edi
  4f657d:      	movl	%esi, 0x20(%esp)
  4f6581:      	movl	%ebx, 0x6a4(%esp)
  4f6588:      	movl	0x6d4(%esp), %ecx
  4f658f:      	movl	0x344(%esp,%ecx), %eax
  4f6596:      	movl	%edi, 0x4(%esp)
  4f659a:      	cmpl	%eax, %edi
  4f659c:      	jl	0x4f66cb <.text+0xf56cb>
  4f65a2:      	movl	0x340(%esp,%ecx), %edx
  4f65a9:      	movl	%ecx, %eax
  4f65ab:      	movl	%edx, 0x6d4(%esp)
  4f65b2:      	cmpl	0x6a0(%esp), %edx
  4f65b9:      	je	0x4f6dc4 <.text+0xf5dc4>
  4f65bf:      	movl	0x344(%esp,%edx), %esi
  4f65c6:      	movl	%edx, %ecx
  4f65c8:      	cmpl	%esi, %edi
  4f65ca:      	jge	0x4f65a2 <.text+0xf55a2>
  4f65cc:      	flds	0x14(%ebp,%edx)
  4f65d0:      	fsubs	0x14(%ebp,%eax)
  4f65d4:      	flds	0x4(%ebp,%edx)
  4f65d8:      	fsubs	0x4(%ebp,%eax)
  4f65dc:      	flds	0x10(%ebp,%edx)
  4f65e0:      	fsubs	0x10(%ebp,%eax)
  4f65e4:      	fxch	%st(1)
  4f65e6:      	fdivrs	0x62c808
  4f65ec:      	flds	0xc(%ebp,%edx)
  4f65f0:      	fsubs	0xc(%ebp,%eax)
  4f65f4:      	fxch	%st(1)
  4f65f6:      	fmul	%st, %st(2)
  4f65f8:      	flds	0x8(%ebp,%edx)
  4f65fc:      	fsubs	0x8(%ebp,%eax)
  4f6600:      	fxch	%st(2)
  4f6602:      	fmul	%st(1), %st
  4f6604:      	flds	(%ebp,%edx)
  4f6608:      	fsubs	(%ebp,%eax)
  4f660c:      	fxch	%st(3)
  4f660e:      	fmul	%st(2), %st
  4f6610:      	fxch	%st(4)
  4f6612:      	fstps	0x6f0(%esp)
  4f6619:      	fstps	0x6ec(%esp)
  4f6620:      	fmul	%st, %st(3)
  4f6622:      	flds	0x4(%ebp,%eax)
  4f6626:      	faddl	0x632380
  4f662c:      	fxch	%st(2)
  4f662e:      	fmulp	%st, %st(1)
  4f6630:      	fxch	%st(3)
  4f6632:      	fstps	0x6fc(%esp)
  4f6639:      	fstpl	0x648(%esp)
  4f6640:      	fstps	0x6f8(%esp)
  4f6647:      	fildl	0x648(%esp)
  4f664e:      	fxch	%st(1)
  4f6650:      	fstps	0x6f4(%esp)
  4f6657:      	fsubs	0x4(%ebp,%eax)
  4f665b:      	flds	0x6f4(%esp)
  4f6662:      	flds	0x6f8(%esp)
  4f6669:      	fmul	%st(2), %st
  4f666b:      	flds	0x6ec(%esp)
  4f6672:      	fmul	%st(3), %st
  4f6674:      	flds	0x6fc(%esp)
  4f667b:      	fmul	%st(4), %st
  4f667d:      	fxch	%st(2)
  4f667f:      	fadds	0x8(%ebp,%eax)
  4f6683:      	flds	0x6f0(%esp)
  4f668a:      	fmul	%st(5), %st
  4f668c:      	fxch	%st(2)
  4f668e:      	fadds	0xc(%ebp,%eax)
  4f6692:      	fxch	%st(4)
  4f6694:      	fmulp	%st, %st(5)
  4f6696:      	fstps	0x6dc(%esp)
  4f669d:      	fadds	0x10(%ebp,%eax)
  4f66a1:      	fxch	%st(3)
  4f66a3:      	fadds	(%ebp,%eax)
  4f66a7:      	fxch	%st(2)
  4f66a9:      	fstps	0x6e0(%esp)
  4f66b0:      	fadds	0x14(%ebp,%eax)
  4f66b4:      	fxch	%st(2)
  4f66b6:      	fstps	0x6e4(%esp)
  4f66bd:      	fstps	0x6d8(%esp)
  4f66c4:      	fstps	0x6e8(%esp)
  4f66cb:      	movl	0x6a4(%esp), %ecx
  4f66d2:      	cmpl	0x344(%esp,%ecx), %edi
  4f66d9:      	jl	0x4f67f6 <.text+0xf57f6>
  4f66df:      	movl	0x40(%esp,%ecx), %edx
  4f66e3:      	movl	%ecx, %eax
  4f66e5:      	movl	%edx, 0x6a4(%esp)
  4f66ec:      	movl	%edx, %ecx
  4f66ee:      	cmpl	0x344(%esp,%edx), %edi
  4f66f5:      	jge	0x4f66df <.text+0xf56df>
  4f66f7:      	flds	0x14(%ebp,%edx)
  4f66fb:      	fsubs	0x14(%ebp,%eax)
  4f66ff:      	flds	0x4(%ebp,%edx)
  4f6703:      	fsubs	0x4(%ebp,%eax)
  4f6707:      	flds	0x10(%ebp,%edx)
  4f670b:      	fsubs	0x10(%ebp,%eax)
  4f670f:      	fxch	%st(1)
  4f6711:      	fdivrs	0x62c808
  4f6717:      	flds	0xc(%ebp,%edx)
  4f671b:      	fsubs	0xc(%ebp,%eax)
  4f671f:      	fxch	%st(1)
  4f6721:      	fmul	%st, %st(2)
  4f6723:      	flds	0x8(%ebp,%edx)
  4f6727:      	fsubs	0x8(%ebp,%eax)
  4f672b:      	fxch	%st(2)
  4f672d:      	fmul	%st(1), %st
  4f672f:      	flds	(%ebp,%edx)
  4f6733:      	fsubs	(%ebp,%eax)
  4f6737:      	fxch	%st(3)
  4f6739:      	fmul	%st(2), %st
  4f673b:      	fxch	%st(4)
  4f673d:      	fstps	0x6c0(%esp)
  4f6744:      	fstps	0x6bc(%esp)
  4f674b:      	fmul	%st, %st(3)
  4f674d:      	flds	0x4(%ebp,%eax)
  4f6751:      	faddl	0x632380
  4f6757:      	fxch	%st(2)
  4f6759:      	fmulp	%st, %st(1)
  4f675b:      	fxch	%st(3)
  4f675d:      	fstps	0x6cc(%esp)
  4f6764:      	fstpl	0x648(%esp)
  4f676b:      	fstps	0x6c8(%esp)
  4f6772:      	fildl	0x648(%esp)
  4f6779:      	fxch	%st(1)
  4f677b:      	fstps	0x6c4(%esp)
  4f6782:      	fsubs	0x4(%ebp,%eax)
  4f6786:      	flds	0x6c4(%esp)
  4f678d:      	flds	0x6c8(%esp)
  4f6794:      	fmul	%st(2), %st
  4f6796:      	flds	0x6bc(%esp)
  4f679d:      	fmul	%st(3), %st
  4f679f:      	flds	0x6cc(%esp)
  4f67a6:      	fmul	%st(4), %st
  4f67a8:      	fxch	%st(2)
  4f67aa:      	fadds	0x8(%ebp,%eax)
  4f67ae:      	flds	0x6c0(%esp)
  4f67b5:      	fmul	%st(5), %st
  4f67b7:      	fxch	%st(2)
  4f67b9:      	fadds	0xc(%ebp,%eax)
  4f67bd:      	fxch	%st(4)
  4f67bf:      	fmulp	%st, %st(5)
  4f67c1:      	fstps	0x6ac(%esp)
  4f67c8:      	fadds	0x10(%ebp,%eax)
  4f67cc:      	fxch	%st(3)
  4f67ce:      	fadds	(%ebp,%eax)
  4f67d2:      	fxch	%st(2)
  4f67d4:      	fstps	0x6b0(%esp)
  4f67db:      	fadds	0x14(%ebp,%eax)
  4f67df:      	fxch	%st(2)
  4f67e1:      	fstps	0x6b4(%esp)
  4f67e8:      	fstps	0x6a8(%esp)
  4f67ef:      	fstps	0x6b8(%esp)
  4f67f6:      	flds	0x6d8(%esp)
  4f67fd:      	faddl	0x632380
  4f6803:      	flds	0x6a8(%esp)
  4f680a:      	faddl	0x632380
  4f6810:      	fxch	%st(1)
  4f6812:      	fstpl	0x658(%esp)
  4f6819:      	fstpl	0x650(%esp)
  4f6820:      	movl	0x658(%esp), %edx
  4f6827:      	movl	0x650(%esp), %ebx
  4f682e:      	cmpl	%edx, %ebx
  4f6830:      	je	0x4f6cd3 <.text+0xf5cd3>
  4f6836:      	jl	0x4f691b <.text+0xf591b>
  4f683c:      	flds	0x6b8(%esp)
  4f6843:      	fsubs	0x6e8(%esp)
  4f684a:      	flds	0x6a8(%esp)
  4f6851:      	fsubs	0x6d8(%esp)
  4f6858:      	flds	0x6b4(%esp)
  4f685f:      	fsubs	0x6e4(%esp)
  4f6866:      	fxch	%st(1)
  4f6868:      	fdivrs	0x62c808
  4f686e:      	flds	0x6b0(%esp)
  4f6875:      	fsubs	0x6e0(%esp)
  4f687c:      	fxch	%st(2)
  4f687e:      	fmul	%st(1), %st
  4f6880:      	flds	0x6ac(%esp)
  4f6887:      	fsubs	0x6dc(%esp)
  4f688e:      	fxch	%st(3)
  4f6890:      	fmul	%st(2), %st
  4f6892:      	fxch	%st(1)
  4f6894:      	fstps	0x2c(%esp)
  4f6898:      	fxch	%st(1)
  4f689a:      	fmul	%st, %st(2)
  4f689c:      	fxch	%st(1)
  4f689e:      	fstps	0x28(%esp)
  4f68a2:      	fmulp	%st, %st(2)
  4f68a4:      	fildl	0x658(%esp)
  4f68ab:      	fxch	%st(1)
  4f68ad:      	fstps	0x30(%esp)
  4f68b1:      	fsubs	0x6d8(%esp)
  4f68b8:      	fld	%st(1)
  4f68ba:      	faddl	0x632380
  4f68c0:      	fxch	%st(2)
  4f68c2:      	fmul	%st(1), %st
  4f68c4:      	flds	0x2c(%esp)
  4f68c8:      	fxch	%st(3)
  4f68ca:      	fstpl	0x698(%esp)
  4f68d1:      	fadds	0x6e8(%esp)
  4f68d8:      	fxch	%st(2)
  4f68da:      	flds	0x28(%esp)
  4f68de:      	fmul	%st(2), %st
  4f68e0:      	fxch	%st(3)
  4f68e2:      	faddl	0x632380
  4f68e8:      	fxch	%st(3)
  4f68ea:      	flds	0x30(%esp)
  4f68ee:      	fmul	%st(3), %st
  4f68f0:      	fxch	%st(4)
  4f68f2:      	fstpl	0x680(%esp)
  4f68f9:      	fadds	0x6e0(%esp)
  4f6900:      	fxch	%st(2)
  4f6902:      	fmulp	%st, %st(1)
  4f6904:      	fxch	%st(2)
  4f6906:      	fadds	0x6dc(%esp)
  4f690d:      	fxch	%st(2)
  4f690f:      	fadds	0x6e4(%esp)
  4f6916:      	jmp	0x4f6a05 <.text+0xf5a05>
  4f691b:      	movl	%ebx, 0x658(%esp)
  4f6922:      	movl	%edx, %ebx
  4f6924:      	movl	0x658(%esp), %edx
  4f692b:      	flds	0x6e8(%esp)
  4f6932:      	fsubs	0x6b8(%esp)
  4f6939:      	flds	0x6d8(%esp)
  4f6940:      	fsubs	0x6a8(%esp)
  4f6947:      	flds	0x6e4(%esp)
  4f694e:      	fsubs	0x6b4(%esp)
  4f6955:      	fxch	%st(1)
  4f6957:      	fdivrs	0x62c808
  4f695d:      	flds	0x6e0(%esp)
  4f6964:      	fsubs	0x6b0(%esp)
  4f696b:      	fxch	%st(2)
  4f696d:      	fmul	%st(1), %st
  4f696f:      	flds	0x6dc(%esp)
  4f6976:      	fsubs	0x6ac(%esp)
  4f697d:      	fxch	%st(3)
  4f697f:      	fmul	%st(2), %st
  4f6981:      	fxch	%st(1)
  4f6983:      	fstps	0x2c(%esp)
  4f6987:      	fxch	%st(1)
  4f6989:      	fmul	%st, %st(2)
  4f698b:      	fxch	%st(1)
  4f698d:      	fstps	0x28(%esp)
  4f6991:      	fmulp	%st, %st(2)
  4f6993:      	fildl	0x658(%esp)
  4f699a:      	fxch	%st(1)
  4f699c:      	fstps	0x30(%esp)
  4f69a0:      	fsubs	0x6a8(%esp)
  4f69a7:      	fld	%st(1)
  4f69a9:      	faddl	0x632380
  4f69af:      	fxch	%st(2)
  4f69b1:      	fmul	%st(1), %st
  4f69b3:      	flds	0x2c(%esp)
  4f69b7:      	fxch	%st(3)
  4f69b9:      	fstpl	0x698(%esp)
  4f69c0:      	fadds	0x6b8(%esp)
  4f69c7:      	fxch	%st(2)
  4f69c9:      	flds	0x28(%esp)
  4f69cd:      	fmul	%st(2), %st
  4f69cf:      	fxch	%st(3)
  4f69d1:      	faddl	0x632380
  4f69d7:      	fxch	%st(3)
  4f69d9:      	flds	0x30(%esp)
  4f69dd:      	fmul	%st(3), %st
  4f69df:      	fxch	%st(4)
  4f69e1:      	fstpl	0x680(%esp)
  4f69e8:      	fadds	0x6b0(%esp)
  4f69ef:      	fxch	%st(2)
  4f69f1:      	fmulp	%st, %st(1)
  4f69f3:      	fxch	%st(2)
  4f69f5:      	fadds	0x6ac(%esp)
  4f69fc:      	fxch	%st(2)
  4f69fe:      	fadds	0x6b4(%esp)
  4f6a05:      	movl	0x698(%esp), %eax
  4f6a0c:      	movl	0x20(%esp), %edi
  4f6a10:      	andl	$0xffff, %eax           # imm = 0xFFFF
  4f6a15:      	subl	%edx, %ebx
  4f6a17:      	orl	$0xfffe0000, %eax       # imm = 0xFFFE0000
  4f6a1c:      	addl	%edx, %edi
  4f6a1e:      	movl	%eax, 0x698(%esp)
  4f6a25:      	flds	0x28(%esp)
  4f6a29:      	fmuls	0x62c814
  4f6a2f:      	flds	0x2c(%esp)
  4f6a33:      	fmuls	0x62c814
  4f6a39:      	flds	0x30(%esp)
  4f6a3d:      	fmuls	0x62c814
  4f6a43:      	fxch	%st(2)
  4f6a45:      	fstps	0x34(%esp)
  4f6a49:      	fstps	0x38(%esp)
  4f6a4d:      	fstps	0x3c(%esp)
  4f6a51:      	fxch	%st(2)
  4f6a53:      	flds	0x62c80c
  4f6a59:      	fdiv	%st(1), %st
  4f6a5b:      	fld	%st(3)
  4f6a5d:      	fmul	%st(1), %st
  4f6a5f:      	fld	%st(3)
  4f6a61:      	fmulp	%st, %st(2)
  4f6a63:      	faddl	0x632380
  4f6a69:      	fxch	%st(1)
  4f6a6b:      	faddl	0x632380
  4f6a71:      	fxch	%st(2)
  4f6a73:      	fadds	0x3c(%esp)
  4f6a77:      	fxch	%st(1)
  4f6a79:      	fstpl	0x668(%esp)
  4f6a80:      	fxch	%st(1)
  4f6a82:      	fstpl	0x660(%esp)
  4f6a89:      	flds	0x62c80c
  4f6a8f:      	fdiv	%st(1), %st
  4f6a91:      	decl	%ebx
  4f6a92:      	jmp	0x4f6b9f <.text+0xf5b9f>
  4f6a97:      	flds	0x34(%esp)
  4f6a9b:      	faddp	%st, %st(3)
  4f6a9d:      	flds	0x38(%esp)
  4f6aa1:      	faddp	%st, %st(4)
  4f6aa3:      	fld	%st(2)
  4f6aa5:      	fmul	%st(1), %st
  4f6aa7:      	flds	0x3c(%esp)
  4f6aab:      	fxch	%st(2)
  4f6aad:      	fmul	%st(5), %st
  4f6aaf:      	fxch	%st(2)
  4f6ab1:      	faddp	%st, %st(3)
  4f6ab3:      	faddl	0x632380
  4f6ab9:      	fxch	%st(1)
  4f6abb:      	faddl	0x632380
  4f6ac1:      	fld	%st(2)
  4f6ac3:      	fxch	%st(2)
  4f6ac5:      	fstpl	0x670(%esp)
  4f6acc:      	fstpl	0x678(%esp)
  4f6ad3:      	fdivrs	0x62c80c
  4f6ad9:      	movl	0x668(%esp), %ebp
  4f6ae0:      	movl	0x660(%esp), %esi
  4f6ae7:      	movl	0x678(%esp), %eax
  4f6aee:      	movl	0x670(%esp), %edx
  4f6af5:      	subl	%ebp, %eax
  4f6af7:      	subl	%esi, %edx
  4f6af9:      	sarl	$0x4, %eax
  4f6afc:      	movl	%ebx, 0x8(%esp)
  4f6b00:      	sarl	$0x4, %edx
  4f6b03:      	movl	0x680(%esp), %ebx
  4f6b0a:      	movl	%edx, 0x688(%esp)
  4f6b11:      	andl	$0xffff, %ebx           # imm = 0xFFFF
  4f6b17:      	movl	%eax, 0x690(%esp)
  4f6b1e:      	orl	$0x1e0000, %ebx         # imm = 0x1E0000
  4f6b24:      	movb	(%edi), %al
  4f6b26:      	movl	%esi, %edx
  4f6b28:      	movl	0x688(%esp), %ecx
  4f6b2f:      	sarl	$0x10, %edx
  4f6b32:      	addl	%ecx, %esi
  4f6b34:      	movl	0x18(%esp), %ecx
  4f6b38:      	movl	%ebp, %eax
  4f6b3a:      	andl	%ecx, %edx
  4f6b3c:      	movl	0x690(%esp), %ecx
  4f6b43:      	sarl	$0x10, %eax
  4f6b46:      	addl	%ecx, %ebp
  4f6b48:      	movl	0x1c(%esp), %ecx
  4f6b4c:      	movl	0xcfdbd8(,%edx,4), %edx
  4f6b53:      	andl	%ecx, %eax
  4f6b55:      	andl	$0xfffeffff, %ebx       # imm = 0xFFFEFFFF
  4f6b5b:      	movl	0x698(%esp), %ecx
  4f6b62:      	movb	(%eax,%edx), %al
  4f6b65:      	incl	%edi
  4f6b66:      	movb	%bh, %ah
  4f6b68:      	movb	0xd1e480(%eax), %al
  4f6b6e:      	addl	%ecx, %ebx
  4f6b70:      	movb	%al, -0x1(%edi)
  4f6b73:      	jge	0x4f6b24 <.text+0xf5b24>
  4f6b75:      	movl	%ebx, 0x680(%esp)
  4f6b7c:      	movl	0x8(%esp), %ebx
  4f6b80:      	movl	0x670(%esp), %eax
  4f6b87:      	movl	0x678(%esp), %edx
  4f6b8e:      	movl	%eax, 0x660(%esp)
  4f6b95:      	movl	%edx, 0x668(%esp)
  4f6b9c:      	subl	$0x10, %ebx
  4f6b9f:      	cmpl	$0x10, %ebx
  4f6ba2:      	jge	0x4f6a97 <.text+0xf5a97>
  4f6ba8:      	movl	0x680(%esp), %eax
  4f6baf:      	movl	%ebx, %ecx
  4f6bb1:      	decl	%ebx
  4f6bb2:      	movl	0x668(%esp), %ebp
  4f6bb9:      	shll	$0x11, %ebx
  4f6bbc:      	andl	$0xffff, %eax           # imm = 0xFFFF
  4f6bc1:      	movl	0x660(%esp), %esi
  4f6bc8:      	orl	%eax, %ebx
  4f6bca:      	cmpl	$0x0, %ecx
  4f6bcd:      	je	0x4f6ca7 <.text+0xf5ca7>
  4f6bd3:      	fxch	%st(1)
  4f6bd5:      	fsubs	0x3c(%esp)
  4f6bd9:      	flds	0x30(%esp)
  4f6bdd:      	fmuls	0x62c810(,%ecx,8)
  4f6be4:      	flds	0x28(%esp)
  4f6be8:      	fmuls	0x62c810(,%ecx,8)
  4f6bef:      	flds	0x2c(%esp)
  4f6bf3:      	fmuls	0x62c810(,%ecx,8)
  4f6bfa:      	fxch	%st(2)
  4f6bfc:      	faddp	%st, %st(3)
  4f6bfe:      	faddp	%st, %st(4)
  4f6c00:      	faddp	%st, %st(4)
  4f6c02:      	fdivrs	0x62c80c
  4f6c08:      	fmul	%st, %st(2)
  4f6c0a:      	fildl	0x660(%esp)
  4f6c11:      	fxch	%st(1)
  4f6c13:      	fmul	%st(4), %st
  4f6c15:      	fildl	0x668(%esp)
  4f6c1c:      	fxch	%st(2)
  4f6c1e:      	fsubrp	%st, %st(4)
  4f6c20:      	fsubp	%st, %st(1)
  4f6c22:      	fxch	%st(2)
  4f6c24:      	fmuls	0x62c814(,%ecx,8)
  4f6c2b:      	fxch	%st(2)
  4f6c2d:      	fmuls	0x62c814(,%ecx,8)
  4f6c34:      	fxch	%st(2)
  4f6c36:      	faddl	0x632380
  4f6c3c:      	fxch	%st(2)
  4f6c3e:      	faddl	0x632380
  4f6c44:      	fxch	%st(2)
  4f6c46:      	fstl	0x688(%esp)
  4f6c4d:      	fxch	%st(2)
  4f6c4f:      	fstl	0x690(%esp)
  4f6c56:      	movb	(%edi), %al
  4f6c58:      	movl	%esi, %edx
  4f6c5a:      	movl	0x688(%esp), %ecx
  4f6c61:      	sarl	$0x10, %edx
  4f6c64:      	addl	%ecx, %esi
  4f6c66:      	movl	0x18(%esp), %ecx
  4f6c6a:      	movl	%ebp, %eax
  4f6c6c:      	andl	%ecx, %edx
  4f6c6e:      	movl	0x690(%esp), %ecx
  4f6c75:      	sarl	$0x10, %eax
  4f6c78:      	addl	%ecx, %ebp
  4f6c7a:      	movl	0x1c(%esp), %ecx
  4f6c7e:      	movl	0xcfdbd8(,%edx,4), %edx
  4f6c85:      	andl	%ecx, %eax
  4f6c87:      	andl	$0xfffeffff, %ebx       # imm = 0xFFFEFFFF
  4f6c8d:      	movl	0x698(%esp), %ecx
  4f6c94:      	movb	(%eax,%edx), %al
  4f6c97:      	incl	%edi
  4f6c98:      	movb	%bh, %ah
  4f6c9a:      	movb	0xd1e480(%eax), %al
  4f6ca0:      	addl	%ecx, %ebx
  4f6ca2:      	movb	%al, -0x1(%edi)
  4f6ca5:      	jge	0x4f6c56 <.text+0xf5c56>
  4f6ca7:      	sarl	$0x10, %esi
  4f6caa:      	movl	0x18(%esp), %ecx
  4f6cae:      	xorl	%edx, %edx
  4f6cb0:      	andl	%ecx, %esi
  4f6cb2:      	sarl	$0x10, %ebp
  4f6cb5:      	movl	0x1c(%esp), %eax
  4f6cb9:      	movb	%bh, %dh
  4f6cbb:      	andl	%ebp, %eax
  4f6cbd:      	movl	0xcfdbd8(,%esi,4), %esi
  4f6cc4:      	fcompp
  4f6cc6:      	movb	(%eax,%esi), %dl
  4f6cc9:      	fcompp
  4f6ccb:      	movb	0xd1e480(%edx), %al
  4f6cd1:      	movb	%al, (%edi)
  4f6cd3:      	flds	0x6b8(%esp)
  4f6cda:      	fadds	0x6cc(%esp)
  4f6ce1:      	flds	0x6ac(%esp)
  4f6ce8:      	fadds	0x6c8(%esp)
  4f6cef:      	flds	0x6b4(%esp)
  4f6cf6:      	fadds	0x6c0(%esp)
  4f6cfd:      	flds	0x6b0(%esp)
  4f6d04:      	fadds	0x6bc(%esp)
  4f6d0b:      	flds	0x6a8(%esp)
  4f6d12:      	fadds	0x6c4(%esp)
  4f6d19:      	fxch	%st(3)
  4f6d1b:      	fstps	0x6ac(%esp)
  4f6d22:      	fstps	0x6b0(%esp)
  4f6d29:      	fstps	0x6b4(%esp)
  4f6d30:      	fstps	0x6a8(%esp)
  4f6d37:      	fstps	0x6b8(%esp)
  4f6d3e:      	flds	0x6e8(%esp)
  4f6d45:      	fadds	0x6fc(%esp)
  4f6d4c:      	flds	0x6dc(%esp)
  4f6d53:      	fadds	0x6f8(%esp)
  4f6d5a:      	flds	0x6e4(%esp)
  4f6d61:      	fadds	0x6f0(%esp)
  4f6d68:      	flds	0x6e0(%esp)
  4f6d6f:      	fadds	0x6ec(%esp)
  4f6d76:      	flds	0x6d8(%esp)
  4f6d7d:      	fadds	0x6f4(%esp)
  4f6d84:      	fxch	%st(3)
  4f6d86:      	fstps	0x6dc(%esp)
  4f6d8d:      	fstps	0x6e0(%esp)
  4f6d94:      	fstps	0x6e4(%esp)
  4f6d9b:      	fstps	0x6d8(%esp)
  4f6da2:      	fstps	0x6e8(%esp)
  4f6da9:      	movl	0x20(%esp), %esi
  4f6dad:      	movl	0xc(%esp), %eax
  4f6db1:      	movl	(%esp), %ebp
  4f6db4:      	addl	%eax, %esi
  4f6db6:      	movl	0x4(%esp), %edi
  4f6dba:      	movl	%esi, 0x20(%esp)
  4f6dbe:      	incl	%edi
  4f6dbf:      	jmp	0x4f6588 <.text+0xf5588>
  4f6dc4:      	addl	$0x700, %esp            # imm = 0x700
  4f6dca:      	popl	%ebp
  4f6dcb:      	popl	%edi
  4f6dcc:      	popl	%esi
  4f6dcd:      	popl	%ebx
  4f6dce:      	popl	%ebp
  4f6dcf:      	retl
