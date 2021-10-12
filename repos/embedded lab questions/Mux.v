module Mux(a,b,c,d,s1,s0,y);
    input a,b,c,d, s1, s0;
    output y;
    assign y = (~s1&~s0&a)|(~s1&s0&b)|(s1&~s0&c)|(s1&s0&d);
endmodule

module main;
    reg a, b, c, d, s1, s0;
    wire y;
    Mux test(a,b,c,d,s1,s0,y);
    
    initial begin
        a = 1'b1; b = 1'b0; c = 1'b1; d = 1'b1;
    end
    
    initial begin
        s1 = 1'b0; s0 = 1'b0;
        #10
        s1 = 1'b0; s0 = 1'b1;
        #10
        s1 = 1'b1; s0 = 1'b0;
        #10
        s1 = 1'b1; s0 = 1'b1;
      $finish ;    
    end
    
    initial begin
      $dumpfile("Mux.vcd");
      $dumpvars(0, main);
      $monitor("a=%d, b=%d, c=%d, d=%d, s1=%d, s0=%d, y=%d", a, b, c, d, s1, s0, y);
    end
    
endmodule