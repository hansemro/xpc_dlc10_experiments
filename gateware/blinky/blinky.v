`timescale 1ns / 1ps

module blinky(
    input wire i_ifclk,
    output wire o_led_green
);

    wire clk_ibuf, clk;

    IBUF ibuf_inst (.I(i_ifclk), .O(clk_ibuf));
    BUFG bufg_inst (.I(clk_ibuf), .O(clk));

    reg [26:0] r_count = 0;

    always @(posedge clk) r_count <= r_count + 1'b1;

    assign o_led_green = ~r_count[26];

endmodule
