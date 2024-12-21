`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03.05.2021 22:14:25
// Design Name: 
// Module Name: Controller
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


module Controller(
    input logic [11:0] c, //controller register 12-bit
    input reg [11:0] d_in,
    output reg [11:0] q_out,
    input logic clk,
    input reset
    );
    
    //bit part declared
    reg [3:0] d; //data memory
    assign d = c[3:0];
    
    reg [2:0] r; //register to load & store
    assign r = c[6:4];
    
    reg [2:0] ra;//register to least significant bit
    assign ra = c[5:3];
    
    reg [2:0] rb; // register to most significant bit
    assign rb = c[2:0];
    
    reg [2:0] w; // register to store + - operation results
    assign w = c[8:6];
    
    reg [2:0] op; //operation (first 3 bits)
    assign op = c[11:9];
    
    always@*//reset
    begin
        if ( reset )
        begin
            q_out <= 0;
        end
    end

    //operations d and q
    always@( posedge clk )
       
      begin 
        if( d_in[11:9] == 3'b000 )//LOAD
        begin
        q_out <= d_in;
        end 
        
        else if( d_in[11:9] == 3'b001 )//STORE
        begin
        d_in <= q_out;
        end
        
        else if( d_in[11:9] == 3'b101 )//ADD
        begin
        q_out[8:6] <= q_out[5:3] + q_out[2:0];
        end
        
        else if( d_in[11:9] == 3'b110 )//SUBTRACT
        begin
        q_out[8:6] <= q_out[2:0] - q_out[5:3];
        end
      end //end of always statement
      
      
      //operations with bit segments
      always@( posedge clk)
      begin 
        if( op == 0 )//LOAD
        begin
        r <= d;
        end 
        
        else if( op == 1 )//STORE
        begin
        d <= r;
        end
        
        else if( op == 2 )//ADD
        begin
        w <= ra + rb;
        end
        
        else if( op == 3 )//SUBTRACT
        begin
        w <= ra - rb;
        end
      end //end of always statement
 
endmodule
