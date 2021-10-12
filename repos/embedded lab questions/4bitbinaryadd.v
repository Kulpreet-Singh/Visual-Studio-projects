module half_adder (
    a, b, sum, carry
);

    input a,b;
    output sum, carry;

    assign sum=a^b;
    assign carry = a&b;
    
endmodule

module full_adder (
    a, b, c, sum, carry
);

    input a, b, c;
    output sum, carry;

    assign sum = a^b^c;
    assign carry = a&b | b&c | a&c;
    
endmodule

module fourbitbinaryAdd(a0, a1, a2, a3, b0, b1, b2, b3, s0, s1, s2, s3, c3);

    input a0, a1, a2, a3, b0, b1, b2, b3;
    output s0, s1, s2, s3, c3;
    wire c0, c1, c2;
    half_adder ha1(a0, b0, s0, c0);

    full_adder fa1(a1, b1, c0, s1, c1);
    full_adder fa2(a2, b2, c1, s2, c2);
    full_adder fa3(a3, b3, c2, s3, c3);
endmodule


module test; 
    reg a0, a1, a2, a3, b0, b1, b2, b3;
    wire s0, s1, s2, s3, carry;
    fourbitbinaryAdd fourbitnumbersadder(a0,a1,a2,a3,b0,b1,b2,b3,s0,s1,s2,s3, carry);
    initial begin
            

        a3=0; a2=1; a1=0; a0=0;
        b3=0; b2=0; b1=1; b0=1;
        #10

        a3=0; a2=0; a1=0; a0=0;
        b3=0; b2=0; b1=0; b0=0;
        #10

        $finish;
         
        
    end

    initial begin
        $dumpfile("dump1.vcd");
        $dumpvars(0, test);
        $display("display\t%d\t%d\t%d\t%d", a3, a2, a1, a0);
        $display("display\t%d\t%d\t%d\t%d\tcarry", b3, b2, b1, b0);
        $monitor("monitoring s\t%d\t%d\t%d\t%d\t %d", s3, s2, s1, s0, carry);
        
        // $monitor("monitoring s\t%d\t%d\t%d\t%d\t", b3, b2, b1, b0);
        // $monitor("monitoring a\t%d\t%d\t%d\t%d\t %d", a3, a2, a1, a0, carry);
    end
endmodule