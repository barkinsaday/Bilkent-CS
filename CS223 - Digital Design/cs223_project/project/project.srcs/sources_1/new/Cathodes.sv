`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 06.05.2021 07:12:07
// Design Name: 
// Module Name: Cathodes
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


module Cathodes(
    input [3:0] digit,
    output reg [6:0] cathode = 0
    );
    
    always@( digit )
    begin
        case( digit )
        
            4'd0:
                cathode = 7'b1111110;
        
            4'd1:
                cathode = 7'b0110000;
                
            4'd2:
                cathode = 7'b1101101;    
                
            4'd3:
                cathode = 7'b1111000; 
                
            4'd4:
                cathode = 7'b0110011;    
                
            4'd5:
                cathode = 7'b1011011;  
                
            4'd6:
                cathode = 7'b1011111;       
                   
            4'd7:
                cathode = 7'b1110000; 
                
            4'd8:
                cathode = 7'b1111111;     
                
             4'd9:
                cathode = 7'b1111011;                        
        endcase
    end  
endmodule
