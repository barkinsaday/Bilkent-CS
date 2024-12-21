`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 06.05.2021 06:57:44
// Design Name: 
// Module Name: Digit_Control
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


module Digit_Control(
 input [3:0] digit1,
 input [3:0] digit2,
 input [3:0] digit3,
 input [3:0] digit4, 
 input [1:0] counter_out,
 output reg [3:0] DIGIT = 0
    );
    
    always@( counter_out)
    begin 
        case( counter_out )
            2'd0:
                DIGIT = digit1;
                
             2'd1:
                DIGIT = digit2;    
                
             2'd2:
                DIGIT = digit3;    
                
             2'd3:
                DIGIT = digit4;    
        endcase
    end
    
endmodule
