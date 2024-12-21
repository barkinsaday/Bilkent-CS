`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03.05.2021 22:51:42
// Design Name: 
// Module Name: test_controller
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module test_controller();
    reg [11:0] d;
    reg [11:0] q;
    logic [11:0] cont;
    logic clk;
    logic reset;
    
    Controller uut( .c(cont), .d_in(d), .q_out(q), .clk(clk), .reset(reset) );
    
    assign reset = 0;
    assign cont = 0;
    assign d = 0;
    assign q = 0;
    
    always
      begin
        clk = 0;
        #5;
        
        clk = 1;
        #5;
      end
    
    
    initial begin
    
    d = 12'b000001011100;//05c
    #10;
    
    d = 12'b000000000000;//000
    #10;
    
    d = 12'b000110101010;//11a
    #10;
    
    d = 12'b001111111111;//3ff
    #10;
    
    d = 12'b101000001010;//a0a
    #10;
    
    d = 12'b110111001110;
    #10;
    end //end declaration
    
    
endmodule
