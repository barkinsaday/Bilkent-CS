`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 06.04.2021 00:44:28
// Design Name: 
// Module Name: tb_traffic_lights
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


module tb_traffic_lights();

logic SA, SB, clk, reset;
logic [2:0] LA, LB;

traffic_lights uut( .clk(clk), .reset(reset), .SA(SA), .SB(SB), .LA(LA), .LB(LB));
    
    always
    begin
        clk = 0;
        #5;
        clk = 1;
        #5;
    end
    
    initial
    begin
        reset = 1;
        SA = 0;
        SB = 0;
        #10;
        
        SA = 1;
        SB = 0;
        #10;
        
        SA = 0;
        SB = 0;
        #10
        
        SA = 0;
        SB = 1;
        #10;
        
        SA = 0;
        SB = 0;
        #10
        
        SA = 1;
        SB = 1;
        #10;
        
        SA = 1;
        SB = 0;
    end
endmodule
