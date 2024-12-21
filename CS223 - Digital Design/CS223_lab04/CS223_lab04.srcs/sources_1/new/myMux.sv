`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05.04.2021 23:26:45
// Design Name: 
// Module Name: myMux
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


module bh_4to1_mux(
    input logic a0,
    input logic a1,
    input logic a2,
    input logic a3,
    input logic s1,
    input logic s0,
    output logic y
    );
    assign y =  a0 && ~s0 && ~s1
                || a1 && s0 && ~s1
                || a2 && ~s0 && s1
                || a3 && s0 && s1;             
endmodule
