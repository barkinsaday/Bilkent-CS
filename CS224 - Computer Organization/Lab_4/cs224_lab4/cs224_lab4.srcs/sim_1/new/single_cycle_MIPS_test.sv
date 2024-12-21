`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03.04.2022 22:11:18
// Design Name: 
// Module Name: single_cycle_MIPS_test
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


module single_cycle_MIPS_test();

logic clk, reset, memwrite;
logic[31:0] writedata, dataadr, pc, instr, readdata;



top uut( clk, reset, writedata, dataadr, pc, instr, readdata, memwrite );

always begin
    clk = 0;
    #5;
    clk = 1;
    #5;
end

initial begin
    reset = 1;
    #5;
    reset = 0;
    #5;
end
endmodule
