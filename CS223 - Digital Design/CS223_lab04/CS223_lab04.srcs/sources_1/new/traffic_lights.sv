`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05.04.2021 23:33:40
// Design Name: 
// Module Name: traffic_lights
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


module traffic_lights(
    input clk,
    input reset,
    input  SA,
    input  SB,
    output logic[2:0] LA,
    output logic [2:0] LB

    );
    reg [3:0] state, next;
    localparam s0 = 0, s1 = 1, s2 = 2, s3 = 3,
                s4 = 4, s5 = 5, s6 = 6, s7 = 7;
                
    //Sequential Block
    always @(posedge clk, negedge reset)
    begin 
        if(~reset)
            state <= s0;
        else
            state <= next;
    end
    
    always @(*)
    begin
        next = state;
        case(state)
            s0: if(SA)
                    next = s0;
                else
                    next = s1;
             s1, s2, s3, s5, s6:
                next = state + 1;
                
              s4: if(SB)
                    next = s4;
                  else
                    next = s5;
               
              s7: next = s0;
             default: next = s0;    
          endcase   
    end
    
    //Output Logic
    always @(*)
    begin
        case(state)
          s0:
            begin
                LA[0] = 0;
                LA[1] = 0;
                LA[2] = 1;
        
                LB[0] = 1;
                LB[1] = 0;
                LB[2] = 0;
            end //A: Green, B: Red
            
            s1, s7:
            begin
                LA[0] = 0;
                LA[1] = 1;
                LA[2] = 0;
        
                LB[0] = 1;
                LB[1] = 0;
                LB[2] = 0;
            end//A: Yellow, B: Red
            
            s2, s6:
            begin
                LA[0] = 1;
                LA[1] = 0;
                LA[2] = 0;
        
                LB[0] = 1;
                LB[1] = 0;
                LB[2] = 0;
            end//A: Red, B: Red
            
            s3, s5:
            begin
                LA[0] = 1;
                LA[1] = 0;
                LA[2] = 0;
        
                LB[0] = 0;
                LB[1] = 1;
                LB[2] = 0;//A: Red, B: Yellow
            end
            
            s4:
            begin
                LA[0] = 1;
                LA[1] = 0;
                LA[2] = 0;
        
                LB[0] = 0;
                LB[1] = 0;
                LB[2] = 1;//A: Red, B:Green
            end 
            
            default: 
            begin
                LA[0] = 1;
                LA[1] = 0;
                LA[2] = 0;
        
                LB[0] = 1;
                LB[1] = 0;
                LB[2] = 0;    
             end    
        endcase    
    end   
endmodule
//Output Logic
//    always @(*)
//    begin
//        A1 = 0;
//        A0 = 0;
//        B1 = 0;
//        B0 = 0;
//        case(state)
//          s0:
//            begin
//                A1 = 1;
//                A0 = 0;
//                B1 = 0;
//                B0 = 0;
//            end //A: Green, B: Red
            
//            s1, s7:
//            begin
//                A1 = 0;
//                A0 = 1;
//                B1 = 0;
//                B0 = 0;
//            end//A: Yellow, B: Red
            
//            s2, s6:
//            begin
//                A1 = 0;
//                A0 = 0;
//                B1 = 0;
//                B0 = 0;
//            end//A: Red, B: Red
            
//            s3, s5:
//            begin
//                A1 = 0;
//                A0 = 0;
//                B1 = 0;
//                B0 = 1;//A: Red, B: Yellow
//            end
            
//            s4:
//            begin
//                A1 = 0;
//                A0 = 0;
//                B1 = 1;
//                B0 = 0;//A: Red, B:Green
//            end          
//        endcase
//    end

//-------------------------------------------------------------------------------------------------------------------------------
//    logic S2, S1, S0; 
//    logic S2_next, S1_next, S0_next;
    
    
    
    
//    //Sequentail Block
//    always @(posedge clk)
//    begin  
//        S2 <= S2_next; 
//        S1 <= S1_next; 
//        S0 <= S0_next; 
//    end
    
//    //Next State Logic
//    always @(*)
//    begin
//        S2_next = ~S2 && S1 && S0
//                  || S2 && ~S0
//                  || S2 && ~S1;
                  
//        S1_next = S1 && ~S0
//                  || ~S1 && S0;
                  
//        S2_next = ~S2 && ~S0 && ~SA 
//                  || S1 && ~S0
//                  || S2 && ~S0 && ~SB;            
//    end
    
//    //output logic
//    assign A1 = ~S2 && ~S1 && ~S0;
    
//    assign A0 = ~S2 && ~S1 && S0
//         || S2 && S1 && S0;
         
//    assign B1 = S2 && ~S1 && ~S0;
    
//    assign B0 = ~S2 && S1 && S0
//                || S2 && ~S1 && S0;
    
//    myMux mux2 (S2, S2, S2, ~S2, S1, S0, S2);//S2'
//    myMux mux1 (S0, S0, ~S0, ~S0, S1, S0, S1);//S1'
//    myMux mux0 ((~SA && S1), S2, (~SB && S1), ~S2, S1, S0, S0);//S0'