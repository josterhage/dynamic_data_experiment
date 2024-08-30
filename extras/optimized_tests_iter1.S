	.file	"tests.c"
	.text
	.p2align 4
	.type	randomize_index, @function
randomize_index:
.LFB92:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	movq	%rdi, %r13
	movl	$2, %edi
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	movslq	%esi, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	subq	$40, %rsp
	.cfi_def_cfa_offset 80
	movq	%fs:40, %rax
	movq	%rax, 24(%rsp)
	xorl	%eax, %eax
	movq	%rsp, %rsi
	call	clock_gettime@PLT
	movl	8(%rsp), %edi
	call	srand@PLT
	testl	%r12d, %r12d
	je	.L1
	movq	%r12, %rbp
	xorl	%ebx, %ebx
	.p2align 4,,10
	.p2align 3
.L3:
	call	rand@PLT
	movl	0(%r13,%rbx,4), %ecx
	cltd
	idivl	%ebp
	movslq	%edx, %rdx
	leaq	0(%r13,%rdx,4), %rax
	movl	(%rax), %edx
	movl	%edx, 0(%r13,%rbx,4)
	addq	$1, %rbx
	movl	%ecx, (%rax)
	cmpq	%r12, %rbx
	jne	.L3
.L1:
	movq	24(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L11
	addq	$40, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
.L11:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE92:
	.size	randomize_index, .-randomize_index
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"words.txt"
	.text
	.p2align 4
	.globl	load_words
	.type	load_words, @function
load_words:
.LFB93:
	.cfi_startproc
	endbr64
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movl	$2, %esi
	leaq	.LC0(%rip), %rdi
	subq	$160, %rsp
	.cfi_def_cfa_offset 176
	movq	%fs:40, %rax
	movq	%rax, 152(%rsp)
	xorl	%eax, %eax
	call	open@PLT
	movq	%rsp, %rsi
	movl	%eax, %edi
	movl	%eax, %ebx
	movl	%eax, words_fd(%rip)
	call	fstat@PLT
	movq	48(%rsp), %rsi
	movl	%ebx, %r8d
	xorl	%r9d, %r9d
	movl	$2, %ecx
	movl	$3, %edx
	xorl	%edi, %edi
	call	mmap@PLT
	movl	$34, %ecx
	xorl	%r9d, %r9d
	xorl	%edi, %edi
	movl	$-1, %r8d
	movl	$3, %edx
	movl	$3732400, %esi
	movq	%rax, %rbx
	call	mmap@PLT
	movl	$3732400, %edx
	xorl	%esi, %esi
	movq	%rax, %rdi
	movq	%rax, words(%rip)
	call	memset@PLT
	movq	%rbx, (%rax)
	movzbl	(%rbx), %edx
	movq	%rax, %rcx
	testb	%dl, %dl
	je	.L16
	.p2align 4,,10
	.p2align 3
.L13:
	movq	%rbx, %rax
	cmpb	$10, %dl
	jne	.L15
	addq	$1, %rax
	movb	$0, (%rbx)
	addq	$8, %rcx
	movq	%rax, (%rcx)
.L15:
	movzbl	1(%rax), %edx
	leaq	1(%rax), %rbx
	testb	%dl, %dl
	jne	.L13
.L16:
	xorl	%eax, %eax
	leaq	all_index(%rip), %rcx
	.p2align 4,,10
	.p2align 3
.L14:
	movl	%eax, (%rcx,%rax,4)
	leaq	1(%rax), %rdx
	addq	$2, %rax
	movl	%edx, (%rcx,%rdx,4)
	cmpq	$466550, %rax
	jne	.L14
	movq	152(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L25
	addq	$160, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 16
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
.L25:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE93:
	.size	load_words, .-load_words
	.p2align 4
	.globl	close_all
	.type	close_all, @function
close_all:
.LFB94:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$168, %rsp
	.cfi_def_cfa_offset 192
	movl	words_fd(%rip), %ebx
	movq	%fs:40, %rax
	movq	%rax, 152(%rsp)
	xorl	%eax, %eax
	movq	%rsp, %rsi
	movl	%ebx, %edi
	call	fstat@PLT
	movq	words(%rip), %rbp
	movl	$3732400, %esi
	movq	0(%rbp), %rdi
	call	munmap@PLT
	movq	48(%rsp), %rsi
	movq	%rbp, %rdi
	call	munmap@PLT
	movl	%ebx, %edi
	call	close@PLT
	movq	152(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L29
	addq	$168, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
.L29:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE94:
	.size	close_all, .-close_all
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC1:
	.string	"Test 1: Filling a linked-list with %d instances of struct_a\n"
	.section	.rodata.str1.1
.LC2:
	.string	"%luns\n"
	.section	.rodata.str1.8
	.align 8
.LC3:
	.string	"Test 2: searching through the list for %d randomized names\n"
	.align 8
.LC4:
	.string	"Test 3: searching through the list for %d randomized names\n"
	.text
	.p2align 4
	.globl	do_test_a
	.type	do_test_a, @function
do_test_a:
.LFB97:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$136, %rsp
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	.cfi_offset 3, -56
	movl	%edi, -136(%rbp)
	movq	%rsp, %rcx
	movq	%fs:40, %rax
	movq	%rax, -56(%rbp)
	xorl	%eax, %eax
	movslq	%edi, %rax
	leaq	0(,%rax,4), %r13
	movq	%rax, -144(%rbp)
	leaq	15(%r13), %rax
	movq	%rax, %rsi
	movq	%rax, %rdx
	andq	$-4096, %rsi
	andq	$-16, %rdx
	subq	%rsi, %rcx
	cmpq	%rcx, %rsp
	je	.L32
.L77:
	subq	$4096, %rsp
	orq	$0, 4088(%rsp)
	cmpq	%rcx, %rsp
	jne	.L77
.L32:
	andl	$4095, %edx
	subq	%rdx, %rsp
	testq	%rdx, %rdx
	jne	.L78
.L33:
	movq	%rax, %rdx
	movq	%rsp, %rcx
	andq	$-4096, %rax
	movq	%rsp, -112(%rbp)
	subq	%rax, %rcx
	andq	$-16, %rdx
	cmpq	%rcx, %rsp
	je	.L35
.L79:
	subq	$4096, %rsp
	orq	$0, 4088(%rsp)
	cmpq	%rcx, %rsp
	jne	.L79
.L35:
	andl	$4095, %edx
	subq	%rdx, %rsp
	testq	%rdx, %rdx
	jne	.L80
.L36:
	leaq	-80(%rbp), %rbx
	movl	$2, %edi
	movq	%rsp, -104(%rbp)
	leaq	all_index(%rip), %r14
	movq	%rbx, %rsi
	movq	%r14, %r12
	leaq	1866200(%r14), %r15
	call	clock_gettime@PLT
	movl	-72(%rbp), %edi
	call	srand@PLT
	.p2align 4,,10
	.p2align 3
.L37:
	call	rand@PLT
	movl	(%r12), %ecx
	addq	$4, %r12
	movslq	%eax, %rdx
	movl	%eax, %esi
	imulq	$1206622985, %rdx, %rdx
	sarl	$31, %esi
	sarq	$49, %rdx
	subl	%esi, %edx
	imull	$466550, %edx, %edx
	subl	%edx, %eax
	cltq
	leaq	(%r14,%rax,4), %rax
	movl	(%rax), %edx
	movl	%edx, -4(%r12)
	movl	%ecx, (%rax)
	cmpq	%r15, %r12
	jne	.L37
	movq	-112(%rbp), %r12
	movq	%r14, %rsi
	movq	%r13, %rcx
	movq	%r13, %rdx
	movq	%r12, %rdi
	call	__memcpy_chk@PLT
	movq	-104(%rbp), %r15
	movq	%r13, %rcx
	movq	%r13, %rdx
	movq	%r12, %rsi
	movq	%r15, %rdi
	call	__memcpy_chk@PLT
	movl	-136(%rbp), %r14d
	movq	%r15, %rdi
	leaq	-96(%rbp), %r15
	movl	%r14d, %esi
	call	randomize_index
	movl	%r14d, %edx
	movl	$2, %edi
	xorl	%eax, %eax
	leaq	.LC1(%rip), %rsi
	call	__printf_chk@PLT
	movq	%r15, %rsi
	movl	$2, %edi
	call	clock_gettime@PLT
	movl	%r14d, %ecx
	sarl	$31, %r14d
	imulq	$274877907, -144(%rbp), %rax
	sarq	$38, %rax
	subl	%r14d, %eax
	movl	%eax, -112(%rbp)
	testl	%ecx, %ecx
	jle	.L38
	leaq	(%r12,%r13), %rcx
	movq	words(%rip), %rax
	movq	%rbx, -120(%rbp)
	leaq	struct_a_list(%rip), %r14
	movq	%rcx, -128(%rbp)
	movq	%r15, -152(%rbp)
	movq	%rax, %rbx
	movq	%r12, %r15
	movq	%r14, %r12
	.p2align 4,,10
	.p2align 3
.L39:
	movslq	(%r15), %rax
	movq	-120(%rbp), %rsi
	movl	$2, %edi
	addq	$4, %r15
	movq	(%rbx,%rax,8), %r14
	call	clock_gettime@PLT
	movl	$48, %esi
	movl	$1, %edi
	call	calloc@PLT
	movl	-72(%rbp), %edi
	movq	%rax, %r13
	call	srand@PLT
	movq	%r14, 0(%r13)
	movq	%r14, %rdi
	call	strlen@PLT
	movl	%eax, 8(%r13)
	call	rand@PLT
	movl	%eax, 12(%r13)
	call	rand@PLT
	movl	$12, %esi
	movl	$1, %edi
	movl	%eax, 16(%r13)
	call	calloc@PLT
	movq	(%r12), %rsi
	movq	%rax, 24(%r13)
	leaq	32(%r13), %rax
	movq	%rax, 8(%rsi)
	movq	%rax, (%r12)
	movq	%rsi, 32(%r13)
	movq	%r12, 40(%r13)
	cmpq	%r15, -128(%rbp)
	jne	.L39
	movq	-120(%rbp), %rbx
	movl	$2, %edi
	movq	-152(%rbp), %r15
	movq	%r12, %r14
	movq	%rbx, %rsi
	call	clock_gettime@PLT
	leaq	.LC2(%rip), %rax
	movq	-72(%rbp), %rdx
	movl	$2, %edi
	subq	-88(%rbp), %rdx
	movq	%rax, %rsi
	movq	%rax, -152(%rbp)
	xorl	%eax, %eax
	call	__printf_chk@PLT
	movl	-112(%rbp), %edx
	movl	$2, %edi
	xorl	%eax, %eax
	leaq	.LC3(%rip), %rsi
	call	__printf_chk@PLT
	movq	%r15, %rsi
	movl	$2, %edi
	call	clock_gettime@PLT
	cmpl	$999, -136(%rbp)
	jle	.L40
	movq	struct_a_list(%rip), %rsi
	movq	%r15, -160(%rbp)
	xorl	%r12d, %r12d
	movq	%rbx, -168(%rbp)
	movq	words(%rip), %r13
	leaq	-32(%rsi), %rax
	movq	%rsi, -120(%rbp)
	movq	%rax, -128(%rbp)
	.p2align 4,,10
	.p2align 3
.L43:
	cmpq	%r14, -120(%rbp)
	je	.L41
	movq	-104(%rbp), %rax
	movq	-128(%rbp), %r15
	movslq	(%rax,%r12,4), %rax
	movq	0(%r13,%rax,8), %rbx
	jmp	.L42
	.p2align 4,,10
	.p2align 3
.L81:
	movq	32(%r15), %rax
	leaq	-32(%rax), %r15
	cmpq	%r14, %rax
	je	.L41
.L42:
	movq	(%r15), %rdi
	movq	%rbx, %rsi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L81
.L41:
	addq	$1, %r12
	cmpl	%r12d, -112(%rbp)
	jg	.L43
	movq	-168(%rbp), %rbx
	movl	$2, %edi
	movq	-160(%rbp), %r15
	movq	%rbx, %rsi
	call	clock_gettime@PLT
	movq	-72(%rbp), %rdx
	movl	$2, %edi
	xorl	%eax, %eax
	movq	-152(%rbp), %rsi
	subq	-88(%rbp), %rdx
	call	__printf_chk@PLT
	movl	-136(%rbp), %eax
	movl	$2, %edi
	imulq	$1374389535, -144(%rbp), %r13
	leaq	.LC4(%rip), %rsi
	sarl	$31, %eax
	sarq	$38, %r13
	subl	%eax, %r13d
	xorl	%eax, %eax
	movl	%r13d, %edx
	movl	%r13d, -112(%rbp)
	call	__printf_chk@PLT
	movq	%r15, %rsi
	movl	$2, %edi
	call	clock_gettime@PLT
.L51:
	movq	struct_a_list(%rip), %rsi
	movq	%rbx, -136(%rbp)
	xorl	%r12d, %r12d
	movq	words(%rip), %r15
	leaq	-32(%rsi), %rax
	movq	%rsi, -120(%rbp)
	movq	%rax, -128(%rbp)
	.p2align 4,,10
	.p2align 3
.L48:
	cmpq	%r14, -120(%rbp)
	je	.L46
	movq	-104(%rbp), %rax
	movq	-128(%rbp), %r13
	movslq	(%rax,%r12,4), %rax
	movq	(%r15,%rax,8), %rbx
	jmp	.L47
	.p2align 4,,10
	.p2align 3
.L82:
	movq	32(%r13), %rax
	leaq	-32(%rax), %r13
	cmpq	%r14, %rax
	je	.L46
.L47:
	movq	0(%r13), %rdi
	movq	%rbx, %rsi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L82
.L46:
	addq	$1, %r12
	cmpl	%r12d, -112(%rbp)
	jg	.L48
	movq	-136(%rbp), %rbx
.L45:
	movq	%rbx, %rsi
	movl	$2, %edi
	call	clock_gettime@PLT
	movq	-72(%rbp), %rdx
	movl	$2, %edi
	xorl	%eax, %eax
	movq	-152(%rbp), %rsi
	subq	-88(%rbp), %rdx
	call	__printf_chk@PLT
	movq	struct_a_list(%rip), %rax
	movq	(%rax), %rbx
	cmpq	%r14, %rax
	je	.L30
	.p2align 4,,10
	.p2align 3
.L49:
	movq	8(%rax), %rdx
	movdqa	.LC5(%rip), %xmm0
	leaq	-32(%rax), %rdi
	movq	%rdx, 8(%rbx)
	movq	%rbx, (%rdx)
	movups	%xmm0, (%rax)
	call	free@PLT
	movq	%rbx, %rax
	movq	(%rbx), %rbx
	cmpq	%r14, %rax
	jne	.L49
.L30:
	movq	-56(%rbp), %rax
	subq	%fs:40, %rax
	jne	.L83
	leaq	-40(%rbp), %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	.cfi_remember_state
	.cfi_def_cfa 7, 8
	ret
.L78:
	.cfi_restore_state
	orq	$0, -8(%rsp,%rdx)
	jmp	.L33
.L38:
	leaq	.LC2(%rip), %r12
	movq	%rbx, %rsi
	movl	$2, %edi
	call	clock_gettime@PLT
	movq	-72(%rbp), %rdx
	movq	%r12, %rsi
	subq	-88(%rbp), %rdx
	movl	$2, %edi
	xorl	%eax, %eax
	movq	%r12, -152(%rbp)
	call	__printf_chk@PLT
	movl	-112(%rbp), %edx
	movl	$2, %edi
	xorl	%eax, %eax
	leaq	.LC3(%rip), %rsi
	call	__printf_chk@PLT
	movq	%r15, %rsi
	movl	$2, %edi
	call	clock_gettime@PLT
	movq	%rbx, %rsi
	movl	$2, %edi
	call	clock_gettime@PLT
	movq	-72(%rbp), %rdx
	movq	%r12, %rsi
	subq	-88(%rbp), %rdx
	movl	$2, %edi
	xorl	%eax, %eax
	call	__printf_chk@PLT
	leaq	.LC4(%rip), %rsi
	movl	$2, %edi
	xorl	%eax, %eax
	imulq	$1374389535, -144(%rbp), %rdx
	sarq	$38, %rdx
	subl	%r14d, %edx
	leaq	struct_a_list(%rip), %r14
	call	__printf_chk@PLT
	movq	%r15, %rsi
	movl	$2, %edi
	call	clock_gettime@PLT
	jmp	.L45
.L80:
	orq	$0, -8(%rsp,%rdx)
	jmp	.L36
.L83:
	call	__stack_chk_fail@PLT
.L40:
	movq	%rbx, %rsi
	movl	$2, %edi
	call	clock_gettime@PLT
	movq	-72(%rbp), %rdx
	movl	$2, %edi
	xorl	%eax, %eax
	movq	-152(%rbp), %rsi
	subq	-88(%rbp), %rdx
	call	__printf_chk@PLT
	movl	-136(%rbp), %eax
	movl	$200, %esi
	movl	$2, %edi
	cltd
	idivl	%esi
	leaq	.LC4(%rip), %rsi
	movl	%eax, %edx
	movl	%eax, -112(%rbp)
	xorl	%eax, %eax
	call	__printf_chk@PLT
	movq	%r15, %rsi
	movl	$2, %edi
	call	clock_gettime@PLT
	cmpl	$199, -136(%rbp)
	jle	.L45
	jmp	.L51
	.cfi_endproc
.LFE97:
	.size	do_test_a, .-do_test_a
	.section	.rodata.str1.8
	.align 8
.LC6:
	.string	"Test 1: Filling a dynamic array with %d instances of struct_b\n"
	.section	.rodata.str1.1
.LC7:
	.string	"Failed"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB8:
	.text
.LHOTB8:
	.p2align 4
	.globl	do_test_b
	.type	do_test_b, @function
do_test_b:
.LFB99:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$88, %rsp
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	.cfi_offset 3, -56
	movl	%edi, -100(%rbp)
	movq	%rsp, %rcx
	movq	%fs:40, %rax
	movq	%rax, -56(%rbp)
	xorl	%eax, %eax
	movslq	%edi, %rax
	leaq	0(,%rax,4), %r13
	movq	%rax, -120(%rbp)
	leaq	15(%r13), %rax
	movq	%rax, %rsi
	movq	%rax, %rdx
	andq	$-4096, %rsi
	andq	$-16, %rdx
	subq	%rsi, %rcx
	cmpq	%rcx, %rsp
	je	.L86
.L106:
	subq	$4096, %rsp
	orq	$0, 4088(%rsp)
	cmpq	%rcx, %rsp
	jne	.L106
.L86:
	andl	$4095, %edx
	subq	%rdx, %rsp
	testq	%rdx, %rdx
	jne	.L107
.L87:
	movq	%rax, %rdx
	movq	%rsp, %rcx
	andq	$-4096, %rax
	movq	%rsp, %r14
	subq	%rax, %rcx
	andq	$-16, %rdx
	cmpq	%rcx, %rsp
	je	.L89
.L108:
	subq	$4096, %rsp
	orq	$0, 4088(%rsp)
	cmpq	%rcx, %rsp
	jne	.L108
.L89:
	andl	$4095, %edx
	subq	%rdx, %rsp
	testq	%rdx, %rdx
	jne	.L109
.L90:
	leaq	-80(%rbp), %rax
	movl	$2, %edi
	movq	%rsp, -112(%rbp)
	leaq	all_index(%rip), %rbx
	movq	%rax, %rsi
	movq	%rax, -128(%rbp)
	movq	%rbx, %r15
	leaq	1866200(%rbx), %r12
	call	clock_gettime@PLT
	movl	-72(%rbp), %edi
	call	srand@PLT
	.p2align 4,,10
	.p2align 3
.L91:
	call	rand@PLT
	movl	(%r15), %esi
	addq	$4, %r15
	movslq	%eax, %rdx
	movl	%eax, %edi
	imulq	$1206622985, %rdx, %rdx
	sarl	$31, %edi
	sarq	$49, %rdx
	subl	%edi, %edx
	imull	$466550, %edx, %edx
	subl	%edx, %eax
	cltq
	leaq	(%rbx,%rax,4), %rax
	movl	(%rax), %edx
	movl	%edx, -4(%r15)
	movl	%esi, (%rax)
	cmpq	%r12, %r15
	jne	.L91
	movq	%rbx, %rsi
	movq	%r13, %rcx
	movq	%r13, %rdx
	movq	%r14, %rdi
	call	__memcpy_chk@PLT
	movq	-112(%rbp), %rbx
	movq	%r13, %rcx
	movq	%r13, %rdx
	movq	%r14, %rsi
	movq	%rbx, %rdi
	call	__memcpy_chk@PLT
	movl	-100(%rbp), %r15d
	movq	%rbx, %rdi
	movl	%r15d, %esi
	call	randomize_index
	movl	$32, %esi
	movl	$1, %edi
	call	calloc@PLT
	leaq	.LC6(%rip), %rsi
	movl	$2, %edi
	movl	%r15d, %edx
	movq	%rax, %rbx
	xorl	%eax, %eax
	call	__printf_chk@PLT
	leaq	-96(%rbp), %rax
	movl	$2, %edi
	movq	%rax, %rsi
	movq	%rax, -112(%rbp)
	call	clock_gettime@PLT
	testl	%r15d, %r15d
	jle	.L92
	movq	-120(%rbp), %rax
	movl	$32, %r13d
	leaq	1(%rax), %r15
	salq	$5, %r15
	.p2align 4,,10
	.p2align 3
.L94:
	movq	%rbx, %rdi
	movq	%r13, %rsi
	call	realloc@PLT
	movq	%rax, %rbx
	testq	%rax, %rax
	je	.L104
	movl	-88(%rbp), %edi
	leaq	-32(%rbx,%r13), %r12
	addq	$32, %r13
	addq	$4, %r14
	call	srand@PLT
	movslq	-4(%r14), %rdx
	movq	words(%rip), %rax
	movq	(%rax,%rdx,8), %rdi
	movq	%rdi, (%r12)
	call	strlen@PLT
	movl	%eax, 8(%r12)
	call	rand@PLT
	movl	%eax, 12(%r12)
	call	rand@PLT
	movl	$64, %esi
	movl	$1, %edi
	movl	%eax, 16(%r12)
	call	calloc@PLT
	movq	%rax, 24(%r12)
	cmpq	%r15, %r13
	jne	.L94
.L92:
	movq	-128(%rbp), %r14
	leaq	.LC2(%rip), %r12
	movl	$2, %edi
	movq	%r14, %rsi
	call	clock_gettime@PLT
	movq	-72(%rbp), %rdx
	movq	%r12, %rsi
	subq	-88(%rbp), %rdx
	movl	$2, %edi
	xorl	%eax, %eax
	call	__printf_chk@PLT
	movq	-120(%rbp), %r15
	movl	-100(%rbp), %r13d
	xorl	%eax, %eax
	leaq	.LC3(%rip), %rsi
	movl	$2, %edi
	imulq	$274877907, %r15, %rdx
	sarl	$31, %r13d
	sarq	$38, %rdx
	subl	%r13d, %edx
	call	__printf_chk@PLT
	movq	-112(%rbp), %rsi
	movl	$2, %edi
	call	clock_gettime@PLT
	movq	%r14, %rsi
	movl	$2, %edi
	call	clock_gettime@PLT
	movq	-72(%rbp), %rdx
	movq	%r12, %rsi
	subq	-88(%rbp), %rdx
	movl	$2, %edi
	xorl	%eax, %eax
	call	__printf_chk@PLT
	imulq	$1374389535, %r15, %rdx
	leaq	.LC4(%rip), %rsi
	xorl	%eax, %eax
	movl	$2, %edi
	sarq	$38, %rdx
	subl	%r13d, %edx
	call	__printf_chk@PLT
	movq	-112(%rbp), %rsi
	movl	$2, %edi
	call	clock_gettime@PLT
	movq	%r14, %rsi
	movl	$2, %edi
	call	clock_gettime@PLT
	movq	-72(%rbp), %rdx
	movl	$2, %edi
	xorl	%eax, %eax
	subq	-88(%rbp), %rdx
	movq	%r12, %rsi
	call	__printf_chk@PLT
	movq	%rbx, %rdi
	call	free@PLT
	movq	-56(%rbp), %rax
	subq	%fs:40, %rax
	jne	.L110
	leaq	-40(%rbp), %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	.cfi_remember_state
	.cfi_def_cfa 7, 8
	ret
	.p2align 4,,10
	.p2align 3
.L107:
	.cfi_restore_state
	orq	$0, -8(%rsp,%rdx)
	jmp	.L87
.L109:
	orq	$0, -8(%rsp,%rdx)
	jmp	.L90
.L110:
	call	__stack_chk_fail@PLT
	.cfi_endproc
	.section	.text.unlikely
	.cfi_startproc
	.type	do_test_b.cold, @function
do_test_b.cold:
.LFSB99:
.L104:
	.cfi_def_cfa 6, 16
	.cfi_offset 3, -56
	.cfi_offset 6, -16
	.cfi_offset 12, -48
	.cfi_offset 13, -40
	.cfi_offset 14, -32
	.cfi_offset 15, -24
	leaq	.LC7(%rip), %rdi
	call	perror@PLT
	movl	$1, %edi
	call	exit@PLT
	.cfi_endproc
.LFE99:
	.text
	.size	do_test_b, .-do_test_b
	.section	.text.unlikely
	.size	do_test_b.cold, .-do_test_b.cold
.LCOLDE8:
	.text
.LHOTE8:
	.section	.data.rel.local,"aw"
	.align 16
	.type	struct_a_list, @object
	.size	struct_a_list, 16
struct_a_list:
	.quad	struct_a_list
	.quad	struct_a_list
	.local	all_index
	.comm	all_index,1866200,32
	.local	words_fd
	.comm	words_fd,4,4
	.local	words
	.comm	words,8,8
	.section	.rodata.cst16,"aM",@progbits,16
	.align 16
.LC5:
	.quad	256
	.quad	290
	.ident	"GCC: (Ubuntu 13.2.0-23ubuntu4) 13.2.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
