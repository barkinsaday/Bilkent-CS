`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 06.05.2021 07:04:21
// Design Name: 
// Module Name: node_control
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


module node_control(
input [1:0] counter_out,
output reg [3:0] node = 0
    );
    
    always@( counter_out)
    begin 
        case( counter_out )
            2'b00:
                node = 4'b1110;
                
             2'b01:
                node = 4'b1101;    
                
             2'b10:
                node = 4'b1011;    
                
             2'b11:
                node = 4'b0111;    
        endcase
    end
endmodule
