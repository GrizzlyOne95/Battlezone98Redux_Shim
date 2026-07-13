; Entry: 004f317c
; Name: Flat_Tile_Perspective_Texture_Map_polygon
; Signature: void Flat_Tile_Perspective_Texture_Map_polygon(_GRAPHIC_BUFFER * param_1, POINT_3D * param_2, long param_3, POLYGON_SKIN param_4)
; Stop: 0x004f39c1
; Reason: Exception while decompiling 004f317c: process: timeout 
; Command: C:\Program Files\LLVM\bin\llvm-objdump.EXE -d --no-show-raw-insn --start-address=0x004f317c --stop-address=0x004f39c1 C:\Users\istuart\Downloads\bzone15227\extracted\bzone.exe


C:\Users\istuart\Downloads\bzone15227\extracted\bzone.exe:	file format coff-i386

Disassembly of section .text:

00401000 <.text>:
  4f317c:      	pushl	%ebp
  4f317d:      	movl	%esp, %ebp
  4f317f:      	pushl	%ebx
  4f3180:      	pushl	%edi
  4f3181:      	pushl	%esi
  4f3182:      	movl	0x14(%ebp), %ebx
  4f3185:      	movl	0xcfdbc0, %eax
  4f318a:      	subl	$0x6e8, %esp            # imm = 0x6E8
  4f3190:      	cmpl	%ebx, %eax
  4f3192:      	je	0x4f3202 <.text+0xf2202>
  4f3194:      	movl	%ebx, 0xcfdbc0
  4f319a:      	leal	0xcfdbd8, %edx
  4f31a0:      	movl	(%ebx), %eax
  4f31a2:      	movl	0x4(%ebx), %ecx
  4f31a5:      	leal	0x8(%ebx), %esi
  4f31a8:      	movl	%ecx, 0x4(%esp)
  4f31ac:      	movl	%eax, %edi
  4f31ae:      	addl	$0x3, %ecx
  4f31b1:      	addl	%esi, %edi
  4f31b3:      	leal	(%esi,%eax,2), %ebx
  4f31b6:      	leal	(%eax,%eax,2), %eax
  4f31b9:      	movl	%esi, -0x4(%edx)
  4f31bc:      	movl	%esi, -0x8(%edx)
  4f31bf:      	movl	%esi, -0xc(%edx)
  4f31c2:      	movl	%esi, -0x10(%edx)
  4f31c5:      	movl	%esi, (%edx)
  4f31c7:      	movl	%edi, 0x4(%edx)
  4f31ca:      	movl	%ebx, 0x8(%edx)
  4f31cd:      	addl	%eax, %esi
  4f31cf:      	addl	%eax, %edi
  4f31d1:      	addl	%eax, %ebx
  4f31d3:      	addl	$0xc, %edx
  4f31d6:      	subl	$0x3, %ecx
  4f31d9:      	jge	0x4f31c5 <.text+0xf21c5>
  4f31db:      	movl	0x4(%esp), %edx
  4f31df:      	movl	0xcfdbd4(,%edx,4), %eax
  4f31e6:      	movl	%eax, 0xcfdbd8(,%edx,4)
  4f31ed:      	movl	%eax, 0xcfdbdc(,%edx,4)
  4f31f4:      	movl	%eax, 0xcfdbe0(,%edx,4)
  4f31fb:      	movl	%eax, 0xcfdbe4(,%edx,4)
  4f3202:      	movl	0x14(%ebp), %ebx
  4f3205:      	movl	$0x186a0, %edx          # imm = 0x186A0
  4f320a:      	movl	0xc(%ebp), %esi
  4f320d:      	movl	0x10(%ebp), %eax
  4f3210:      	movl	(%ebx), %ecx
  4f3212:      	movl	0x4(%ebx), %edi
  4f3215:      	decl	%ecx
  4f3216:      	decl	%edi
  4f3217:      	fildl	0x4(%ebx)
  4f321a:      	movl	%ecx, 0x90(%esp)
  4f3221:      	movl	%edi, 0x94(%esp)
  4f3228:      	incl	%ecx
  4f3229:      	movl	%esi, (%esp)
  4f322c:      	shll	$0x3, %eax
  4f322f:      	leal	0x8(%ebx), %edi
  4f3232:      	fildl	(%ebx)
  4f3234:      	movl	%ecx, 0x10(%esp)
  4f3238:      	leal	(%eax,%eax,2), %ecx
  4f323b:      	xorl	%eax, %eax
  4f323d:      	movl	%edi, 0x1c(%esp)
  4f3241:      	flds	0x4(%esi,%eax)
  4f3245:      	faddl	0x632380
  4f324b:      	flds	0xc(%esi,%eax)
  4f324f:      	fmul	%st(2), %st
  4f3251:      	flds	0x10(%esi,%eax)
  4f3255:      	fmul	%st(4), %st
  4f3257:      	fxch	%st(2)
  4f3259:      	fstpl	0x48(%esp)
  4f325d:      	fstps	0xc(%esi,%eax)
  4f3261:      	fstps	0x10(%esi,%eax)
  4f3265:      	movl	0x48(%esp), %edi
  4f3269:      	movl	%eax, 0x3d0(%esp,%eax)
  4f3270:      	movl	%eax, 0x100(%esp,%eax)
  4f3277:      	movl	%edi, 0x3ec(%esp,%eax)
  4f327e:      	addl	$0x18, %eax
  4f3281:      	cmpl	%edx, %edi
  4f3283:      	jg	0x4f3289 <.text+0xf2289>
  4f3285:      	movl	%eax, %ebx
  4f3287:      	movl	%edi, %edx
  4f3289:      	cmpl	%ecx, %eax
  4f328b:      	jne	0x4f3241 <.text+0xf2241>
  4f328d:      	subl	$0x18, %ebx
  4f3290:      	leal	-0x18(%eax), %ecx
  4f3293:      	flds	0x62c808
  4f3299:      	fsubs	0x14(%esi)
  4f329c:      	fxch	%st(2)
  4f329e:      	fcompp
  4f32a0:      	fmuls	0x62c810
  4f32a6:      	movl	$0x0, 0x3d0(%esp,%eax)
  4f32b1:      	movl	%ecx, 0xe8(%esp)
  4f32b8:      	movl	0x8(%ebp), %edi
  4f32bb:      	movl	%ebx, 0xc0(%esp)
  4f32c2:      	faddl	0x632380
  4f32c8:      	movl	%ebx, 0x98(%esp)
  4f32cf:      	movl	%ebx, 0xc4(%esp)
  4f32d6:      	movl	%esi, %ebp
  4f32d8:      	movl	0x20(%edi), %eax
  4f32db:      	movl	(%edi), %ecx
  4f32dd:      	addl	%edx, %eax
  4f32df:      	movl	0x14(%edi), %esi
  4f32e2:      	movl	0x1c(%edi), %edi
  4f32e5:      	imull	%ecx
  4f32e7:      	fstpl	0x38(%esp)
  4f32eb:      	addl	%edi, %esi
  4f32ed:      	movl	%ecx, 0xc(%esp)
  4f32f1:      	addl	%eax, %esi
  4f32f3:      	movl	0x3ec(%esp,%ebx), %edi
  4f32fa:      	movl	%esi, 0x18(%esp)
  4f32fe:      	movl	%ebx, 0x9c(%esp)
  4f3305:      	movl	0xc4(%esp), %ecx
  4f330c:      	movl	0x3ec(%esp,%ecx), %eax
  4f3313:      	movl	%edi, 0x4(%esp)
  4f3317:      	cmpl	%eax, %edi
  4f3319:      	jl	0x4f341d <.text+0xf241d>
  4f331f:      	movl	0x3e8(%esp,%ecx), %edx
  4f3326:      	movl	%ecx, %eax
  4f3328:      	movl	%edx, 0xc4(%esp)
  4f332f:      	cmpl	0x98(%esp), %edx
  4f3336:      	je	0x4f39b6 <.text+0xf29b6>
  4f333c:      	movl	0x3ec(%esp,%edx), %esi
  4f3343:      	movl	%edx, %ecx
  4f3345:      	cmpl	%esi, %edi
  4f3347:      	jge	0x4f331f <.text+0xf231f>
  4f3349:      	flds	0x4(%ebp,%edx)
  4f334d:      	fsubs	0x4(%ebp,%eax)
  4f3351:      	flds	0x10(%ebp,%edx)
  4f3355:      	fsubs	0x10(%ebp,%eax)
  4f3359:      	fxch	%st(1)
  4f335b:      	fdivrs	0x62c808
  4f3361:      	flds	0xc(%ebp,%edx)
  4f3365:      	fsubs	0xc(%ebp,%eax)
  4f3369:      	fxch	%st(1)
  4f336b:      	fmul	%st, %st(2)
  4f336d:      	flds	0x8(%ebp,%edx)
  4f3371:      	fsubs	0x8(%ebp,%eax)
  4f3375:      	fxch	%st(2)
  4f3377:      	fmul	%st(1), %st
  4f3379:      	flds	(%ebp,%edx)
  4f337d:      	fsubs	(%ebp,%eax)
  4f3381:      	fxch	%st(3)
  4f3383:      	fmul	%st(2), %st
  4f3385:      	fxch	%st(4)
  4f3387:      	fstps	0xdc(%esp)
  4f338e:      	flds	0x4(%ebp,%eax)
  4f3392:      	faddl	0x632380
  4f3398:      	fxch	%st(3)
  4f339a:      	fmulp	%st, %st(2)
  4f339c:      	fstps	0xd8(%esp)
  4f33a3:      	fxch	%st(1)
  4f33a5:      	fstpl	0x48(%esp)
  4f33a9:      	fstps	0xe0(%esp)
  4f33b0:      	fildl	0x48(%esp)
  4f33b4:      	fxch	%st(1)
  4f33b6:      	fstps	0xe4(%esp)
  4f33bd:      	fsubs	0x4(%ebp,%eax)
  4f33c1:      	flds	0xe0(%esp)
  4f33c8:      	flds	0xe4(%esp)
  4f33cf:      	fmul	%st(2), %st
  4f33d1:      	flds	0xd8(%esp)
  4f33d8:      	fmul	%st(3), %st
  4f33da:      	fxch	%st(1)
  4f33dc:      	fadds	0x8(%ebp,%eax)
  4f33e0:      	flds	0xdc(%esp)
  4f33e7:      	fmul	%st(4), %st
  4f33e9:      	fxch	%st(2)
  4f33eb:      	fadds	0xc(%ebp,%eax)
  4f33ef:      	fxch	%st(3)
  4f33f1:      	fmulp	%st, %st(4)
  4f33f3:      	fstps	0xcc(%esp)
  4f33fa:      	fadds	0x10(%ebp,%eax)
  4f33fe:      	fxch	%st(2)
  4f3400:      	fadds	(%ebp,%eax)
  4f3404:      	fxch	%st(1)
  4f3406:      	fstps	0xd0(%esp)
  4f340d:      	fxch	%st(1)
  4f340f:      	fstps	0xd4(%esp)
  4f3416:      	fstps	0xc8(%esp)
  4f341d:      	movl	0x9c(%esp), %ecx
  4f3424:      	cmpl	0x3ec(%esp,%ecx), %edi
  4f342b:      	jl	0x4f3520 <.text+0xf2520>
  4f3431:      	movl	0xe8(%esp,%ecx), %edx
  4f3438:      	movl	%ecx, %eax
  4f343a:      	movl	%edx, 0x9c(%esp)
  4f3441:      	movl	%edx, %ecx
  4f3443:      	cmpl	0x3ec(%esp,%edx), %edi
  4f344a:      	jge	0x4f3431 <.text+0xf2431>
  4f344c:      	flds	0x4(%ebp,%edx)
  4f3450:      	fsubs	0x4(%ebp,%eax)
  4f3454:      	flds	0x10(%ebp,%edx)
  4f3458:      	fsubs	0x10(%ebp,%eax)
  4f345c:      	fxch	%st(1)
  4f345e:      	fdivrs	0x62c808
  4f3464:      	flds	0xc(%ebp,%edx)
  4f3468:      	fsubs	0xc(%ebp,%eax)
  4f346c:      	fxch	%st(1)
  4f346e:      	fmul	%st, %st(2)
  4f3470:      	flds	0x8(%ebp,%edx)
  4f3474:      	fsubs	0x8(%ebp,%eax)
  4f3478:      	fxch	%st(2)
  4f347a:      	fmul	%st(1), %st
  4f347c:      	flds	(%ebp,%edx)
  4f3480:      	fsubs	(%ebp,%eax)
  4f3484:      	fxch	%st(3)
  4f3486:      	fmul	%st(2), %st
  4f3488:      	fxch	%st(4)
  4f348a:      	fstps	0xb4(%esp)
  4f3491:      	flds	0x4(%ebp,%eax)
  4f3495:      	faddl	0x632380
  4f349b:      	fxch	%st(3)
  4f349d:      	fmulp	%st, %st(2)
  4f349f:      	fstps	0xb0(%esp)
  4f34a6:      	fxch	%st(1)
  4f34a8:      	fstpl	0x48(%esp)
  4f34ac:      	fstps	0xb8(%esp)
  4f34b3:      	fildl	0x48(%esp)
  4f34b7:      	fxch	%st(1)
  4f34b9:      	fstps	0xbc(%esp)
  4f34c0:      	fsubs	0x4(%ebp,%eax)
  4f34c4:      	flds	0xb8(%esp)
  4f34cb:      	flds	0xbc(%esp)
  4f34d2:      	fmul	%st(2), %st
  4f34d4:      	flds	0xb0(%esp)
  4f34db:      	fmul	%st(3), %st
  4f34dd:      	fxch	%st(1)
  4f34df:      	fadds	0x8(%ebp,%eax)
  4f34e3:      	flds	0xb4(%esp)
  4f34ea:      	fmul	%st(4), %st
  4f34ec:      	fxch	%st(2)
  4f34ee:      	fadds	0xc(%ebp,%eax)
  4f34f2:      	fxch	%st(3)
  4f34f4:      	fmulp	%st, %st(4)
  4f34f6:      	fstps	0xa4(%esp)
  4f34fd:      	fadds	0x10(%ebp,%eax)
  4f3501:      	fxch	%st(2)
  4f3503:      	fadds	(%ebp,%eax)
  4f3507:      	fxch	%st(1)
  4f3509:      	fstps	0xa8(%esp)
  4f3510:      	fxch	%st(1)
  4f3512:      	fstps	0xac(%esp)
  4f3519:      	fstps	0xa0(%esp)
  4f3520:      	flds	0xc8(%esp)
  4f3527:      	faddl	0x632380
  4f352d:      	flds	0xa0(%esp)
  4f3534:      	faddl	0x632380
  4f353a:      	fxch	%st(1)
  4f353c:      	fstpl	0x58(%esp)
  4f3540:      	fstpl	0x50(%esp)
  4f3544:      	movl	0x58(%esp), %edx
  4f3548:      	movl	0x50(%esp), %ebx
  4f354c:      	cmpl	%edx, %ebx
  4f354e:      	je	0x4f38ef <.text+0xf28ef>
  4f3554:      	jl	0x4f35f3 <.text+0xf25f3>
  4f355a:      	flds	0xa0(%esp)
  4f3561:      	fsubs	0xc8(%esp)
  4f3568:      	flds	0xac(%esp)
  4f356f:      	fsubs	0xd4(%esp)
  4f3576:      	fxch	%st(1)
  4f3578:      	fdivrs	0x62c808
  4f357e:      	flds	0xa8(%esp)
  4f3585:      	fsubs	0xd0(%esp)
  4f358c:      	fxch	%st(2)
  4f358e:      	fmul	%st(1), %st
  4f3590:      	flds	0xa4(%esp)
  4f3597:      	fsubs	0xcc(%esp)
  4f359e:      	fxch	%st(3)
  4f35a0:      	fmul	%st(2), %st
  4f35a2:      	fxch	%st(1)
  4f35a4:      	fstps	0x24(%esp)
  4f35a8:      	fxch	%st(1)
  4f35aa:      	fmulp	%st, %st(2)
  4f35ac:      	fstps	0x20(%esp)
  4f35b0:      	fildl	0x58(%esp)
  4f35b4:      	fxch	%st(1)
  4f35b6:      	fstps	0x28(%esp)
  4f35ba:      	fsubs	0xc8(%esp)
  4f35c1:      	flds	0x24(%esp)
  4f35c5:      	flds	0x20(%esp)
  4f35c9:      	fmul	%st(2), %st
  4f35cb:      	flds	0x28(%esp)
  4f35cf:      	fmul	%st(3), %st
  4f35d1:      	fxch	%st(1)
  4f35d3:      	fadds	0xd0(%esp)
  4f35da:      	fxch	%st(3)
  4f35dc:      	fmulp	%st, %st(2)
  4f35de:      	fadds	0xcc(%esp)
  4f35e5:      	fxch	%st(1)
  4f35e7:      	fadds	0xd4(%esp)
  4f35ee:      	jmp	0x4f3691 <.text+0xf2691>
  4f35f3:      	movl	%ebx, 0x58(%esp)
  4f35f7:      	movl	%edx, %ebx
  4f35f9:      	movl	0x58(%esp), %edx
  4f35fd:      	flds	0xc8(%esp)
  4f3604:      	fsubs	0xa0(%esp)
  4f360b:      	flds	0xd4(%esp)
  4f3612:      	fsubs	0xac(%esp)
  4f3619:      	fxch	%st(1)
  4f361b:      	fdivrs	0x62c808
  4f3621:      	flds	0xd0(%esp)
  4f3628:      	fsubs	0xa8(%esp)
  4f362f:      	fxch	%st(2)
  4f3631:      	fmul	%st(1), %st
  4f3633:      	flds	0xcc(%esp)
  4f363a:      	fsubs	0xa4(%esp)
  4f3641:      	fxch	%st(3)
  4f3643:      	fmul	%st(2), %st
  4f3645:      	fxch	%st(1)
  4f3647:      	fstps	0x24(%esp)
  4f364b:      	fxch	%st(1)
  4f364d:      	fmulp	%st, %st(2)
  4f364f:      	fstps	0x20(%esp)
  4f3653:      	fildl	0x58(%esp)
  4f3657:      	fxch	%st(1)
  4f3659:      	fstps	0x28(%esp)
  4f365d:      	fsubs	0xa0(%esp)
  4f3664:      	flds	0x24(%esp)
  4f3668:      	flds	0x20(%esp)
  4f366c:      	fmul	%st(2), %st
  4f366e:      	flds	0x28(%esp)
  4f3672:      	fmul	%st(3), %st
  4f3674:      	fxch	%st(1)
  4f3676:      	fadds	0xa8(%esp)
  4f367d:      	fxch	%st(3)
  4f367f:      	fmulp	%st, %st(2)
  4f3681:      	fadds	0xa4(%esp)
  4f3688:      	fxch	%st(1)
  4f368a:      	fadds	0xac(%esp)
  4f3691:      	movl	0x18(%esp), %edi
  4f3695:      	subl	%edx, %ebx
  4f3697:      	addl	%edx, %edi
  4f3699:      	flds	0x20(%esp)
  4f369d:      	fmuls	0x62c814
  4f36a3:      	flds	0x24(%esp)
  4f36a7:      	fmuls	0x62c814
  4f36ad:      	flds	0x28(%esp)
  4f36b1:      	fmuls	0x62c814
  4f36b7:      	fxch	%st(2)
  4f36b9:      	fstps	0x2c(%esp)
  4f36bd:      	fstps	0x30(%esp)
  4f36c1:      	fstps	0x34(%esp)
  4f36c5:      	fxch	%st(1)
  4f36c7:      	flds	0x62c80c
  4f36cd:      	fdiv	%st(1), %st
  4f36cf:      	fld	%st(2)
  4f36d1:      	fmul	%st(1), %st
  4f36d3:      	fld	%st(4)
  4f36d5:      	fmulp	%st, %st(2)
  4f36d7:      	faddl	0x632380
  4f36dd:      	fxch	%st(1)
  4f36df:      	faddl	0x632380
  4f36e5:      	fxch	%st(2)
  4f36e7:      	fadds	0x34(%esp)
  4f36eb:      	fxch	%st(1)
  4f36ed:      	fstpl	0x68(%esp)
  4f36f1:      	fxch	%st(1)
  4f36f3:      	fstpl	0x60(%esp)
  4f36f7:      	fxch	%st(2)
  4f36f9:      	flds	0x62c80c
  4f36ff:      	fdiv	%st(3), %st
  4f3701:      	decl	%ebx
  4f3702:      	jmp	0x4f37d6 <.text+0xf27d6>
  4f3707:      	flds	0x2c(%esp)
  4f370b:      	faddp	%st, %st(2)
  4f370d:      	flds	0x30(%esp)
  4f3711:      	faddp	%st, %st(3)
  4f3713:      	fld	%st(1)
  4f3715:      	fmul	%st(1), %st
  4f3717:      	flds	0x34(%esp)
  4f371b:      	fxch	%st(2)
  4f371d:      	fmul	%st(4), %st
  4f371f:      	fxch	%st(2)
  4f3721:      	faddp	%st, %st(5)
  4f3723:      	faddl	0x632380
  4f3729:      	fxch	%st(1)
  4f372b:      	faddl	0x632380
  4f3731:      	fld	%st(4)
  4f3733:      	fxch	%st(2)
  4f3735:      	fstpl	0x70(%esp)
  4f3739:      	fstpl	0x78(%esp)
  4f373d:      	fdivrs	0x62c80c
  4f3743:      	movl	0x68(%esp), %ebp
  4f3747:      	movl	0x60(%esp), %esi
  4f374b:      	movl	0x78(%esp), %eax
  4f374f:      	movl	0x70(%esp), %edx
  4f3753:      	subl	%ebp, %eax
  4f3755:      	subl	%esi, %edx
  4f3757:      	sarl	$0x4, %eax
  4f375a:      	movl	%ebx, 0x8(%esp)
  4f375e:      	sarl	$0x4, %edx
  4f3761:      	movl	%eax, 0x88(%esp)
  4f3768:      	movl	0x38(%esp), %ebx
  4f376c:      	movl	%edx, 0x80(%esp)
  4f3773:      	movb	$0x10, %bl
  4f3775:      	movb	(%edi), %dl
  4f3777:      	movl	%ebp, %eax
  4f3779:      	movl	0x88(%esp), %ecx
  4f3780:      	sarl	$0x10, %eax
  4f3783:      	movl	0x94(%esp), %edx
  4f378a:      	addl	%ecx, %ebp
  4f378c:      	andl	%edx, %eax
  4f378e:      	movl	%esi, %edx
  4f3790:      	movl	0x80(%esp), %ecx
  4f3797:      	sarl	$0x10, %edx
  4f379a:      	movl	0xcfdbd8(,%eax,4), %eax
  4f37a1:      	addl	%ecx, %esi
  4f37a3:      	movl	0x90(%esp), %ecx
  4f37aa:      	andl	%ecx, %edx
  4f37ac:      	movb	(%eax,%edx), %dl
  4f37af:      	incl	%edi
  4f37b0:      	movb	%bh, %dh
  4f37b2:      	movb	0xd1e480(%edx), %al
  4f37b8:      	decb	%bl
  4f37ba:      	movb	%al, -0x1(%edi)
  4f37bd:      	jne	0x4f3777 <.text+0xf2777>
  4f37bf:      	movl	0x8(%esp), %ebx
  4f37c3:      	movl	0x70(%esp), %eax
  4f37c7:      	movl	0x78(%esp), %edx
  4f37cb:      	movl	%eax, 0x60(%esp)
  4f37cf:      	movl	%edx, 0x68(%esp)
  4f37d3:      	subl	$0x10, %ebx
  4f37d6:      	cmpl	$0x10, %ebx
  4f37d9:      	jge	0x4f3707 <.text+0xf2707>
  4f37df:      	cmpl	$0x0, %ebx
  4f37e2:      	movl	0x68(%esp), %ebp
  4f37e6:      	movl	0x60(%esp), %esi
  4f37ea:      	je	0x4f38bd <.text+0xf28bd>
  4f37f0:      	fxch	%st(3)
  4f37f2:      	fsubs	0x34(%esp)
  4f37f6:      	flds	0x28(%esp)
  4f37fa:      	fmuls	0x62c810(,%ebx,8)
  4f3801:      	flds	0x20(%esp)
  4f3805:      	fmuls	0x62c810(,%ebx,8)
  4f380c:      	flds	0x24(%esp)
  4f3810:      	fmuls	0x62c810(,%ebx,8)
  4f3817:      	fxch	%st(2)
  4f3819:      	faddp	%st, %st(3)
  4f381b:      	faddp	%st, %st(3)
  4f381d:      	faddp	%st, %st(3)
  4f381f:      	fdivrs	0x62c80c
  4f3825:      	fmul	%st, %st(1)
  4f3827:      	fildl	0x60(%esp)
  4f382b:      	fxch	%st(1)
  4f382d:      	fmul	%st(3), %st
  4f382f:      	fildl	0x68(%esp)
  4f3833:      	fxch	%st(2)
  4f3835:      	fsubrp	%st, %st(3)
  4f3837:      	fsubp	%st, %st(1)
  4f3839:      	fxch	%st(1)
  4f383b:      	fmuls	0x62c814(,%ebx,8)
  4f3842:      	fxch	%st(1)
  4f3844:      	fmuls	0x62c814(,%ebx,8)
  4f384b:      	fxch	%st(1)
  4f384d:      	faddl	0x632380
  4f3853:      	fxch	%st(1)
  4f3855:      	faddl	0x632380
  4f385b:      	fxch	%st(1)
  4f385d:      	fstl	0x80(%esp)
  4f3864:      	fxch	%st(1)
  4f3866:      	fstl	0x88(%esp)
  4f386d:      	movl	0x38(%esp), %eax
  4f3871:      	movb	(%edi), %dl
  4f3873:      	movb	%ah, %bh
  4f3875:      	movl	%ebp, %eax
  4f3877:      	movl	0x88(%esp), %ecx
  4f387e:      	sarl	$0x10, %eax
  4f3881:      	movl	0x94(%esp), %edx
  4f3888:      	addl	%ecx, %ebp
  4f388a:      	andl	%edx, %eax
  4f388c:      	movl	%esi, %edx
  4f388e:      	movl	0x80(%esp), %ecx
  4f3895:      	sarl	$0x10, %edx
  4f3898:      	movl	0xcfdbd8(,%eax,4), %eax
  4f389f:      	addl	%ecx, %esi
  4f38a1:      	movl	0x90(%esp), %ecx
  4f38a8:      	andl	%ecx, %edx
  4f38aa:      	incl	%edi
  4f38ab:      	movb	(%eax,%edx), %dl
  4f38ae:      	movb	%bh, %dh
  4f38b0:      	movb	0xd1e480(%edx), %al
  4f38b6:      	decb	%bl
  4f38b8:      	movb	%al, -0x1(%edi)
  4f38bb:      	jne	0x4f3875 <.text+0xf2875>
  4f38bd:      	sarl	$0x10, %ebp
  4f38c0:      	movl	0x94(%esp), %eax
  4f38c7:      	sarl	$0x10, %esi
  4f38ca:      	andl	%eax, %ebp
  4f38cc:      	movl	0x90(%esp), %ecx
  4f38d3:      	movl	0x38(%esp), %edx
  4f38d7:      	andl	%ecx, %esi
  4f38d9:      	movl	0xcfdbd8(,%ebp,4), %eax
  4f38e0:      	fcompp
  4f38e2:      	movb	(%eax,%esi), %dl
  4f38e5:      	fcompp
  4f38e7:      	movb	0xd1e480(%edx), %al
  4f38ed:      	movb	%al, (%edi)
  4f38ef:      	flds	0xa4(%esp)
  4f38f6:      	fadds	0xbc(%esp)
  4f38fd:      	flds	0xac(%esp)
  4f3904:      	fadds	0xb4(%esp)
  4f390b:      	flds	0xa8(%esp)
  4f3912:      	fadds	0xb0(%esp)
  4f3919:      	flds	0xa0(%esp)
  4f3920:      	fadds	0xb8(%esp)
  4f3927:      	fxch	%st(3)
  4f3929:      	fstps	0xa4(%esp)
  4f3930:      	fstps	0xa8(%esp)
  4f3937:      	fstps	0xac(%esp)
  4f393e:      	fstps	0xa0(%esp)
  4f3945:      	flds	0xcc(%esp)
  4f394c:      	fadds	0xe4(%esp)
  4f3953:      	flds	0xd4(%esp)
  4f395a:      	fadds	0xdc(%esp)
  4f3961:      	flds	0xd0(%esp)
  4f3968:      	fadds	0xd8(%esp)
  4f396f:      	flds	0xc8(%esp)
  4f3976:      	fadds	0xe0(%esp)
  4f397d:      	fxch	%st(3)
  4f397f:      	fstps	0xcc(%esp)
  4f3986:      	fstps	0xd0(%esp)
  4f398d:      	fstps	0xd4(%esp)
  4f3994:      	fstps	0xc8(%esp)
  4f399b:      	movl	0x18(%esp), %esi
  4f399f:      	movl	0xc(%esp), %eax
  4f39a3:      	movl	(%esp), %ebp
  4f39a6:      	addl	%eax, %esi
  4f39a8:      	movl	0x4(%esp), %edi
  4f39ac:      	movl	%esi, 0x18(%esp)
  4f39b0:      	incl	%edi
  4f39b1:      	jmp	0x4f3305 <.text+0xf2305>
  4f39b6:      	addl	$0x6e8, %esp            # imm = 0x6E8
  4f39bc:      	popl	%esi
  4f39bd:      	popl	%edi
  4f39be:      	popl	%ebx
  4f39bf:      	popl	%ebp
  4f39c0:      	retl
