
.syntax unified
.cpu cortex-m0
;.align 2
.thumb
.code 16
.text	

   .global  inner_prod
   
   

x       .req  r0    /*; input array x[] */
c       .req  r1    /*; input array c[] */
N       .req  r2    /*;offset and number of samples (a multiple of 4) // 40 samples: the lpcsize == 40 for narrowband mode, submode3 */
acc     .req  r3    /*; accumulator */
sum     .req  r6    /*; sum */
x_0     .req  r4    /*; elements from array x[]*/
c_0     .req  r5    /*; elements from array c[] */




.thumb_func
inner_prod:

    push    {r0-r7, lr}	/*; store valid parameters into stack	*/
    movs     sum, #0			/*; reset sum value*/
        
Loop:
        
    movs    acc, #0			/*; reset accumulator*/
    movs	N, #0			// reset offset

    //cycle 1
    ldrsh	x_0, [x, N]		//load x0 by x+n
    ldrsh	c_0, [c, N]		//load c0 by c+n
    muls	x_0, c_0, x_0	//x0*c0 -> x0
    add		acc, acc, x_0	// acc=acc+x0
    adds	N, #2			//n=n+2

    ldrsh	x_0, [x, N]		//load x0 by x+n
    ldrsh	c_0, [c, N]		//load c0 by c+n
    muls	x_0, c_0, x_0	//x0*c0 -> x0
    add		acc, acc, x_0	// acc=acc+x0
    adds	N, #2			//n=n+2

    ldrsh	x_0, [x, N]		//load x0 by x+n
    ldrsh	c_0, [c, N]		//load c0 by c+n
    muls	x_0, c_0, x_0	//x0*c0 -> x0
    add		acc, acc, x_0	// acc=acc+x0
    adds	N, #2			//n=n+2

    ldrsh	x_0, [x, N]		//load x0 by x+n
    ldrsh	c_0, [c, N]		//load c0 by c+n
    muls	x_0, c_0, x_0	//x0*c0 -> x0
    add		acc, acc, x_0	// acc=acc+x0
    adds	N, #2			//n=n+2

	asrs	acc, acc, #6	//acc=acc>>6
	add		sum, sum, acc	//sum=sum+acc

    //cycle 2
    ldrsh	x_0, [x, N]		//load x0 by x+n
    ldrsh	c_0, [c, N]		//load c0 by c+n
    muls	x_0, c_0, x_0	//x0*c0 -> x0
    add		acc, acc, x_0	// acc=acc+x0
    adds	N, #2			//n=n+2

    ldrsh	x_0, [x, N]		//load x0 by x+n
    ldrsh	c_0, [c, N]		//load c0 by c+n
    muls	x_0, c_0, x_0	//x0*c0 -> x0
    add		acc, acc, x_0	// acc=acc+x0
    adds	N, #2			//n=n+2

    ldrsh	x_0, [x, N]		//load x0 by x+n
    ldrsh	c_0, [c, N]		//load c0 by c+n
    muls	x_0, c_0, x_0	//x0*c0 -> x0
    add		acc, acc, x_0	// acc=acc+x0
    adds	N, #2			//n=n+2

    ldrsh	x_0, [x, N]		//load x0 by x+n
    ldrsh	c_0, [c, N]		//load c0 by c+n
    muls	x_0, c_0, x_0	//x0*c0 -> x0
    add		acc, acc, x_0	// acc=acc+x0
    adds	N, #2			//n=n+2

	asrs	acc, acc, #6	//acc=acc>>6
	add		sum, sum, acc	//sum=sum+acc

    //cycle 3
    ldrsh	x_0, [x, N]		//load x0 by x+n
    ldrsh	c_0, [c, N]		//load c0 by c+n
    muls	x_0, c_0, x_0	//x0*c0 -> x0
    add		acc, acc, x_0	// acc=acc+x0
    adds	N, #2			//n=n+2

    ldrsh	x_0, [x, N]		//load x0 by x+n
    ldrsh	c_0, [c, N]		//load c0 by c+n
    muls	x_0, c_0, x_0	//x0*c0 -> x0
    add		acc, acc, x_0	// acc=acc+x0
    adds	N, #2			//n=n+2

    ldrsh	x_0, [x, N]		//load x0 by x+n
    ldrsh	c_0, [c, N]		//load c0 by c+n
    muls	x_0, c_0, x_0	//x0*c0 -> x0
    add		acc, acc, x_0	// acc=acc+x0
    adds	N, #2			//n=n+2

    ldrsh	x_0, [x, N]		//load x0 by x+n
    ldrsh	c_0, [c, N]		//load c0 by c+n
    muls	x_0, c_0, x_0	//x0*c0 -> x0
    add		acc, acc, x_0	// acc=acc+x0
    adds	N, #2			//n=n+2

	asrs	acc, acc, #6	//acc=acc>>6
	add		sum, sum, acc	//sum=sum+acc

    //cycle 4
    ldrsh	x_0, [x, N]		//load x0 by x+n
    ldrsh	c_0, [c, N]		//load c0 by c+n
    muls	x_0, c_0, x_0	//x0*c0 -> x0
    add		acc, acc, x_0	// acc=acc+x0
    adds	N, #2			//n=n+2

    ldrsh	x_0, [x, N]		//load x0 by x+n
    ldrsh	c_0, [c, N]		//load c0 by c+n
    muls	x_0, c_0, x_0	//x0*c0 -> x0
    add		acc, acc, x_0	// acc=acc+x0
    adds	N, #2			//n=n+2

    ldrsh	x_0, [x, N]		//load x0 by x+n
    ldrsh	c_0, [c, N]		//load c0 by c+n
    muls	x_0, c_0, x_0	//x0*c0 -> x0
    add		acc, acc, x_0	// acc=acc+x0
    adds	N, #2			//n=n+2

    ldrsh	x_0, [x, N]		//load x0 by x+n
    ldrsh	c_0, [c, N]		//load c0 by c+n
    muls	x_0, c_0, x_0	//x0*c0 -> x0
    add		acc, acc, x_0	// acc=acc+x0
    adds	N, #2			//n=n+2

	asrs	acc, acc, #6	//acc=acc>>6
	add		sum, sum, acc	//sum=sum+acc

    //cycle 5
    ldrsh	x_0, [x, N]		//load x0 by x+n
    ldrsh	c_0, [c, N]		//load c0 by c+n
    muls	x_0, c_0, x_0	//x0*c0 -> x0
    add		acc, acc, x_0	// acc=acc+x0
    adds	N, #2			//n=n+2

    ldrsh	x_0, [x, N]		//load x0 by x+n
    ldrsh	c_0, [c, N]		//load c0 by c+n
    muls	x_0, c_0, x_0	//x0*c0 -> x0
    add		acc, acc, x_0	// acc=acc+x0
    adds	N, #2			//n=n+2

    ldrsh	x_0, [x, N]		//load x0 by x+n
    ldrsh	c_0, [c, N]		//load c0 by c+n
    muls	x_0, c_0, x_0	//x0*c0 -> x0
    add		acc, acc, x_0	// acc=acc+x0
    adds	N, #2			//n=n+2

    ldrsh	x_0, [x, N]		//load x0 by x+n
    ldrsh	c_0, [c, N]		//load c0 by c+n
    muls	x_0, c_0, x_0	//x0*c0 -> x0
    add		acc, acc, x_0	// acc=acc+x0
    adds	N, #2			//n=n+2

	asrs	acc, acc, #6	//acc=acc>>6
	add		sum, sum, acc	//sum=sum+acc

    //cycle 6
    ldrsh	x_0, [x, N]		//load x0 by x+n
    ldrsh	c_0, [c, N]		//load c0 by c+n
    muls	x_0, c_0, x_0	//x0*c0 -> x0
    add		acc, acc, x_0	// acc=acc+x0
    adds	N, #2			//n=n+2

    ldrsh	x_0, [x, N]		//load x0 by x+n
    ldrsh	c_0, [c, N]		//load c0 by c+n
    muls	x_0, c_0, x_0	//x0*c0 -> x0
    add		acc, acc, x_0	// acc=acc+x0
    adds	N, #2			//n=n+2

    ldrsh	x_0, [x, N]		//load x0 by x+n
    ldrsh	c_0, [c, N]		//load c0 by c+n
    muls	x_0, c_0, x_0	//x0*c0 -> x0
    add		acc, acc, x_0	// acc=acc+x0
    adds	N, #2			//n=n+2

    ldrsh	x_0, [x, N]		//load x0 by x+n
    ldrsh	c_0, [c, N]		//load c0 by c+n
    muls	x_0, c_0, x_0	//x0*c0 -> x0
    add		acc, acc, x_0	// acc=acc+x0
    adds	N, #2			//n=n+2

	asrs	acc, acc, #6	//acc=acc>>6
	add		sum, sum, acc	//sum=sum+acc

    //cycle 7
    ldrsh	x_0, [x, N]		//load x0 by x+n
    ldrsh	c_0, [c, N]		//load c0 by c+n
    muls	x_0, c_0, x_0	//x0*c0 -> x0
    add		acc, acc, x_0	// acc=acc+x0
    adds	N, #2			//n=n+2

    ldrsh	x_0, [x, N]		//load x0 by x+n
    ldrsh	c_0, [c, N]		//load c0 by c+n
    muls	x_0, c_0, x_0	//x0*c0 -> x0
    add		acc, acc, x_0	// acc=acc+x0
    adds	N, #2			//n=n+2

    ldrsh	x_0, [x, N]		//load x0 by x+n
    ldrsh	c_0, [c, N]		//load c0 by c+n
    muls	x_0, c_0, x_0	//x0*c0 -> x0
    add		acc, acc, x_0	// acc=acc+x0
    adds	N, #2			//n=n+2

    ldrsh	x_0, [x, N]		//load x0 by x+n
    ldrsh	c_0, [c, N]		//load c0 by c+n
    muls	x_0, c_0, x_0	//x0*c0 -> x0
    add		acc, acc, x_0	// acc=acc+x0
    adds	N, #2			//n=n+2

	asrs	acc, acc, #6	//acc=acc>>6
	add		sum, sum, acc	//sum=sum+acc

    //cycle 8
    ldrsh	x_0, [x, N]		//load x0 by x+n
    ldrsh	c_0, [c, N]		//load c0 by c+n
    muls	x_0, c_0, x_0	//x0*c0 -> x0
    add		acc, acc, x_0	// acc=acc+x0
    adds	N, #2			//n=n+2

    ldrsh	x_0, [x, N]		//load x0 by x+n
    ldrsh	c_0, [c, N]		//load c0 by c+n
    muls	x_0, c_0, x_0	//x0*c0 -> x0
    add		acc, acc, x_0	// acc=acc+x0
    adds	N, #2			//n=n+2

    ldrsh	x_0, [x, N]		//load x0 by x+n
    ldrsh	c_0, [c, N]		//load c0 by c+n
    muls	x_0, c_0, x_0	//x0*c0 -> x0
    add		acc, acc, x_0	// acc=acc+x0
    adds	N, #2			//n=n+2

    ldrsh	x_0, [x, N]		//load x0 by x+n
    ldrsh	c_0, [c, N]		//load c0 by c+n
    muls	x_0, c_0, x_0	//x0*c0 -> x0
    add		acc, acc, x_0	// acc=acc+x0
    adds	N, #2			//n=n+2

	asrs	acc, acc, #6	//acc=acc>>6
	add		sum, sum, acc	//sum=sum+acc

    //cycle 9
    ldrsh	x_0, [x, N]		//load x0 by x+n
    ldrsh	c_0, [c, N]		//load c0 by c+n
    muls	x_0, c_0, x_0	//x0*c0 -> x0
    add		acc, acc, x_0	// acc=acc+x0
    adds	N, #2			//n=n+2

    ldrsh	x_0, [x, N]		//load x0 by x+n
    ldrsh	c_0, [c, N]		//load c0 by c+n
    muls	x_0, c_0, x_0	//x0*c0 -> x0
    add		acc, acc, x_0	// acc=acc+x0
    adds	N, #2			//n=n+2

    ldrsh	x_0, [x, N]		//load x0 by x+n
    ldrsh	c_0, [c, N]		//load c0 by c+n
    muls	x_0, c_0, x_0	//x0*c0 -> x0
    add		acc, acc, x_0	// acc=acc+x0
    adds	N, #2			//n=n+2

    ldrsh	x_0, [x, N]		//load x0 by x+n
    ldrsh	c_0, [c, N]		//load c0 by c+n
    muls	x_0, c_0, x_0	//x0*c0 -> x0
    add		acc, acc, x_0	// acc=acc+x0
    adds	N, #2			//n=n+2

	asrs	acc, acc, #6	//acc=acc>>6
	add		sum, sum, acc	//sum=sum+acc

    //cycle 10
    ldrsh	x_0, [x, N]		//load x0 by x+n
    ldrsh	c_0, [c, N]		//load c0 by c+n
    muls	x_0, c_0, x_0	//x0*c0 -> x0
    add		acc, acc, x_0	// acc=acc+x0
    adds	N, #2			//n=n+2

    ldrsh	x_0, [x, N]		//load x0 by x+n
    ldrsh	c_0, [c, N]		//load c0 by c+n
    muls	x_0, c_0, x_0	//x0*c0 -> x0
    add		acc, acc, x_0	// acc=acc+x0
    adds	N, #2			//n=n+2

    ldrsh	x_0, [x, N]		//load x0 by x+n
    ldrsh	c_0, [c, N]		//load c0 by c+n
    muls	x_0, c_0, x_0	//x0*c0 -> x0
    add		acc, acc, x_0	// acc=acc+x0
    adds	N, #2			//n=n+2

    ldrsh	x_0, [x, N]		//load x0 by x+n
    ldrsh	c_0, [c, N]		//load c0 by c+n
    muls	x_0, c_0, x_0	//x0*c0 -> x0
    add		acc, acc, x_0	// acc=acc+x0
    adds	N, #2			//n=n+2

	asrs	acc, acc, #6	//acc=acc>>6
	add		sum, sum, acc	//sum=sum+acc

    pop   {r0-r7, pc}
.end
   
