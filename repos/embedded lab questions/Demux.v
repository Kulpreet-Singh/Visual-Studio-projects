module Demux(a,b,c,d,s1,s0,y);
    input y, s1, s0;
    output a, b, c, d;
    assign a = (~s1&~s0)&y;
    assign b = (~s1&s0)&y;
    assign c = (s1&~s0)&y;
    assign d = (s1&s0)&y;
endmodule

module main;
    reg y, s1, s0;
    wire a, b, c, d;
    Demux test(a,b,c,d,s1,s0,y);
    
    initial begin
        y = 1'b1;
        #10
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
      $dumpfile("Demux.vcd");
      $dumpvars(0, main);
      $monitor("a=%d, b=%d, c=%d, d=%d, s1=%d, s0=%d, y=%d", a, b, c, d, s1, s0, y);
    end
    
endmodule