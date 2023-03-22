`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/21/2023 02:16:20 PM
// Design Name: 
// Module Name: latch
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


module latch #(parameter N_CHANNEL = 8)
//number of channels = 8
(
    input   AXI_clk, //axi clock
    input   AXI_rst_n, //axi reset, active low

    //AXI4-S slave interface (saving data)
    input   [N_CHANNEL - 1 : 0] s_data,
    input   s_valid,
    output  s_ready, 
    
    //AXI4-M master interface (send off data)
    input   m_ready,
    output  reg m_valid,
    output  reg [N_CHANNEL - 1 : 0] m_data
    );
    
    always @(posedge AXI_clk) begin
        if (s_valid & s_ready) begin
            m_data <= s_data;
        end
    end
    
    
    always @(posedge AXI_clk) begin
        m_valid <= s_valid;
    end
    
    assign s_ready = m_ready;
    
endmodule
